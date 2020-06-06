#include <iostream>
#include <fstream>
#include <ctime>

//��С�ȽϺ궨��
#ifndef MIN
#define MIN(A,B)	(((A) < (B)) ? (A) : (B))
#endif

#ifndef MAX
#define MAX(A,B)	(((A) > (B)) ? (A) : (B))
#endif

//ѵ�����ݴ��·�� mnist���ݼ�·��
#define TRAIN_DATA_PATH "./mnist/train-images.idx3-ubyte"
#define TRAIN_LABEL_PATH "./mnist/train-labels.idx1-ubyte"
#define TEST_DATA_PATH "./mnist/t10k-images.idx3-ubyte"
#define TEST_LABEL_PATH "./mnist/t10k-labels.idx1-ubyte"

//���ݼ���ѵ��/������������
#define TRAIN_NUM 60000
#define TEST_NUM 10000

//mnist���ݼ�shape
#define MNIST_ROW 28
#define MNIST_COL 28

//Lenet5ģ��Ҫ�����������Ϊ32*32
#define INPUT_ROW 32
#define INPUT_COL 32

using namespace std;

//ģ��ѵ�����ݵĽṹ�壬�������ݺͱ�ǩ
typedef struct {
	double data[INPUT_ROW * INPUT_COL];
	double label;
} Sample;

typedef struct {
	int batch;
	int height;
	int width;
	int channel;
	double* data;
}Layer;


//������
const int batchSize = 10;
const double learningRate = 0.03;
const int epochs = 3;
Sample *trainSamples, *testSamples;




//���ݶ�ȡ����
void loadMnist();
int ReverseInt(int);		//���С��ת��
void loadTrainData();
void loadTrainLabel();
void loadTestData();
void loadTestLabel();
void delMnist();

//�����
struct activation_func {
	/* scale: -0.8 ~ 0.8 ��label��ʼֵ��Ӧ */
	inline static double tan_h(double val) {
		double ep = exp(val);
		double em = exp(-val);

		return (ep - em) / (ep + em);
	}

	inline static double dtan_h(double val) {
		return 1.0 - val * val;
	}

	/* scale: 0.1 ~ 0.9 ��label��ʼֵ��Ӧ */
	inline static double relu(double val) {
		return val > 0.0 ? val : 0.0;
	}

	inline static double drelu(double val) {
		return val > 0.0 ? 1.0 : 0.0;
	}

	/* scale: 0.1 ~ 0.9 ��label��ʼֵ��Ӧ */
	inline double sigmoid(double val) {
		return 1.0 / (1.0 + exp(-val));
	}

	inline double dsigmoid(double val) {
		return val * (1.0 - val);
	}
};

//��ʧ���� ��������ʧ����
struct loss_func {
	inline static double mse(double y, double t) {
		return (y - t) * (y - t) / 2;
	}

	inline static double dmse(double y, double t) {
		return y - t;
	}
};

int main() {
	loadMnist();
	for(int a = 0;a<10;++a)
	for (int i = 0; i < 32; ++i) {
		for (int j = 0; j < 32; ++j) {
			if (trainSamples[a].data[i * 32 + j] > 0.5) cout << '*';
			else cout << ' ';
		}
		cout << endl;
	}
		

	delMnist();
	return 0;
}


int ReverseInt(int i)
{
	return ((i & 0x000000FF) << 24 | (i & 0x0000FF00) << 8 | (i & 0x00FF0000) >> 8 | (i & 0xFF000000) >> 24);
}

void loadMnist()
{
	loadTrainData();
	loadTrainLabel();
	loadTestData();
	loadTestLabel();
}


void loadTrainData() {
	ifstream file(TRAIN_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 16 + MNIST_ROW * MNIST_COL * TRAIN_NUM; //train data�е�ͼ�����ݴӵ�16�ֽڿ�ʼ
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//��Ա���Ը�ֵ�������ڴ�
		trainSamples = new Sample[TRAIN_NUM]();
		//�������� 
		for (int i = 0; i < TRAIN_NUM; ++i) {
			//����һ��ͼƬ���ݲ��� 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < MNIST_ROW; ++r) {
				for (int c = 0; c < MNIST_COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * MNIST_ROW * MNIST_COL + MNIST_COL * r + c];
					trainSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//��һ����[0,1]
				}
			}
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}
}

void loadTrainLabel() {
	ifstream file(TRAIN_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 8 + TRAIN_NUM; //train label�еı�ǩ���ݴӵ�8�ֽڿ�ʼ
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//�����ǩ����
		unsigned char label = 0;
		for (int i = 0; i < TRAIN_NUM; ++i) {
			label = (unsigned char)buffer[i + 8];
			trainSamples[i].label = (double)label;
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}
}

void loadTestData() {
	ifstream file(TEST_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 16 + MNIST_ROW * MNIST_COL * TEST_NUM; //TEST data�е�ͼ�����ݴӵ�16�ֽڿ�ʼ
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//��Ա���Ը�ֵ�������ڴ�
		testSamples = new Sample[TEST_NUM]();
		//�������� 
		for (int i = 0; i < TEST_NUM; ++i) {
			//����һ��ͼƬ���ݲ��� 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < MNIST_ROW; ++r) {
				for (int c = 0; c < MNIST_COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * MNIST_ROW * MNIST_COL + MNIST_COL * r + c];
					testSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//��һ����[0,1]
				}
			}
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}
}

void loadTestLabel() {
	ifstream file(TEST_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 8 + TEST_NUM; //test label�еı�ǩ���ݴӵ�8�ֽڿ�ʼ
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//�����ǩ����
		unsigned char label = 0;
		for (int i = 0; i < TEST_NUM; ++i) {
			label = (unsigned char)buffer[i + 8];
			testSamples[i].label = (double)label;
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}
}

void delMnist()
{
	if (trainSamples != NULL) {
		delete[] trainSamples;
	}
	if (testSamples != NULL) {
		delete[] testSamples;
	}
}




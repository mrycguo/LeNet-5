#include <iostream>
#include <fstream>
#include <ctime>

//大小比较宏定义
#ifndef MIN
#define MIN(A,B)	(((A) < (B)) ? (A) : (B))
#endif

#ifndef MAX
#define MAX(A,B)	(((A) > (B)) ? (A) : (B))
#endif

//训练数据存放路径 mnist数据集路径
#define TRAIN_DATA_PATH "./mnist/train-images.idx3-ubyte"
#define TRAIN_LABEL_PATH "./mnist/train-labels.idx1-ubyte"
#define TEST_DATA_PATH "./mnist/t10k-images.idx3-ubyte"
#define TEST_LABEL_PATH "./mnist/t10k-labels.idx1-ubyte"

//数据集的训练/测试数量划分
#define TRAIN_NUM 60000
#define TEST_NUM 10000

//mnist数据集shape
#define MNIST_ROW 28
#define MNIST_COL 28

//Lenet5模型要求数据输入层为32*32
#define INPUT_ROW 32
#define INPUT_COL 32

using namespace std;

//模型训练数据的结构体，包括数据和标签
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


//超参数
const int batchSize = 10;
const double learningRate = 0.03;
const int epochs = 3;
Sample *trainSamples, *testSamples;




//数据读取函数
void loadMnist();
int ReverseInt(int);		//大端小端转换
void loadTrainData();
void loadTrainLabel();
void loadTestData();
void loadTestLabel();
void delMnist();

//激活函数
struct activation_func {
	/* scale: -0.8 ~ 0.8 和label初始值对应 */
	inline static double tan_h(double val) {
		double ep = exp(val);
		double em = exp(-val);

		return (ep - em) / (ep + em);
	}

	inline static double dtan_h(double val) {
		return 1.0 - val * val;
	}

	/* scale: 0.1 ~ 0.9 和label初始值对应 */
	inline static double relu(double val) {
		return val > 0.0 ? val : 0.0;
	}

	inline static double drelu(double val) {
		return val > 0.0 ? 1.0 : 0.0;
	}

	/* scale: 0.1 ~ 0.9 和label初始值对应 */
	inline double sigmoid(double val) {
		return 1.0 / (1.0 + exp(-val));
	}

	inline double dsigmoid(double val) {
		return val * (1.0 - val);
	}
};

//损失函数 均方差损失函数
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
		//将文件读入内存buffer中
		int sz = 16 + MNIST_ROW * MNIST_COL * TRAIN_NUM; //train data中的图像数据从第16字节开始
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//成员属性赋值及分配内存
		trainSamples = new Sample[TRAIN_NUM]();
		//处理数据 
		for (int i = 0; i < TRAIN_NUM; ++i) {
			//读入一个图片数据并作 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < MNIST_ROW; ++r) {
				for (int c = 0; c < MNIST_COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * MNIST_ROW * MNIST_COL + MNIST_COL * r + c];
					trainSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//归一化到[0,1]
				}
			}
		}
		//释放内存
		delete[] buffer;
	}
}

void loadTrainLabel() {
	ifstream file(TRAIN_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 8 + TRAIN_NUM; //train label中的标签数据从第8字节开始
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//读入标签数据
		unsigned char label = 0;
		for (int i = 0; i < TRAIN_NUM; ++i) {
			label = (unsigned char)buffer[i + 8];
			trainSamples[i].label = (double)label;
		}
		//释放内存
		delete[] buffer;
	}
}

void loadTestData() {
	ifstream file(TEST_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 16 + MNIST_ROW * MNIST_COL * TEST_NUM; //TEST data中的图像数据从第16字节开始
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//成员属性赋值及分配内存
		testSamples = new Sample[TEST_NUM]();
		//处理数据 
		for (int i = 0; i < TEST_NUM; ++i) {
			//读入一个图片数据并作 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < MNIST_ROW; ++r) {
				for (int c = 0; c < MNIST_COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * MNIST_ROW * MNIST_COL + MNIST_COL * r + c];
					testSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//归一化到[0,1]
				}
			}
		}
		//释放内存
		delete[] buffer;
	}
}

void loadTestLabel() {
	ifstream file(TEST_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 8 + TEST_NUM; //test label中的标签数据从第8字节开始
		char* buffer = new char[sz]();
		file.read(buffer, sz);
		//读入标签数据
		unsigned char label = 0;
		for (int i = 0; i < TEST_NUM; ++i) {
			label = (unsigned char)buffer[i + 8];
			testSamples[i].label = (double)label;
		}
		//释放内存
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




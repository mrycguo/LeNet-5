#include "DataReader.h"
/*
#include <iostream>
#include <fstream>

using namespace std;

DataReader::DataReader()
{
	trainNum = 0;
	trainSamples = NULL;
	testNum = 0;
	testSamples = NULL;
}

DataReader::~DataReader()
{
	trainNum = 0;
	if (trainSamples != NULL) {
		delete[] trainSamples;
	}
	testNum = 0;
	if (testSamples != NULL) {
		delete[] testSamples;
	}
}

void DataReader::loadMnist()
{
	loadTrainData();
	loadTrainLabel();
	loadTestData();
	loadTestLabel();
}

void DataReader::loadTrainData() {
	ifstream file(TRAIN_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 16 + ROW * COL * TRAIN_NUM; //train data�е�ͼ�����ݴӵ�16�ֽڿ�ʼ
		char* buffer = new char[sz];
		file.read(buffer,sz);
		//��Ա���Ը�ֵ�������ڴ�
		this->trainNum = TRAIN_NUM;
		this->trainSamples = new Sample[TRAIN_NUM];
		//�������� 
		for (int i = 0; i < TRAIN_NUM; ++i) {
			//����һ��ͼƬ���ݲ��� 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < ROW; ++r) {
				for (int c = 0; c < COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * ROW * COL + COL * r + c];
					trainSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//��һ����[0,1]
				}
			}
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}
}

void DataReader::loadTrainLabel() {
	ifstream file(TRAIN_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 8 + TRAIN_NUM; //train label�еı�ǩ���ݴӵ�8�ֽڿ�ʼ
		char* buffer = new char[sz];
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

void DataReader::loadTestData() {
	ifstream file(TEST_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 16 + ROW * COL * TEST_NUM; //TEST data�е�ͼ�����ݴӵ�16�ֽڿ�ʼ
		char* buffer = new char[sz];
		file.read(buffer, sz);
		//��Ա���Ը�ֵ�������ڴ�
		this->testNum = TEST_NUM;
		this->testSamples = new Sample[TEST_NUM];
		//�������� 
		for (int i = 0; i < TEST_NUM; ++i) {
			//����һ��ͼƬ���ݲ��� 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < ROW; ++r) {
				for (int c = 0; c < COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * ROW * COL + COL * r + c];
					testSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//��һ����[0,1]
				}
			}
		}
		//�ͷ��ڴ�
		delete[] buffer;
	}

}

void DataReader::loadTestLabel() {
	ifstream file(TEST_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//���ļ������ڴ�buffer��
		int sz = 8 + TEST_NUM; //test label�еı�ǩ���ݴӵ�8�ֽڿ�ʼ
		char* buffer = new char[sz];
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
*/
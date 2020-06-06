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
		//将文件读入内存buffer中
		int sz = 16 + ROW * COL * TRAIN_NUM; //train data中的图像数据从第16字节开始
		char* buffer = new char[sz];
		file.read(buffer,sz);
		//成员属性赋值及分配内存
		this->trainNum = TRAIN_NUM;
		this->trainSamples = new Sample[TRAIN_NUM];
		//处理数据 
		for (int i = 0; i < TRAIN_NUM; ++i) {
			//读入一个图片数据并作 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < ROW; ++r) {
				for (int c = 0; c < COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * ROW * COL + COL * r + c];
					trainSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//归一化到[0,1]
				}
			}
		}
		//释放内存
		delete[] buffer;
	}
}

void DataReader::loadTrainLabel() {
	ifstream file(TRAIN_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 8 + TRAIN_NUM; //train label中的标签数据从第8字节开始
		char* buffer = new char[sz];
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

void DataReader::loadTestData() {
	ifstream file(TEST_DATA_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 16 + ROW * COL * TEST_NUM; //TEST data中的图像数据从第16字节开始
		char* buffer = new char[sz];
		file.read(buffer, sz);
		//成员属性赋值及分配内存
		this->testNum = TEST_NUM;
		this->testSamples = new Sample[TEST_NUM];
		//处理数据 
		for (int i = 0; i < TEST_NUM; ++i) {
			//读入一个图片数据并作 0 padding
			unsigned char pixel = 0;
			for (int r = 0; r < ROW; ++r) {
				for (int c = 0; c < COL; ++c) {
					pixel = (unsigned char)buffer[16 + i * ROW * COL + COL * r + c];
					testSamples[i].data[(r + 2) * INPUT_COL + (c + 2)] = (double)pixel / 255;//归一化到[0,1]
				}
			}
		}
		//释放内存
		delete[] buffer;
	}

}

void DataReader::loadTestLabel() {
	ifstream file(TEST_LABEL_PATH, ios::binary);
	if (file.is_open()) {
		//将文件读入内存buffer中
		int sz = 8 + TEST_NUM; //test label中的标签数据从第8字节开始
		char* buffer = new char[sz];
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
*/
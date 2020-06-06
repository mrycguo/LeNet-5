#include "Lenet.h"
#include <iostream>

/*
using namespace std;

Lenet::Lenet()
{
	trainNum = 0;
	trainSamples = NULL;
	testNum = 0;
	testSamples = NULL;
}

Lenet::~Lenet()
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

void Lenet::feedTrainData(Sample * trainData, int trainNum){
	this->trainSamples = trainData;		//偷懒，没有写成memcpy的形式
	this->trainNum = trainNum;
}

void Lenet::feedTestData(Sample * testData, int testNum){
	this->testSamples = testData;
	this->testNum = testNum;
}

void Lenet::train()
{

}

void Lenet::predict()
{
}

*/
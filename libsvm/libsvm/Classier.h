#pragma once
#include "svm.h"
class Classier
{
public:
	Classier();
	~Classier();

	void setParam();
	void train(double** dataset, double* labels);
	void predict(const char* filePath, double** dataset, double* res);
	void getAccuracy(double* labels, double* res);


	int getTrainNum() const { return TrainNum; }
	void setTrainNum(int val) { TrainNum = val; }

	int getTestNum() const { return TestNum; }
	void setTestNum(int val) { TestNum = val; }


private:
	void readData(const char* datPpath,const char* labelPath,double** dataset,double *labels);
	

	svm_problem svm;
	svm_parameter param;
	svm_model*svmModel;

	int TrainNum;
	
	int TestNum;
	

};


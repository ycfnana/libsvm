// libsvm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Classier.h"
#define TrainNum 2115048
double** dataset;
double* labels;
int _tmain(int argc, _TCHAR* argv[])
{
	dataset = new double*[TrainNum];
	for (int idx = 0; idx < TrainNum; idx++){
		dataset[idx] = new double[16];
	}
	labels = new double[TrainNum];

	Classier *cla = new Classier();
	cla->setTrainNum(TrainNum);
	cla->setParam();
	cla->train(dataset, labels);
	
	return 0;
}


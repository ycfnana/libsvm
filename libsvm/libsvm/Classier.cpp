#include "stdafx.h"

#include "Classier.h"
#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <vector>  
using namespace std;

Classier::Classier()
{
	
}


Classier::~Classier()
{
}

void Classier::setParam()
{
	param.svm_type = C_SVC;
	param.kernel_type = RBF;
	param.degree = 3;
	param.gamma = 0.5;
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 40;
	param.C = 500;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	// param.probability = 0;
	param.nr_weight = 0;
	param.weight = NULL;
	param.weight_label = NULL;
}

void Classier::train(double** dataset, double* labels)
{
	const char* datapath = "F:/cuModelDecision3/train_data.csv";
	const char* labelspath = "F:/cuModelDecision3/labels.csv";
	readData(datapath, labelspath, dataset, labels);
	svm.l = TrainNum;
	svm_node* features = new svm_node[17];
	svm.x = new svm_node*[svm.l];
	svm.y = new double[svm.l];
	for (int idx = 0; idx < svm.l; idx++){
		for (int i = 0; i < 17; i++){
			features[i].index = i + 1;
			features[i].value = dataset[idx][i];
		}
		features[16].index = -1;
		svm.x[idx] = features;
		svm.y[idx] = labels[idx];
	}


	svmModel = svm_train(&svm, &param);

	svm_save_model("F:/111/libsvm.txt", svmModel);

}

void Classier::predict(const char* filePath, double** dataset, double* res)
{
	svm_model* model = svm_load_model(filePath);
	for (int idx = 0; idx < TestNum; idx++){
		svm_node* feature = new svm_node[17];
		for (int i = 0; i < 17; i++){
			feature[i].index = i + 1;
			feature[i].value = dataset[idx][i];
		}
		feature[17].index = -1;
		res[idx] = svm_predict(model, feature);

	}


}

void Classier::getAccuracy(double* labels, double* res)
{
	double err = 0.0;
	for (int idx = 0; idx < TestNum; idx++){
		if (labels[idx] != res[idx]){
			err++;
		}
	}
	double accuracy = 1 - (err / (1.0*TestNum));
	cout << "err rate is "<<accuracy << endl;

}

void Classier::readData(const char* dataPath,const char* labelPath,double** dataset, double *labels)
{
	ifstream dataFile(dataPath);
	ifstream labelsFile(labelPath);
	string line;
	int i = 0;
	int index = 0;
	while (getline(dataFile, line)){

		

			istringstream sin(line); 
			vector<string> fields; 
			string field;
			int j = 0;

			while (getline(sin, field, ',')) 
			{
				dataset[index][j] = atoi(field.c_str());
				j++;
			}
			index++;
		




		i++;


	}
	i = 0;
	index = 0;
	while (getline(labelsFile, line)){

		
			if (line.compare("True")){
				labels[index] = 1;
			}
			else{
				labels[index] = 0;
			}
			index++;
		i++;
	}

	dataFile.close();
	labelsFile.close();
}

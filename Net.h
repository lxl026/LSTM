#pragma once
#include "Layer.h"
#include "config.h"
#include <string>
#include <iostream> 
#include <fstream>  
#include <sstream>  
using namespace std;

class Net
{
public:

	Net(int inputRow, int inputCol, int* nodeNum, int depth, char* weightFileName);

	~Net();

	void Predict(double(*inputMatrix)[MAXPOINTNUM], double(*outputtMatrix)[MAXPOINTNUM]);
private:

	void GetWeigtParameter(char* weightFileName);

	Layer* L;

	int inputRow;
	int inputCol;
	int deepth;

};

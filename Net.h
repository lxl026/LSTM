#pragma once
#include "Layer.h"
#include <string>
#include <iostream>  
#include <fstream>  
#include <sstream>  
using namespace std;

const int MAXINPUTLEN = 1024;

class Net
{
public:

	/*
	预测时网络输入为矩阵
	inputRow，inputCol分别为输入的行数和列数，列数不可超过MAXINPUTLEN（32）
	nodeNum是一个一维数组，表示各个隐藏层的节点个数，亦即输出向量的长度
	depth是数组的长度，也是LSTM网络的层数
	weightFileName为存储权重的文件名，按照Wf、Wi、Wc、Wo的顺序排列，矩阵的每一行占一行，每个数字后面都会带‘,’
	默认不考虑bias，如果有bias，则放在对应权重的最后面
	*/
	Net(int inputRow,int inputCol,int* nodeNum,int depth,char* weightFileName);

	~Net();

	/*
	预测的输入输出都为矩阵
	//输入矩阵大小见构造函数参数
	输出矩阵的行数与输入矩阵的行数相同，列数与最后一层的输出矩阵的输出向量长度相同
	*/
	void Predict(double (*inputMatrix)[MAXINPUTLEN], double(*outputtMatrix)[MAXINPUTLEN]);

private:

	//从文件读取权重
	void GetWeigtParameter(char* weightFileName);

	Layer* L;//网络数组指针

	int inputRow;//输入的行数
	int inputCol;//输入的列数
	int deepth;//LSTM网络深度，即不考虑输入层输出层后的网络层数

};


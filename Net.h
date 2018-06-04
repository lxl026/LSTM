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
	Ԥ��ʱ��������Ϊ����
	inputRow��inputCol�ֱ�Ϊ������������������������ɳ���MAXINPUTLEN��32��
	nodeNum��һ��һά���飬��ʾ�������ز�Ľڵ�������༴��������ĳ���
	depth������ĳ��ȣ�Ҳ��LSTM����Ĳ���
	weightFileNameΪ�洢Ȩ�ص��ļ���������Wf��Wi��Wc��Wo��˳�����У������ÿһ��ռһ�У�ÿ�����ֺ��涼�����,��
	Ĭ�ϲ�����bias�������bias������ڶ�ӦȨ�ص������
	*/
	Net(int inputRow,int inputCol,int* nodeNum,int depth,char* weightFileName);

	~Net();

	/*
	Ԥ������������Ϊ����
	//��������С�����캯������
	����������������������������ͬ�����������һ������������������������ͬ
	*/
	void Predict(double (*inputMatrix)[MAXINPUTLEN], double(*outputtMatrix)[MAXINPUTLEN]);

private:

	//���ļ���ȡȨ��
	void GetWeigtParameter(char* weightFileName);

	Layer* L;//��������ָ��

	int inputRow;//���������
	int inputCol;//���������
	int deepth;//LSTM������ȣ����������������������������

};


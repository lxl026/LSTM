#pragma once

const int MAX = 1024;

class Layer
{
public:

	Layer();

	//层的初始化函数，初始化输入输出向量的长度
	void Init(int inputLen, int outputLen);

	~Layer();
	int inputLen;//输入长度
	int outputLen;//输出长度

	//各权重矩阵
	double Wf[MAX * 2 + 1][MAX];//遗忘门
	double Wi[MAX * 2 + 1][MAX];//输入门
	double Wc[MAX * 2 + 1][MAX];//新记忆
	double Wo[MAX * 2 + 1][MAX];//输出门

	double h[MAX * 2];//前部分为层的输出，为了方便矩阵运算，将h和输入向量x合并

	void LayerOutput(double inputVector[], bool isFirst, double* output);

private:
	
	double c[MAX];
	double cHat[MAX];
	double f[MAX];
	double i[MAX];
	double o[MAX];
	void Cal_f();
	void Cal_i();
	void Cal_cHat();
	void Cal_c();
	void Cal_o();
	void Cal_h();
	
};


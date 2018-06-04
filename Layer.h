#pragma once

const int MAX = 1024;

class Layer
{
public:

	Layer();

	//��ĳ�ʼ����������ʼ��������������ĳ���
	void Init(int inputLen, int outputLen);

	~Layer();
	int inputLen;//���볤��
	int outputLen;//�������

	//��Ȩ�ؾ���
	double Wf[MAX * 2 + 1][MAX];//������
	double Wi[MAX * 2 + 1][MAX];//������
	double Wc[MAX * 2 + 1][MAX];//�¼���
	double Wo[MAX * 2 + 1][MAX];//�����

	double h[MAX * 2];//ǰ����Ϊ��������Ϊ�˷���������㣬��h����������x�ϲ�

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


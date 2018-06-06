#pragma once
#include "config.h"

class Layer
{
public:

	Layer();

	void Init(int inputLen, int outputLen);

	~Layer();
	int inputLen;
	int outputLen;

				 
	double Wf[(MAXPOINTNUM * 2 + 1)*MAXPOINTNUM];
	double Wi[(MAXPOINTNUM * 2 + 1)*MAXPOINTNUM];
	double Wc[(MAXPOINTNUM * 2 + 1)*MAXPOINTNUM];
	double Wo[(MAXPOINTNUM * 2 + 1)*MAXPOINTNUM];

	double h[MAXPOINTNUM * 2];

	void LayerOutput(double inputVector[], bool isFirst, double* output);

private:

	double c[MAXPOINTNUM];
	double cHat[MAXPOINTNUM];
	double f[MAXPOINTNUM];
	double i[MAXPOINTNUM];
	double o[MAXPOINTNUM];
	void Cal_f();
	void Cal_i();
	void Cal_cHat();
	void Cal_c();
	void Cal_o();
	void Cal_h();
	
};


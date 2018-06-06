#include "Layer.h"
#include "math.h"
#include<iostream>
#include <string.h>
#include <thread>
using namespace std;
#define _BIAS
#define MULTHREAD
 
double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

void matrixCal(double *res, double *array, double *vec1, int r, int c)
{
	for (int i = 0; i < c; i++)
	{
		res[i] = 0.0;
		for (int j = 0; j < r; j++)
		{
			res[i] += vec1[j] * array[i*r+j];
		}
	}
}

Layer::Layer()
{
	
}

void Layer::Init(int inputLen, int outputLen)
{
	this->inputLen = inputLen;
	this->outputLen = outputLen;
}

Layer::~Layer()
{
}

void Layer::Cal_c()
{
	for (int k = 0; k < outputLen; k++)
	{
		c[k] = f[k] * c[k] + i[k] * cHat[k];
	}
}

void Layer::Cal_h()
{
	for (int k = 0; k < outputLen; k++)
	{
		h[k] = o[k] * tanh(c[k]);
	}
}

void Layer::LayerOutput(double inputVector[], bool isFirst, double* outputVector)
{
	if (isFirst)
	{
		memset(c, 0, outputLen);
		memset(h, 0, outputLen);
	}

	for (int i = 0; i < inputLen; i++) 
		h[outputLen + i] = inputVector[i];
#ifdef MULTHREAD
	thread threads[4];
	threads[0] = thread(matrixCal, f, Wf, h, outputLen + inputLen, outputLen);
	threads[1] = thread(matrixCal, i, Wi, h, outputLen + inputLen, outputLen);
	threads[2] = thread(matrixCal, cHat, Wc, h, outputLen + inputLen, outputLen);
	threads[3] = thread(matrixCal, o, Wo, h, outputLen + inputLen, outputLen);
	threads[0].join();
	threads[1].join();
	threads[2].join();
	threads[3].join();
	for (int ii = 0; ii < outputLen; ii++)
	{
		/*f[ii] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
		f[ii] += h[j] * Wf[j][ii];
		}*/
#ifdef BIAS
		f[i] += Wf[outputLen + inputLen];
		i[k] += Wi[outputLen + inputLen];
		c[k] += Wc[outputLen + inputLen];
		o[k] += Wo[outputLen + inputLen];
#endif
		f[ii] = sigmoid(f[ii]);
		i[ii] = sigmoid(i[ii]);
		cHat[ii] = sigmoid(cHat[ii]);
		o[ii] = sigmoid(o[ii]);
	}
	Cal_c();
	Cal_h();
#else

	matrixCal(f, Wf, h, outputLen + inputLen, outputLen);
	matrixCal(i, Wi, h, outputLen + inputLen, outputLen);
	matrixCal(cHat, Wc, h, outputLen + inputLen, outputLen);
	matrixCal(o, Wo, h, outputLen + inputLen, outputLen);

	for (int ii = 0; ii < outputLen; ii++)
	{
		/*f[ii] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
		f[ii] += h[j] * Wf[j][ii];
		}*/
#ifdef BIAS
		f[i] += Wf[outputLen + inputLen];
		i[k] += Wi[outputLen + inputLen];
		c[k] += Wc[outputLen + inputLen];
		o[k] += Wo[outputLen + inputLen];
#endif
		f[ii] = sigmoid(f[ii]);
		i[ii] = sigmoid(i[ii]);
		cHat[ii] = sigmoid(cHat[ii]);
		o[ii] = sigmoid(o[ii]);
	}
	Cal_c();
	Cal_h();
#endif // MULTHREAD

	
	for (int i = 0; i < outputLen; i++) 
		outputVector[i] = h[i];
}

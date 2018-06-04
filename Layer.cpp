#include "Layer.h"
#include "math.h"
#include<iostream>
#include <thread>
using namespace std;
#define _BIAS
//#define MULPROCESS
 
double sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
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

void Layer::Cal_f()
{
	
	for (int i = 0; i < outputLen; i++)
	{
		f[i] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
			f[i] += h[j] * Wf[j][i];
		}
#ifdef BIAS
		f[i] += Wf[outputLen + inputLen];
#endif
		f[i] = sigmoid(f[i]);
	}
}

void Layer::Cal_i()
{
	for (int k = 0; k < outputLen; k++)
	{
		i[k] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
			i[k] += h[j] * Wi[j][k];
		}
#ifdef BIAS
		i[k] += Wi[outputLen + inputLen];
#endif
		i[k] = sigmoid(i[k]);
	}

}

void Layer::Cal_cHat()
{

	for (int i = 0; i < outputLen; i++)
	{
		cHat[i] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
			cHat[i] += h[j] * Wc[j][i];
		}
#ifdef BIAS
		cHat[i] += Wc[outputLen + inputLen];
#endif
		cHat[i] = sigmoid(cHat[i]);
	}
}


void Layer::Cal_c()
{

	for (int k = 0; k < outputLen; k++)
	{
		c[k] = f[k] * c[k] + i[k] * cHat[k];
	}
}

void Layer::Cal_o()
{
	for (int i = 0; i < outputLen; i++)
	{
		o[i] = 0;
		for (int j = 0; j < outputLen + inputLen; j++)
		{
			o[i] += h[j] * Wo[j][i];
		}
#ifdef BIAS
		o[i] += Wo[outputLen + inputLen];
#endif
		o[i] = sigmoid(o[i]);
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
	if (isFirst)//ʱ�еĵ�һ�����룬c��hӦ����0
	{
		for (int i = 0; i < outputLen; i++)
		{
			c[i] = 0;
			h[i] = 0;
		}
	}

	for (int i = 0; i < inputLen; i++) 
		h[outputLen + i] = inputVector[i];//������x�����ϲ���h֮�󣬱��ھ�������
#ifdef MULPROCESS
/*
	thread threads[3];
	threads[0] = thread(&Layer::Cal_f, this);
  threads[1] = thread(&Layer::Cal_i, this);
	threads[2] = thread(&Layer::Cal_o, this);
	threads[0].detach();
	threads[1].detach();
  threads[2].detach();
	Cal_cHat();
	Cal_c();
	Cal_h();
 */
  thread t(&Layer::Cal_o, this);
  t.join();
  Cal_f();
	Cal_i();
	Cal_cHat();
	Cal_c();
	Cal_h();
#else
	Cal_f();
	Cal_i();
	Cal_cHat();
	Cal_c();
	Cal_o();
	Cal_h();
#endif // MULPROCESS

	
	for (int i = 0; i < outputLen; i++) 
		outputVector[i] = h[i];
}

#include <celero/Celero.h>
#include <algorithm>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <ivec.h>//MMX
#include <fvec.h>//SSE(also include ivec.h)
#include <dvec.h>//SSE2(also include fvec.h)

using namespace Eigen; 
using namespace std;

#define row 1024
#define col 256
#define thread_num 4
#define Each 64
CELERO_MAIN

class TestFixture : public celero::TestFixture
{
public:
	TestFixture()
	{
		Wf1D = new double[row*col];
		// f = new double[col];
		// h = new double[row];
	}
	~TestFixture(){
		delete[] Wf1D;
		// delete[] f;
		// delete[] h;
	}

	// Before each sample
	virtual void setUp(int64_t experimentValue) override
	{
		
		
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < col; j++)
			{
				 Wf1D[i*col+j] = Wf1D2[i*col+j] = WfT[j][i] = Wf[i][j] = (double)rand()/RAND_MAX;
			}
		}

		for(int i = 0; i < row; i++)
		{
			h[i] = (double)rand()/RAND_MAX;
		}

		for(int i = 0; i < col; i++)
		{
			f[i] = (double)rand()/RAND_MAX;
		}

	}

	// Before each Experiment
	virtual void onExperimentStart(int64_t) override
	{
		
	}

	// After each Experiment
	virtual void onExperimentEnd() override
	{
		
		
	}

	// After each sample
	virtual void tearDown() override
	{
		
	}

	double f[col];//陆谩鹿没
	double h[row];
	// double *f;
	// double *h;

	double Wf[row][col];

	double WfT[col][row];

	double* Wf1D;
	double Wf1D2[col*row];

};

static const int SamplesCount = 100;
static const int IterationsCount = 2;


BASELINE_F(Matrix, default, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < col; i++)
	{
		f[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			f[i] += h[j] * Wf[j][i];
		}
	}
	
}


BENCHMARK_F(Matrix, Transposition, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < col; i++)
	{
		f[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			f[i] += h[j] * WfT[i][j];
		}
	}
}

BENCHMARK_F(Matrix, Continuty, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(i==0) f[j] = 0.0;
			f[j] += h[i] * Wf[i][j];
		}
	}
}

BENCHMARK_F(Matrix, Dimension, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < col; i++)
	{
		f[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			f[i] += h[j] * Wf1D[j*col+i];
		}

	}

}

BENCHMARK_F(Matrix, Dimension_Transposition, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < col; i++)
	{
		f[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			f[i] += h[j] * Wf1D[i*row+j];
		}
	}
}

void Dt_test(double *res,double *array,double *vec1,int r,int c)
{
	for (int i = 0; i < c; i++)
	{
		res[i] = 0.0;
		for (int j = 0; j < r; j++)
		{
			res[i] += vec1[j] * array[i*row+j];
		}
	}
}
BENCHMARK_F(Matrix, Dt_test, TestFixture, IterationsCount, SamplesCount)
{
	Dt_test(f,Wf1D,h,row,col);

}


BENCHMARK_F(Matrix, Dt_test2, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < col; i++)
	{
		f[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			f[i] += h[j] * Wf1D2[i*row+j];
		}
	}
}
BENCHMARK_F(Matrix, Dt_test3, TestFixture, IterationsCount, SamplesCount)
{
	Dt_test(f,Wf1D2,h,row,col);

}
BENCHMARK_F(Matrix, Dimension_Continuty, TestFixture, IterationsCount, SamplesCount)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(i==0) f[j] = 0.0;
			f[j] += h[i] * Wf1D[i*col+j];
		}
	}
}

BENCHMARK_F(Matrix, SIMD_Transposition, TestFixture, IterationsCount, SamplesCount)
{
	F32vec4 *tmp1 = (F32vec4 *)h;
	F32vec4 sum;
	for(int i=0; i<col; i++)
	{
		f[i]=0.0f;
		F32vec4 *tmp = (F32vec4 *)(WfT[i]);
		for(int j=0; j<row/4; j++)
		{
			sum=tmp[j]*tmp1[j];
			f[i]+=sum[0]+sum[1]+sum[2]+sum[3];
		}
		if(row/4*4!=row)
		{
			for(int j=row/4*4;j<row;j++)
			{
				f[i]+=WfT[j][i]*h[j];
			}
		}
	}
}

void nTread_DT(double *res,double *array,double *vec1,int start,int end)
{
	for (int i = start; i < end; i++)
	{
		res[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			res[i] += vec1[j] * array[i*row+j];
		}
	}
}

BENCHMARK_F(Matrix, nThread_DT, TestFixture, IterationsCount, SamplesCount)
{
	thread threads[thread_num];
	
    for(int i=0; i<thread_num; i++){
        threads[i]=thread(nTread_DT,f,Wf1D,h,i*Each,(i+1)*Each);
    }
    for(auto& t : threads){
        t.join();
    }

}
void nTread_T(double *res,double (*array)[row],double *vec1,int start,int end)
{
	for (int i = start; i < end; i++)
	{
		res[i] = 0.0;
		for (int j = 0; j < row; j++)
		{
			res[i] += vec1[j] * array[i][j];
		}
	}
}
BENCHMARK_F(Matrix, nThread_T, TestFixture, IterationsCount, SamplesCount)
{
	thread threads[thread_num];
	
    for(int i=0; i<thread_num; i++){
        threads[i]=thread(nTread_DT,f,Wf1D2,h,i*Each,(i+1)*Each);
    }
    for(auto& t : threads){
        t.join();
    }

}
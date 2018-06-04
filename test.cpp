#include "test.h"
#include "iostream"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "vector"
#include "assert.h"
#include "TimeCalcultion.h"
using namespace std;

#define innode  2       //����������������2������
#define hidenode  26    //���ؽ�������洢��Я��λ��?
#define outnode  1      //���������������һ��Ԥ������?
#define alpha  0.1      //ѧϰ����
#define binary_dim 8    //������������󳤶�?

#define randval(high) ( (double)rand() / RAND_MAX * high )
#define uniform_plus_minus_one ( (double)( 2.0 * rand() ) / ((double)RAND_MAX + 1.0) - 1.0 )  //��������ֲ�?


int largest_number = (pow(2, binary_dim));  //����������󳤶ȶ�Ӧ�Ŀ��Ա�ʾ�����ʮ������

											//��һ��10��������ת��Ϊ2������
void int2binary(int n, int *arr)
{
	int i = 0;
	while (n)
	{
		arr[i++] = n % 2;
		n /= 2;
	}
	while (i < binary_dim)
		arr[i++] = 0;
}

test::test()
{
	
}

void test::fun()
{
	int nodeNum[1] = { 32 };
  char fileName[12];
  strcpy(fileName,"weight.csv");
	Net testNet(8,2, nodeNum, 1, fileName);
	TimeCalcultion timec;
	for (int i = 0; i < 1000000; i++)
	{
		int a_int = (int)randval(largest_number / 2.0);  //�������һ������?a
		int a[binary_dim];
		int2binary(a_int, a);                 //תΪ��������

		int b_int = (int)randval(largest_number / 2.0);  //���������һ������?b
		int b[binary_dim];
		int2binary(b_int, b);                 //תΪ��������


		int c_int = a_int + b_int;            //��ʵ�ĺ� c
		int c[binary_dim];
		int2binary(c_int, c);                 //תΪ��������

		double input[8][1024];
		for (int j = 0; j < 8; j++)
		{
			input[j][0] = a[j];
			input[j][1] = b[j];
		}

		double output[8][1024];

		timec.Start();
		testNet.Predict(input,output);
		timec.End();

		double W_out[26] = { -0.82149,-3.18744,1.5325,-4.18416,11.9961,-0.733455,-3.89614,-2.12248,9.98977,-2.60765,-3.18115,-4.31643,-4.35058,-2.77191,-1.19539,-2.31951,0.205476,0.559464,0.33883,-0.57547,-2.83563,-1.69292,1.11119,-2.10913,-6.63332,-1.73419 };

		int predict[8];
		for (int j = 0; j < 8; j++)
		{
			double out = 0;
			for (int k = 0; k<hidenode; k++)
				out += output[j][k] * W_out[k];
			out = 1.0 / (1.0 + exp(-out));
			predict[j] = (int)floor(out + 0.5);
		}
		
		int out = 0;
		/*for (int k = binary_dim - 1; k >= 0; k--)
			out += predict[k] * pow(2, k);

		cout << "pred:";
		for (int k = binary_dim - 1; k >= 0; k--)
			cout << predict[k];
		cout << endl;

		cout << "true:";
		for (int k = binary_dim - 1; k >= 0; k--)
			cout << c[k];
		cout << endl;
		
		cout << a_int << " + " << b_int << " = " << out << endl;
		*/

	}
	timec.Show();
	
}


test::~test()
{
}

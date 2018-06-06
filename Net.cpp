#include "Net.h"

Net::Net(int inputRow, int inputCol, int * nodeNum, int deepth, char* weightFileName):inputRow(inputRow), inputCol(inputCol), deepth(deepth)
{
	this->inputRow = inputRow;
	this->inputCol = inputCol;
	this->deepth = deepth;

	L = new Layer[deepth];

	for (int i = 0; i < deepth; i++)
	{
		if (i == 0) L[i].Init(inputCol, nodeNum[i]);//��һ���������������Ϊ������������

		else L[i].Init(nodeNum[i - 1], nodeNum[i]);
	}

	GetWeigtParameter(weightFileName);
}

void Net::GetWeigtParameter(char* weightFileName)
{
	ifstream fin(weightFileName);
	string line;
	for (int i = 0; i < this->deepth; i++)
	{
		int c = L[i].outputLen + L[i].inputLen;
		for (int j = 0; j < c; j++)//��ȡWf
		{
			getline(fin, line);
			istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
			string field;
			int k = 0;
			while(getline(sin, field, ','))
			{
				
				stringstream ss;
				ss << field;
				ss >> L[i].Wf[k * c + j];
				k++;
			}
		}
		for (int j = 0; j < c; j++)
		{
			getline(fin, line);
			istringstream sin(line); 
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wi[k * c + j];
				k++;
			}
		}
		for (int j = 0; j < c; j++)//��ȡWc
		{
			getline(fin, line);
			istringstream sin(line);
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wc[k * c + j];
				k++;
			}
		}
		for (int j = 0; j < c; j++)//��ȡWo
		{
			getline(fin, line);
			istringstream sin(line); 
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wo[k * c + j];
				k++;
			}
		}
	}
	fin.close();
	
}

void Net::Predict(double(*inputMatrix)[MAXPOINTNUM], double(*outputtMatrix)[MAXPOINTNUM])
{

	for (int i = 0; i < inputRow; i++)
	{
		bool isFirst = false;
		if (i == 0) isFirst = true;//ʱ��ĵ�һ�����룬isFirstΪtrue���ø����c��h��Ҫ��0
		
		for (int j = 0; j < deepth; j++) 
		{
			if(j==0) L[j].LayerOutput(inputMatrix[i], isFirst, outputtMatrix[i]);//j==0,����Ӿ����ȡ���������һ��������ȡ
			else L[j].LayerOutput(outputtMatrix[i], isFirst, outputtMatrix[i]);
		}
	}
}

Net::~Net()
{
	delete []L;
}

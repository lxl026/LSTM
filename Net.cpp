#include "Net.h"

Net::Net(int inputRow, int inputCol, int * nodeNum, int deepth, char* weightFileName)
{
	this->inputRow = inputRow;
	this->inputCol = inputCol;
	this->deepth = deepth;

	L = new Layer[deepth];

	for (int i = 0; i < deepth; i++)
	{
		if (i == 0) L[i].Init(inputCol, nodeNum[i]);//第一层的输入向量长度为输入矩阵的行数

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
		for (int j = 0; j < L[i].outputLen + L[i].inputLen; j++)//读取Wf
		{
			getline(fin, line);
			istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
			string field;
			int k = 0;
			while(getline(sin, field, ','))
			//for (int k = 0; k < L[i].outputLen; k++)
			{
				
				stringstream ss;
				ss << field;
				ss >> L[i].Wf[j][k++];
			}
		}
		for (int j = 0; j < L[i].outputLen + L[i].inputLen; j++)//读取Wi
		{
			getline(fin, line);
			istringstream sin(line); 
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wi[j][k++];
			}
		}
		for (int j = 0; j < L[i].outputLen + L[i].inputLen; j++)//读取Wc
		{
			getline(fin, line);
			istringstream sin(line);
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wc[j][k++];
			}
		}
		for (int j = 0; j < L[i].outputLen + L[i].inputLen; j++)//读取Wo
		{
			getline(fin, line);
			istringstream sin(line); 
			string field;
			int k = 0;
			while (getline(sin, field, ','))
			{
				stringstream ss;
				ss << field;
				ss >> L[i].Wo[j][k++];
			}
		}
	}
	fin.close();
	
}

void Net::Predict(double(*inputMatrix)[MAXINPUTLEN], double(*outputtMatrix)[MAXINPUTLEN])
{

	for (int i = 0; i < inputRow; i++)
	{
		bool isFirst = false;
		if (i == 0) isFirst = true;//时序的第一个输入，isFirst为true，让各层的c和h都要置0
		
		for (int j = 0; j < deepth; j++) 
		{
			if(j==0) L[j].LayerOutput(inputMatrix[i], isFirst, outputtMatrix[i]);//j==0,输入从矩阵获取，其余从上一层的输出获取
			else L[j].LayerOutput(outputtMatrix[i], isFirst, outputtMatrix[i]);
		}
	}
}

Net::~Net()
{
	delete []L;
}

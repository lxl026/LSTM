#include <fstream>  
#include <sstream>  
#include <string> 
#include "test.h"


int main()
{
/*	// ����cout��������ָ��  
	streambuf* coutBuf = cout.rdbuf();
	ofstream of("outnew.txt");
	// ��ȡ�ļ�out.txt��������ָ��  
	streambuf* fileBuf = of.rdbuf();

	// ����cout��������ָ��Ϊout.txt����������ָ��  
	cout.rdbuf(fileBuf);*/
	
	test t;
	t.fun();

/*	of.flush();
	of.close();
	// �ָ�coutԭ������������ָ��  
	cout.rdbuf(coutBuf);*/

    return 0;
}


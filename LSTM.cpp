#include <fstream>  
#include <sstream>  
#include <string> 
#include "test.h"


int main()
{
/*	// 保存cout流缓冲区指针  
	streambuf* coutBuf = cout.rdbuf();
	ofstream of("outnew.txt");
	// 获取文件out.txt流缓冲区指针  
	streambuf* fileBuf = of.rdbuf();

	// 设置cout流缓冲区指针为out.txt的流缓冲区指针  
	cout.rdbuf(fileBuf);*/
	
	test t;
	t.fun();

/*	of.flush();
	of.close();
	// 恢复cout原来的流缓冲区指针  
	cout.rdbuf(coutBuf);*/

    return 0;
}


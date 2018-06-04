#include "TimeCalcultion.h"


TimeCalcultion::TimeCalcultion()
{
	totalTime = 0;
	counts = 0;
}


TimeCalcultion::~TimeCalcultion()
{
}

void TimeCalcultion::Start()
{
	t1 = clock();
}

void TimeCalcultion::End()
{
	t2 = clock();  
	counts += 1;
	totalTime += (double)(t2 - t1)/CLOCKS_PER_SEC;;
}

void TimeCalcultion::Show()
{
	avgTime = totalTime / counts;
	std::cout << "Counts:" << counts << "\tTotalTime:" << totalTime * 1000 << "\tAvgTime:" << avgTime * 100 << std::endl;
}

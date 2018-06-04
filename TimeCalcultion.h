#include<iostream>
#include <cstdlib>
#include <ctime>
class TimeCalcultion
{
public:
	TimeCalcultion();
	~TimeCalcultion();
	double totalTime;
	double avgTime;
	int counts;
  clock_t t1;
  clock_t t2;
	void Start();
	void End();
	void Show();

};


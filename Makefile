a.out:Layer.o LSTM.o Net.o test.o TimeCalcultion.o
	g++ Layer.o LSTM.o Net.o test.o TimeCalcultion.o -o a.out -pthread -std=c++11
  
Layer.o:Layer.cpp Layer.h
	g++ -c Layer.cpp -o Layer.o -pthread -std=c++11

LSTM.o:LSTM.cpp
	g++ -c LSTM.cpp -o LSTM.o -pthread -std=c++11
  
Net.o:Net.cpp Net.h
	g++ -c Net.cpp -o Net.o -pthread -std=c++11
  
test.o:test.cpp test.h
	g++ -c test.cpp -o test.o -pthread -std=c++11
  
TimeCalcultion.o:TimeCalcultion.cpp TimeCalcultion.h
	g++ -c TimeCalcultion.cpp -o TimeCalcultion.o -pthread -std=c++11

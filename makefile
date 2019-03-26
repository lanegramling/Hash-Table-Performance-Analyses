lab6: main.o
	g++ -std=c++11 -g -Wall main.o -o lab6
main.o: main.cpp Timer.h Timer.hpp Hash.h Hash.hpp HashDouble.h HashDouble.hpp HashQuadraticProbing.h HashQuadraticProbing.hpp Bucket.h Bucket.hpp Node.h Node.hpp
	g++ -std=c++11 -g -Wall -c main.cpp
clean:
	rm *.o lab6

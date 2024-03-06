CFLAGS=-g 
CXXFLAGS=-std=c++11
CC=g++-12

scheduler: scheduler.cpp
	$(CC) $(CXXFLAGS) scheduler.cpp -o scheduler

clean:
	rm -f scheduler *~

check_version:
	$(CC) --version



all:run

point.o: point.cpp point.h
	g++ -c -w point.cpp
task_scheduling.o: task_scheduling.cpp
	g++ -c -w task_scheduling.cpp
run: point.o task_scheduling.o
	g++ point.o task_scheduling.o -o run

clean:
	rm -rf *.o
	rm -rf run
	rm -rf *~

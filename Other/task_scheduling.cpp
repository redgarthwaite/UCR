//include your first name, last name, login, student id here


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cfloat>
#include "point.h"
#include "pair.h"

using namespace std;

//Your task is to write "solution" function that takes the set "tasks" and an empty set
//that will contain the maximum-size subset of mutually compatible tasks. The sets are
//given as vectors. Each task is represented as a Point that is
//defined in class Point as (x, y), where x is the starting time of a task and
//y is the finish time of the task
void solution(vector<Point> tasks, vector<Point> &result)
{
  //input code required for lab 
  // early finish greedy algorithm
  int res = 0;
  result.push_back(tasks[res]);
  for(int i = 1; i < tasks.size();i++)
    {
      if(tasks[i].y >= tasks[res].y && tasks[i].x >= tasks[res].y)
	{
	  result.push_back(tasks[i]);
	  res = i;
	}
    }
}
int main(int argc, char* argv[])
{
	
	string file_input = argv[1];
	ifstream instr;
	instr.open(file_input.c_str(), ios::in);
	string aline;
	
	//read tasks from input file into a set
	//tasks in input file should be in the format: start_time finish_time
	vector<Point> tasks;
	
	while(!instr.eof())
	{
		getline(instr, aline);
		if(!aline.empty())
		{
			Point apoint = Point(aline);
			tasks.push_back(apoint);
		}
	}
	instr.close();

	//sort a set of tasks by starting time
	vector<Point>::iterator start = tasks.begin();
	vector<Point>::iterator stop = tasks.end();
	sort(start, stop, less_y);
	
	//call your function "solution" to find the maximum subset of compatible tasks
	vector<Point> result;
	solution(tasks, result);

	//print out the solution subset of compatible tasks
	if(result.size() != 0){
		vector<Point>::iterator start1 = result.begin();
		vector<Point>::iterator stop1 = result.end();
		for(; start1 != stop1; start1++){
			cout << *start1 << endl;
		}//for
	}//if
	return 0;
}

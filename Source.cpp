/*
Author: Derek Manierre
Operating Systems Round Robin Project
Due: April 7th 2016
*/

#include <iostream>
#include <queue>
#include "generator.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

const int QUANTUM = 1, CS = 0;
double simClock = 0; // Simulation Clock set to 0
double arrival = 0;
int allDone = 0;

double arrivalTime(double x);
double serviceTime();
double turnaroundTime(double x, double y);
double totalWait(double x, double y, double z);

int main(){
	
	srand(time(NULL));
	queue<Generator> readyQ; 
	queue<Generator> doneQ;
	for (int i = 0; i < 100; i++){ //Generate and enqueue 100 processes
		arrival = arrivalTime(arrival);
		readyQ.push(Generator(i,arrival,serviceTime()));
	}
	int size = readyQ.size();
	Generator v = readyQ.front();
	simClock += v.arrival_time;
	Generator b; //Create case to increment timer if no processes have arrived yet
	b = readyQ.back();

	while (allDone != size){ //Run Processes until all are completed
			Generator a;
			a = readyQ.front();
			readyQ.pop();
			
			if (a.isDone == false && a.arrival_time >= simClock){ //Normal Quantum Session
				a.service_time = a.service_time - QUANTUM;

				if (a.starting == true){
					a.start_time = simClock;
					a.starting = false;
				}
				
				simClock += QUANTUM;
				simClock += CS;
				
				if (a.service_time == 0){
					a.isDone = true;
					a.finish_time = simClock;
					allDone += 1;
					doneQ.push(a);
				}
			}

			else if (a.isDone == false && a.arrival_time < simClock){ //If the service time < Quantum time
				if (a.starting == true){
					a.start_time = simClock;
					a.starting = false;
				}
				a.isDone = true;
				simClock = simClock + a.service_time + CS;
				a.finish_time = simClock;
				allDone += 1;
				doneQ.push(a);
			}
else if(a.processID == b.processID){ //If no processes have arrived after it checks the last item in queue
				simClock += 1;
			}

			readyQ.push(a);
	}
	
	double turnaround_array[100];
	for (int c = 0; c < size; c++){ //Create an array to hold turnaround times
		Generator b = readyQ.front(); 
		readyQ.pop();
		double tempTurnaround = turnaroundTime(b.finish_time, b.start_time);
		turnaround_array[c] = tempTurnaround;
		readyQ.push(b);
	}
	
	double wait_array[100];
	for (int z = 0; z < size; z++){ //Create an array to hold total wait times
		Generator d = readyQ.front();
		readyQ.pop();
		double tempWait = totalWait(d.finish_time, d.service_time, d.arrival_time);
		wait_array[z] = tempWait;
		readyQ.push(d);
	}

	double service_array[100];
	for (int n = 0; n < size; n++){//Create an array to hold service times
		Generator p = readyQ.front();
		readyQ.pop();
		service_array[n] = p.service_time;
		readyQ.push(p);
	}
	double tempTotal3 = 0;
	for (int q = 0; q < size; q++){//Calculate average service time
		tempTotal3 = service_array[q] + tempTotal3;
	}
	double average_service_time = tempTotal3 / size;
	
	double tempTotal = 0;
	for (int e = 0; e < size; e++){ //Calculate the average turnaround time
		tempTotal = turnaround_array[e] + tempTotal;
	}
	double average_turnaround_time = tempTotal / size;
	
	double tempTotal2 = 0;
	for (int f = 0; f < size; f++){ //Calculate the average wait time
		tempTotal2 = wait_array[f] + tempTotal2;
	}
	double average_wait_time = tempTotal2 / size;

	cout << "The number of processes completed is: " << size << endl; //Output the number of processes completed
	cout << endl;
	
	for (int k = 0; k < 99; k++){
		Generator l = readyQ.front();
		readyQ.pop();
		readyQ.push(l);
		
		Generator m = doneQ.front();
		doneQ.pop();
		doneQ.push(m);
	}

	for (int g = 0; g < size; g++){ //Output the arrival times and service times
		Generator h = readyQ.front();
		readyQ.pop();
		cout << "The arrival time of process " << h.processID << " is " << std::setprecision(3) << h.arrival_time << " and the service time is " << std::setprecision(3) << h.service_time << "." << endl;
	} 
	cout << endl;
	for (int j = 0; j < 20; j++){ //Output the start times, end times, and wait times
		Generator w = doneQ.front();
		doneQ.pop();
		cout << "The start time of process " << w.processID << " is " << std::setprecision(3) << w.start_time << ", the end time is " << std::setprecision(3) << w.finish_time << ", and the wait time is " << std::setprecision(3) << w.finish_time - w.service_time - w.arrival_time << "." << endl;

	}
	//Output the average service time, average wait time, and average turnaround time
	cout << endl;
	cout << "The average service time is: " << std::setprecision(3) << average_service_time << endl;
	cout << "The average turnaround time is: " << std::setprecision(3) << average_turnaround_time << endl;
	cout << "The average wait time is: " << std::setprecision(3) << average_wait_time << endl;
	
	int x;
	cin >> x;
}
double arrivalTime(double x){
	double random = (rand()%100+1);
	return (-.2*log(1 - (random/100))) + x;
}
double serviceTime(){// Service time Generation
	double random = (rand() % 100 + 1);
	return (2 + (5 - 2)*random / 100);
}
double turnaroundTime(double x, double y){
	double turnaround_time = x - y;
	return turnaround_time;
}
double totalWait(double x, double y, double z){
	double total_wait_time = x - y - z;
	return total_wait_time;
}
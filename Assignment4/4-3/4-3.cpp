#include <iostream>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

using namespace std;

int f;
// function for Numerical Integration along using given operation intensity
double func(double x)
{
	for(int i = 0; i< f; i++)
	{
		x = x*x;
		x = sqrt(x);
	}
	return x*x;
}

// recording current time
double record_time()
{
    timeval tim;
    
    gettimeofday(&tim, NULL);
    double t1 = (double)tim.tv_sec+ (double)(tim.tv_usec/1000000.0); // current time in seconds

    return t1;
}

// MAIN Function
int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		cout << "Program expects 4 input parameters along with ./a.out" << endl;
		return 0;
	}
	
	// function to run
	int a = 1, b = 10;
	int num_proc = stoi(argv[1]), policy_n = stoi(argv[2]), n = stoi(argv[3]), i;
	f = stoi(argv[4]);
	double t = ((b-a)*1.0)/(n*1.0), sum = 0.0, tt;
	
	// time starts
    clock_t t0 = clock();
	double t1 = record_time();
	
	omp_set_num_threads(num_proc);
	#pragma omp parallel for schedule(dynamic, policy_n)
	for(i=0;i<n;i++)
	{
		double c = ((i+0.5)*t) + a;
		sum += func(c);
	}
	
	sum = sum*t;

	// time ends
	double t2= record_time();
	tt = (t2 - t1);
	cout << tt << endl;

	return 0;
}

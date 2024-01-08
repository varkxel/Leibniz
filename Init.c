#include <stdbool.h>
#include <stdio.h>

#include <StringHandling.h>

#include "Leibniz.h"

int main(int argc, char** argv)
{
	// 1st arg is iterations
	long long iterations = 0;
	bool iterationsSet = false;
	
	// 2nd arg is threads
	long threads = 0;
	bool threadsSet = false;
	
	// Threads
	if(argc >= 3)
	{
		threadsSet = ArgToLong(argv[2], &threads);
		if(threads <= 0 || !threadsSet)
		{
			fprintf(stderr, "Thread count \"%li\" is not valid, setting to default value.\n", threads);
			threadsSet = false;
		}
	}
	
	// Iterations
	if(argc >= 2)
	{
		iterationsSet = ArgToLong64(argv[1], &iterations);
		if(iterations <= 0 || !iterationsSet)
		{
			fprintf(stderr, "Iteration count \"%lli\" is not valid, setting to default value.\n", iterations);
			iterationsSet = false;
		}
	}
	
	// Set variables if not already set
	if(!iterationsSet) iterations = 0x00FFFFFF;
	if(!threadsSet)    threads = 1;
	
	double result = Leibniz(iterations, (int) threads);
	printf("Value of PI with %lli iterations: %.16lf\n", iterations, result);
	
	return 0;
}

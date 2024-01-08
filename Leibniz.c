#include "Leibniz.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Unix Stuff
#include <pthread.h>
#include <unistd.h>

typedef struct
{
	long long iterations;
	int threadNum;
	int threadTotal;
	
	double result;
}
ThreadData;

volatile int activeThreads = 0;
pthread_mutex_t activeThreadsMutex = PTHREAD_MUTEX_INITIALIZER;

void* Thread(void* args)
{
	ThreadData* data = (ThreadData*) args;
	
	double sum = 0.0;
	for(long long i = data->threadNum; i < data->iterations; i += data->threadTotal)
	{
		double n = (double) i;
		
		double numerator = pow(-1.0, n);
		double denominator = (2.0 * n) + 1.0;
		sum += numerator / denominator;
	}
	data->result = sum;
	
	// Remove this thread from the list
	pthread_mutex_lock(&activeThreadsMutex);
	activeThreads--;
	pthread_mutex_unlock(&activeThreadsMutex);
	
	pthread_exit(NULL);
}

double Leibniz(const long long iterations, const int threadCount)
{
	const int initialThreads = activeThreads;
	
	// Allocate thread data.
	pthread_t* threads = malloc(threadCount * sizeof(pthread_t));
	ThreadData* data = malloc(threadCount * sizeof(ThreadData));
	
	for(int i = 0; i < threadCount; i++)
	{
		// Add to thread total.
		pthread_mutex_lock(&activeThreadsMutex);
		activeThreads++;
		pthread_mutex_unlock(&activeThreadsMutex);
		
		// Initialise the thread's data struct.
		data[i].iterations = iterations;
		data[i].threadTotal = threadCount;
		data[i].threadNum = i;
		
		// Create the thread.
		pthread_create(&threads[i], NULL, Thread, &data[i]);
	}
	
	// Join all the threads.
	while(activeThreads > initialThreads) sleep(1);
	
	// Free thread array as it's no longer needed.
	free(threads);
	
	double sum = 0.0;
	for(int i = 0; i < threadCount; i++) sum += data[i].result;
	
	free(data);
	
	return sum * 4.0;
}

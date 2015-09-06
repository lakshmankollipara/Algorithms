/*
CS325_Project 1
Experimental Analysis
Name : Lakshman Madhav Kollipara
       Shajith Ravi
       Paris Kalathas
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int algor1(int array[], int length)
{
	int i;
	int j;
	int k;
	int maxsum = array[0];
	int subsum = 0;
	for(i = 0; i < length; i++)
	{
		for(j = i; j < length; j++)
		{
			subsum = array[i];
			for(k = i + 1; k <= j; k++)
			{
				subsum += array[k];
			}
		
			if(subsum > maxsum)
			{
				maxsum = subsum;
			}
		}
	}
	
	return maxsum;
}


int algor2(int array[], int length)
{
	int i;
	int j;
	int maxsum = 0;
	int subsum = 0;
	for(i = 0; i < length; i++)
	{
		subsum = 0;
		for(j = i; j < length; j++)
		{
			subsum += array[j];
			if(subsum > maxsum)
			{
				maxsum = subsum;
			}
		}
	}
	return maxsum;
}
int algor3(int a[], int lo, int hi)
{
	int midpoint;
	int leftMax=0;
	int rightMax=0;
	int temp;
	int bothMax=0;;
	int i, sum;
	if (lo==hi)
	{
		return a[lo];
	}
	midpoint = (lo + hi)/2;
	int maxCrossingSum(int a[], int lo, int midpoint, int hi)
	{
		int bothMaxLeft = 0;
		sum = 0;
		for (i =midpoint; i >= lo ; i--)
		{
			sum += a[i];
			if (sum > bothMaxLeft)
			{
				bothMaxLeft = sum;
			}
		}
		int bothMaxRight = 0;
		sum = 0;
		for (i = midpoint + 1; i <= hi; i++ )
			{
				sum += a[i];
				if (sum > bothMaxRight)
					{
						bothMaxRight = sum;
					}
			}
		return bothMaxRight + bothMaxLeft;
		}
	leftMax = algor3(a, lo, midpoint);
	rightMax = algor3(a, midpoint+1, hi);
	bothMax= maxCrossingSum(a, lo, midpoint, hi);
	if (leftMax >= rightMax)
	{
		if(bothMax>= leftMax)
		{
			return bothMax;
		}
		else
		{
			return leftMax;
		}
	}
	else
	{
		if(bothMax>= rightMax)
		{
			return bothMax;
		}
		else
		{
			return rightMax;
		}
	}
}
 
int algor4(int array[], int length)
{
	int i;
	int maxsub= 0;
	int maxcurrent = 0;
	
	for(i = 0; i < length; i++)
	{
		if((maxcurrent + array[i]) > 0)
		{	
			maxcurrent += array[i];
		}
		else
		{
			maxcurrent = 0;
		}
		if(maxcurrent > maxsub)
		{
			maxsub = maxcurrent;
		}
	}
	return maxsub;
}    
 int * randomArray(int size)
{
	static int *array;
	int i;
	
	array = (int*)malloc(sizeof(int)*size);
	for(i = 0; i  < size; i++)
	{
		array[i] = rand()%200-100;
	}
	
	return array;
} 
    
int main()
{
	int i, size;
	printf("\nEnumeration:\n");
	for(size = 1; size <= 9; size++)
	{
		int n = size*100;
		printf("Size: %d\n", n);
		long totaltime = 0;
		
		for(i = 0; i < 10; i++)
		{
			int * randArray;
			struct timeval start, end;
			randArray = randomArray(n);
			gettimeofday (&start, NULL);
			//printf("Max sum: %d.\n", algor1(randArray, n));
			algor1(randArray, n);
			gettimeofday (&end, NULL);
			totaltime += (((end.tv_sec - start.tv_sec)*1000000)+(end.tv_usec - start.tv_usec));
			free(randArray);
		}
		
		totaltime = totaltime/10;
		printf("Average Time for size: %d is: %lu us.\n", n, totaltime);
	}

		printf("\nBetter Enumeration:\n");
	for(size = 1; size <= 18; size++)
	{
		int n;
		if(size > 9)
		{
			n = (size -9)*1000;
		}
		else
		{
			n = size*100;
		}
		printf("Size: %d\n", n);
		
		long totaltime = 0;
		
		for(i = 0; i < 10; i++)
		{
			int * randArray;
			struct timeval start, end;
			randArray = randomArray(n);
			gettimeofday (&start, NULL);
			//printf("Max sum: %d.\n", algor2(randArray, n));
			algor2(randArray, n);
			gettimeofday (&end, NULL);
			totaltime += (((end.tv_sec - start.tv_sec)*1000000)+(end.tv_usec - start.tv_usec));
			free(randArray);
		}
		
		totaltime = totaltime/10;
		printf("Average Time for size: %d is: %lu us.\n", n, totaltime);
	}

	printf("\nDivide & Conquer:\n");
	for(size = 1; size <= 18; size++)
	{
		int n;
		if(size > 9)
		{
			n = (size -9)*1000;
		}
		else
		{
			n = size*100;
		}
		
		printf("Size: %d\n", n);
		long totaltime = 0;
		for(i = 0; i < 10; i++)
		{
			int * randArray;
			struct timeval start, end;
			randArray = randomArray(n);
			gettimeofday (&start, NULL);
			//printf("Max sum: %d.\n", algor3(randArray, 0, n-1));
			algor3(randArray, 0, n-1);
			gettimeofday (&end, NULL);
			totaltime += (((end.tv_sec - start.tv_sec)*1000000)+(end.tv_usec - start.tv_usec));
			free(randArray);
		}
		
		totaltime = totaltime/10;
		printf("Average Time for size: %d is: %lu us.\n", n, totaltime);
	}

	printf("\nLinear Time:\n");
	for(size = 1; size <= 18; size++)
	{
		int n;
		if(size > 9)
		{
			n = (size -9)*1000;
		}
		else
		{
			n = size*100;
		}
		
		printf("Size: %d\n", n);
		long totaltime = 0;
		for(i = 0; i < 10; i++)
		{
			int * randArray;
			struct timeval start, end;
			randArray = randomArray(n);
			gettimeofday (&start, NULL);
			//printf("Max sum: %d.\n", algor4(randArray, n));
			algor4(randArray, n);
			gettimeofday (&end, NULL);
			totaltime += (((end.tv_sec - start.tv_sec)*1000000)+(end.tv_usec - start.tv_usec));
			free(randArray);
		}
		
		totaltime = totaltime/10;
		printf("Average Time for size: %d is: %lu μs.\n", n, totaltime);
	}

	return 0;
}

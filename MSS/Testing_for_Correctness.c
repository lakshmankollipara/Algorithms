/*
CS325_Project 1
Testing for Correctness
Testcases obtained by using random generated arrays and outputs from Experimental analysis program.
Name : Lakshman Madhav Kollipara
       Shajith Ravi
       Paris Kalathas
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

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
  
int testcases()
{
	printf("Testing using pre calculated Max sum.\n");
	int a[20] = {-27, -14, 6, 22, -29, 10, -38, -8, -17, 18, -20, 23, -7, 17, 49, 44, 1, -16, 9, -46};//127
	int b[20] = {-48, -10, 15, 27, 6, -32, -34, -3, 49, -26, 34, -29, 17, -8, -13, 45, -37, -49, -30, 10};//69
	int c[20] = {-27, 6, -32, 29, -5, 33, 12, 45, -35, 25, 10, -18, -36, -1, 4, 9, 41, -20, 7, -29};//114
	int d[20] = {30, -17, 34, 35, 1, -18, -34, 15, -7, -11, -5, 24, -31, -15, 39, 7, 38, -28, 41, 31};//129
	int e[20] = {8, -39, -24, -30, 41, -8, 22, -13, 49, 17, 9, 0, -4, -10, 19, 3, 44, -38, -37, -7};//169
	
	printf("Testing Algorithm 1...\n");
	if(algor1(a, 20) != 127) return 0;
	if(algor1(b, 20) != 69) return 0;
	if(algor1(c, 20) != 114) return 0;
	if(algor1(d, 20) != 129) return 0;
	if(algor1(e, 20) != 169) return 0;
	
	printf("Testing Algorithm 2...\n");
	if(algor2(a, 20) != 127) return 0;
	if(algor2(b, 20) != 69) return 0;
	if(algor2(c, 20) != 114) return 0;
	if(algor2(d, 20) != 129) return 0;
	if(algor2(e, 20) != 169) return 0;
	
	printf("Testing Algorithm 3...\n");
	if(algor3(a, 0, 20-1) != 127) return 0;
	if(algor3(b, 0, 20-1) != 69) return 0;
	if(algor3(c, 0, 20-1) != 114) return 0;
	if(algor3(d, 0, 20-1) != 129) return 0;
	if(algor3(e, 0, 20-1) != 169) return 0;

	printf("Testing Algorithm 4...\n");
	if(algor4(a, 20) != 127) return 0;
	if(algor4(b, 20) != 69) return 0;
	if(algor4(c, 20) != 114) return 0;
	if(algor4(d, 20) != 129) return 0;
	if(algor4(e, 20) != 169) return 0;

	return 1;
}
    
int main() {
if(testcases() == 1)
{
	printf("\nTEST SUCCESSFUL\n");	
}
else
{
	printf("\nTEST FAILED\n");
}
}
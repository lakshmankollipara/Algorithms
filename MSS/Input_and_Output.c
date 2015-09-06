/*
CS325_Project 1
Input and Output
Name : Lakshman Madhav Kollipara
       Shajith Ravi
       Paris Kalathas
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#define DELIMITER " \r\n\t,"
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
	int i,j;
	int maxsub= 0;
	int maxcurrent = 0;
	int low,high,end_low,end_high;
	
	for(i = 0; i < length; i++)
	{
		end_high = i;
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
int PrintSubArray(FILE * output_file, int a[], int N)
{
	int m = a[0], here = a[0];
	int start = 0, end = 0;
	int s = 0;
	int i;
	for (i = 0; i < N; i++)
	{
		if ((here + a[i]) < a[i])
		{
			s = i;
		}
		if ((here + a[i]) > a[i])
		{
			here = here + a[i];
		}
		else
		{
			here = a[i];
		}
		if (m < here)
		{
			m = here;
			start = s;
			end = i;
		}
	}
	fprintf(output_file, "Sub Array: [");
	for (i = start; i <= end; i++)
	{
		fprintf(output_file, "%d\t", a[i]);
	}
	fprintf(output_file, "]");
	fprintf(output_file, "\n");
}   
int main(){
	system("rm MSS_Results.txt -f");
	int lineIdx = 0;
	int charIdx = 0;
	int removedChars = 0;
	int TERMINATOR = 2147483647;
	size_t buf = 2048;
	char *token = malloc(4096 * sizeof(char));
	char *orLine = malloc(4096 * sizeof(char));
	char **importedLine = malloc(8192 * sizeof(orLine));
	int tokenizedArray[100][100];// = malloc(sizeof(orLine * numOfLines));
	

	FILE *input_file = fopen("MSS_Problems.txt", "rb+");
	FILE *output_file;
	if(input_file == NULL){
      perror("Error opening file");
      return(-1);
	}
	while(fgets(orLine, buf, input_file) != NULL){
		importedLine[lineIdx] = orLine;
		for(charIdx = 0; charIdx < strlen(importedLine[lineIdx]); charIdx++){
			importedLine[lineIdx][charIdx] = importedLine[(lineIdx)][(charIdx+1)];
		}
		importedLine[lineIdx][(strlen(importedLine[lineIdx])-1-removedChars)] = '\n';
		token = strtok(importedLine[lineIdx], DELIMITER);
		charIdx = 0;
		while(token){
			tokenizedArray[lineIdx][charIdx] = atoi(token);
			token = strtok(NULL, DELIMITER);
			charIdx++;
		}
		tokenizedArray[lineIdx][(charIdx)] = TERMINATOR;
		lineIdx++;
	}
	tokenizedArray[(lineIdx)][0] = TERMINATOR;
	fclose(input_file);
	lineIdx = 0;
	charIdx = 0;
	output_file= fopen("MSS_Results.txt","w");
	if (output_file == NULL)
    {
        printf("Error Opening output_file\n");
        exit (1);
    }
	while(tokenizedArray[lineIdx][charIdx] != TERMINATOR){
		fprintf(output_file, "Array %d: ", lineIdx);
		fprintf(output_file, "[");
		while(tokenizedArray[lineIdx][charIdx] != TERMINATOR){
			fprintf(output_file, "%d\t",tokenizedArray[lineIdx][charIdx]);
			charIdx++;
		}
		fprintf(output_file, "]");
		fprintf(output_file, "\n");
		PrintSubArray(output_file, tokenizedArray[lineIdx], charIdx);
		fprintf(output_file, "Enumeration_Max Sum:%d\n", algor1(tokenizedArray[lineIdx], charIdx));
		fprintf(output_file, "Better Enumeration_Max Sum:%d\n", algor2(tokenizedArray[lineIdx], charIdx));
		fprintf(output_file, "Divide & Conquer_Max Sum:%d\n", algor3(tokenizedArray[lineIdx],0, charIdx-1));
		fprintf(output_file, "Linear Time_Max Sum:%d\n", algor4(tokenizedArray[lineIdx], charIdx));
		lineIdx++;
		charIdx = 0;

		
		fprintf(output_file, "\n");
	}
	fclose(output_file);
 	fflush(stdout);
	return 0;
}
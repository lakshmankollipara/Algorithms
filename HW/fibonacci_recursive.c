#include<stdio.h>
#include<time.h>

int fib(int n)
{
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( fib(n-1) + fib(n-2) );
} 
int main()
{
	clock_t start,end, duration;
	start = clock();
   int n = 75;
   int i;
   for ( i = 0 ; i < n ; i++ )
   {
      fib(i);
      //printf("%d\n", fib(i));
   }
   end = clock();
   duration = (end - start)/CLOCKS_PER_SEC;
   printf("Duration: %Lf\n",(long double)duration );
   return 0;
}
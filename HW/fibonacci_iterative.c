#include<stdio.h>
#include<time.h>
 
int main()
{
   clock_t start,end, duration;
   start = clock();
   int n = 10000000 ;
   int first = 0, second = 1, next,i;
   for ( i = 0 ; i < n ; i++ )
   {
      if ( i <= 1 )
         next = i;
      else
      {
         next = first + second;
         first = second;
         second = next;
      }
      printf("%d\n",next);
   }
   end = clock();
   duration = (end - start)/CLOCKS_PER_SEC;
   printf("Duration: %Lf\n",(long double)duration );
   return 0;
}


   
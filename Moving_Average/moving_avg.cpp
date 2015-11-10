#include <stdio.h>
#include <stdlib.h>
#include "ema.h"

#define PERIOD 15 // Number of data points collected at a time

float average[PERIOD];
float add(float x);
float averager(void);
float calc_ema(float p_ave, float x);
int init();

int main()
{
   float p_ave;
   float x; 
   float ema;

   init();

   p_ave = averager();
   printf("p_ave is %f\n",p_ave);

   x = add(15);
   printf("x is %f\n",x);

   ema = calc_ema(p_ave, x); 
   printf("EMA is %f\n",ema);
}

float add(float x)
{
   int count=0;
   for(count=0; count< PERIOD-1; count++)
   {
     average[count] = average[count+1];
   }

   average[count] = x;

   return x;
}

float averager(void)
{
int count = 0;
float sum = 0;

   for(count=0; count < PERIOD; count++)
   {
     sum += average[count];
   }

   return sum/PERIOD;
}

float calc_ema(float p_ave, float x)
{
   float alpha;
   float ema;

   alpha = (2.0 / (PERIOD+1));
   printf("alpha is %f\n",alpha);

   ema = ((x - p_ave))*alpha + p_ave;

   return ema;
}

int init()
{
   int count = 0;
   for(count=0; count<PERIOD; count++)
   {
     average[count] = count;
   }
}



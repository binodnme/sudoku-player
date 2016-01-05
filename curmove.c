#include <stdio.h>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define AFTERTEXT 5
#define M 9
#define N 10
#define POSX 23
#define POSY 2


int curmove(int *a,int *b,int *row,int *col,int signal)
{


 switch(signal)
  {
   case UP:
        if(*b!=POSY)
           {
            *b-=2;
            (*row)--;

           }
        else
           {
            *b=POSY+2*(M-1);
            *row=8;
           }

        break;
   case DOWN:
        if(*b!=POSY+2*(M-1))
           {
            *b+=2;
            (*row)++;
           }
        else
           {
            *b=POSY;
            *row=0;
           }
        break;
   case LEFT:
        if(*a!=POSX)
           {
            *a-=3;
            (*col)--;
           }
        else
           {
            *a=POSX+3*(N-2);
            if(*b!=POSY)
             {
              *b-=2;
              (*row)--;
             }
            else
             {
              *b=POSY+2*(M-1);
              *row=8;
             }
            *col=8;

           }
        break;
   case RIGHT:
   case AFTERTEXT:
        if(*a!=POSX+3*(N-2))
           {
            *a+=3;
            (*col)++;
           }
          else
           {
            *a=POSX;
             if(*b!=POSY+2*(M-1))
              {
               *b+=2;
               (*row)++;
              }
             else
              {
               *b=POSY;
               *row=0;
              }
            *col=0;
           }

  }
 return 0;
}

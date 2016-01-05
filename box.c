#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define UPLEFT 218
#define HORIZONTAL 196
#define UPJOINT 194
#define UPRIGHT 191
#define VERTICAL 179
#define MIDJOINT 197
#define LEFTJOINT 195
#define RIGHTJOINT 180
#define DOWNLEFT 192
#define DOWNJOINT 193
#define DOWNRIGHT 217
#define COLRBOX 12
#define COLRBOXSEP 11


void gotoxy(int x,int y);



int box(int x,int y)
{
  int i,cols,rows,m;
  x--;
  y--;
  rows=9;
  cols=9;

    system("cls");

    gotoxy(x,y);

            /*TOP*/
   SetColorAndBackground(COLRBOXSEP,0);
   printf("%c",UPLEFT);
   SetColorAndBackground(COLRBOX,0);           /*FOR UPPER LEFT CORNER*/
   for(i=1;i<cols;i++)
    {

     printf("%c",HORIZONTAL);
     printf("%c",HORIZONTAL);         /*FOR UPPER AND LOWER BAR*/
     if(i%3==0)
     {
        SetColorAndBackground(COLRBOXSEP,0);
        printf("%c",UPJOINT);
        SetColorAndBackground(COLRBOX,0);
     }
     else
       printf("%c",UPJOINT);        /*FOR JOIN BETWEEN TWO CELLS(TOP)*/
    }
    printf("%c",HORIZONTAL);
    printf("%c",HORIZONTAL);
    SetColorAndBackground(COLRBOXSEP,0);
    printf("%c\n",UPRIGHT);        /*FOR UPPER RIGHT CORNER*/
    SetColorAndBackground(COLRBOX,0);
    y++;
    gotoxy(x,y);


         /*MIDDLE*/
   for(i=0;i<=cols;i++)
    {
     printf("%c",VERTICAL);          /*FOR SIDE BAR*/
     printf(" ");
     printf(" ");
    }
   printf("\n");

   y++;
   gotoxy(x,y);

   for(m=1;m<rows;m++)
     {
      if(m%3==0)
        {
           SetColorAndBackground(COLRBOXSEP,0);
           printf("%c",LEFTJOINT);
           SetColorAndBackground(COLRBOX,0);
        }
      else
        printf("%c",LEFTJOINT);           /*FOR JOIN BETWEEN TWO CELLS(LEFT SIDE)*/
      for(i=1;i<cols;i++)
       {
        printf("%c",HORIZONTAL);
        printf("%c",HORIZONTAL);
        if(m%3==0&&i%3==0)
         {
           SetColorAndBackground(COLRBOXSEP,0);
           printf("%c",MIDJOINT);
           SetColorAndBackground(COLRBOX,0);
         }
        else
          printf("%c",MIDJOINT);        /*FOR JOIN BETWEEN TWO CELLS(MIDDLE)*/
       }
       printf("%c",HORIZONTAL);
       printf("%c",HORIZONTAL);

       if(m%3==0)
        {
           SetColorAndBackground(COLRBOXSEP,0);
           printf("%c",RIGHTJOINT);
           SetColorAndBackground(COLRBOX,0);
        }
       else
           printf("%c\n",RIGHTJOINT);        /*FOR JOIN BETWEEN TWO CELLS(RIGHT SIDE)*/

       y++;
       gotoxy(x,y);

      for(i=0;i<=cols;i++)
       {
        printf("%c",VERTICAL);
        printf(" ");
        printf(" ");
       }
       printf("\n");

       y++;
       gotoxy(x,y);
     }


      /*BOTTOM*/
    SetColorAndBackground(COLRBOXSEP,0);
    printf("%c",DOWNLEFT);           /*FOR LOWER LEFT CORNER*/
    SetColorAndBackground(COLRBOX,0);
    for(i=1;i<cols;i++)
     {
      printf("%c",HORIZONTAL);
      printf("%c",HORIZONTAL);
      if(i%3==0)
       {
        SetColorAndBackground(COLRBOXSEP,0);
        printf("%c",DOWNJOINT);
        SetColorAndBackground(COLRBOX,0);
       }
      else
        printf("%c",DOWNJOINT);       /*FOR JOIN BETWEEN TWO CELLS(BOTTOM)*/
     }
     printf("%c",HORIZONTAL);
     printf("%c",HORIZONTAL);
     SetColorAndBackground(COLRBOXSEP,0);
     printf("%c",DOWNRIGHT);         /*FOR LOWER RIGHT CORNER*/
     SetColorAndBackground(23,0);

    return 0;
}

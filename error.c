#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define ROWN 1
#define COLN 2
#define BOXN 3
#define POSX 23
#define POSY 2

void SetColorAndBackground(int ForgC, int BackC);
int check1(int *,int *,int ,int ,int ,int,char [9][9]);
int check2(int *,int *,int ,int ,int ,int ,int ,char [9][9]);
int seccheck(int ,int ,int,int,int,char [][]);


int error(int *ptr1,int *ptr2,int inc,int row,int col,char str[9][9])
{
 int i,j,starti,recrow,reccol;
 int flag=0,count=0;

    /*TO CHECK ERROR IN ROW*/
   for(i=0;i<9;i++)
      if(col!=i&&str[row][i]!='0')
         if(str[row][col]==str[row][i])
            {
              if(inc!=0)
               {
                recrow=row;
                reccol=i;
                count++;
               }
             else
                return 1;
            }
    if(count==1)
      {
        for(j=0;j<inc;j++)
          if(*(ptr1+j)==recrow&&*(ptr2+j)==reccol)
            {
             flag=1;
             break;
            }

        if(flag==0)
          {
            if((col<3&&reccol<3)||((col>=3&&col<6)&&(reccol>=3&&reccol<6))||((col>=6&&col<9)&&(reccol>=6&&reccol<9)))
                ;

            else if(seccheck(ROWN,recrow,reccol,row,col,str)!=1)
              {
               gotoxy(POSX+3*reccol,POSY+2*recrow);
               printf("%c",str[recrow][reccol]);
               gotoxy(POSX+3*col,POSY+2*row);
              }
          }
       }

        count=0;
        flag=0;
          /*TO CHECK ERROR IN COLUMN*/
          for(i=0;i<9;i++)
            if(row!=i&&str[i][col]!='0')
              if(str[row][col]==str[i][col])
                 {
                  if(inc!=0)
                   {
                    recrow=i;
                    reccol=col;
                    count++;
                   }
                  else
                   return 1;
                 }

      if(count==1)
      {
        for(j=0;j<inc;j++)
          if(*(ptr1+j)==recrow&&*(ptr2+j)==reccol)
            {
             flag=1;
             break;
            }

        if(flag==0)
          {
            if((row<3&&recrow<3)||((row>=3&&row<6)&&(recrow>=3&&recrow<6))||((row>=6&&row<9)&&(recrow>=6&&recrow<9)))
                ;

            else if(seccheck(COLN,recrow,reccol,row,col,str)!=1)
              {
               for(i=0;i<inc;i++)
                 if(*(ptr1+i)==row&&*(ptr2+i)==col)
                   break;
               gotoxy(POSX+3*reccol,POSY+2*recrow);
               printf("%c",str[recrow][reccol]);
               gotoxy(POSX+3*col,POSY+2*row);
              }
          }
       }


       /*TO CHECK ERROR IN 3*3 BOX*/
        if(row<3)
           starti=0;
        else if(row>=3&&row<6)
           starti=3;
        else
           starti=6;

      if(check1(ptr1,ptr2,inc,row,col,starti,str)==1)
        return 1;

return 0;
}




int check1(int *ptr1,int *ptr2,int inc,int row,int col,int starti,char str[9][9])
 {
     int startj;

         if(col<3)
              startj=0;

         else if(col>=3&&col<6)
              startj=3;
         else
              startj=6;

    if(check2(ptr1,ptr2,inc,row,col,starti,startj,str)==1)
        return 1;

  return 0;
 }


int check2(int *ptr1,int *ptr2,int inc,int row,int col,int starti,int startj,char str[9][9])
{
 int i,j,recrow,reccol,count=0,flag=0;

     for(i=starti;i<3+starti;i++)
        for(j=startj;j<3+startj;j++)
           if((i!=row||j!=col)&&str[i][j]!='0')
             if(str[row][col]==str[i][j])
                {
                  if(inc!=0)
                   {
                    recrow=i;
                    reccol=j;
                    count++;
                   }
                  else
                   return 1;
                 }

    if(count==1)
      {
        for(j=0;j<inc;j++)
          if(*(ptr1+j)==recrow&&*(ptr2+j)==reccol)
            {
             flag=1;
             break;
            }

        if(flag==0)
        {
            if(seccheck(BOXN,recrow,reccol,row,col,str)!=1)
               {
                gotoxy(POSX+3*reccol,POSY+2*recrow);
                printf("%c",str[recrow][reccol]);
                gotoxy(POSX+3*col,POSY+2*row);
               }
        }
       }

 return 0;
}


void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}


int seccheck(int signal,int recrow,int reccol,int row,int col,char str[9][9])
{
  int i,j,starti,startj;
  int flag=0;


 /*SECONDARY CHECK IN A COL*/
    if(signal==ROWN||signal==BOXN)
      for(i=0;i<9;i++)
       if(recrow!=i)
        if(row!=i)
         if(str[recrow][reccol]==str[i][reccol])
           flag=1;

 /*SECONDARY CHECK IN A ROW*/
    if(signal==COLN||signal==BOXN)
     for(i=0;i<9;i++)
        if(reccol!=i)
         if(col!=i)
          if(str[recrow][reccol]==str[recrow][i])
           flag=1;

 /*SECONDARY CHECK IN A 3*3 BOX*/
    if(signal==ROWN||signal==COLN)
      {
         if(recrow<3)
           starti=0;
         else if(recrow>=3&&recrow<6)
           starti=3;
         else
           starti=6;

         if(reccol<3)
          startj=0;
         else if(reccol>=3&&reccol<6)
          startj=3;
         else
          startj=6;

         for(i=starti;i<starti+3;i++)
           for(j=startj;j<startj+3;j++)
             if(recrow!=i&&reccol!=j)
               if(str[recrow][reccol]==str[i][j])
                 flag=1;
      }
 return flag;
}

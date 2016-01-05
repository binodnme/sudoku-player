#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define AFTERTEXT 5
#define POSX 23
#define POSY 2


void gotoxy(int x,int y);
void SetColorAndBackground(int ForgC, int BackC);
int error(int *,int *,int ,int ,int ,char [][]);
COORD coord = {0, 0};
int level();
int sudofnl(int ,int ,int ,char [][]);
int curmove(int *,int *,int *,int *,int);

/*START OF DATA FUNCTION*/
int data(int level,int status,int inc,char str[9][9],int *ptr1,int *ptr2,char user[15],char dir[20])
 {
  int i,j,flag;
  int row=0,col=0,count=81-inc;
  int a=POSX,b=POSY;
  unsigned char d,c;
  FILE *fsave,*fr;
  char ch;

  /*TO PRINT THE DATA*/
    for(i=0;i<9;i++)
      for(j=0;j<9;j++)
       {
        gotoxy(a,b);
        if(str[i][j]>'0'&&str[i][j]<='9')
          {
           SetColorAndBackground(10,0);//GREEN
           printf("%c",str[i][j]);
          }
            curmove(&a,&b,&row,&col,AFTERTEXT);
         }
        SetColorAndBackground(23,0);//NORMAL


        /*TO RESTORE THE DATA INPUT BY THE USER*/
   if(status==1)
    {
        fr=fopen(dir,"r");
           level=getc(fr);

         for(i=0;i<9;i++)
           for(j=0;j<9;j++)
             {
                 if((ch=getc(fr))!='0')
                    if(ch!=str[i][j])
                     {
                      gotoxy(a,b);
                      str[i][j]=ch;
                      count--;
                      if(error(NULL,NULL,0,i,j,str)==1)
                       {
                        SetColorAndBackground(92,0);//RED
                        putch(str[i][j]);
                        SetColorAndBackground(23,0);//NORMAL
                       }
                      else
                        putch(str[i][j]);

                     }
                  curmove(&a,&b,&row,&col,AFTERTEXT);

             }
        fclose(fr);
    }

gotoxy(0,POSY);
printf("\n\nPLAYER STATUS:\n\nNAME:%s\n\nLEVEL:%d",user,level);

   /*CHECKS WHETHER THE BOX IS FULL OR NOT*/
   while(1)
     {
           flag=0;
            gotoxy(a,b);
           //TAKES THE INPUT CHARACTER
            c=getch();
           //TO EXIT
           if(c==27)
              {
               system("cls");
               gotoxy(15,4);
               printf("Do you want to save game?\n");
               gotoxy(15,6);
               printf("1.yes\n");
               gotoxy(15,8);
               printf("2.no");

                 i=1;
                 while(i==1)
                  {
                   switch(getch())
                     {
                      case '1':
                            if((fsave=fopen(dir,"w"))==NULL)
                                printf("FILE ERROR!!");
                            else
                                {
                                   fputc(level,fsave);
                                    for(i=0;i<9;i++)
                                     for(j=0;j<9;j++)
                                        fputc(str[i][j],fsave);
                                   fclose(fsave);
                                }

                      case '2':
                            return 1;

                      default:
                        i=0;
                     }

                   }
              }



           /*FOR THE ARROW KEY*/
           else if(c==224)
              {
                d=getch();

                 switch(d)
                   {
                    case 'H':                           /*MOVES THE CURSOR UP*/
                             curmove(&a,&b,&row,&col,UP);
                             break;

                    case 'M':                           /*MOVES THE CURSOR RIGHT*/
                             curmove(&a,&b,&row,&col,RIGHT);
                             break;

                    case 'P':                           /*MOVES THE CURSOR DOWN*/
                             curmove(&a,&b,&row,&col,DOWN);
                             break;

                    case 'K':                           /*MOVES THE CURSOR LEFT*/
                            curmove(&a,&b,&row,&col,LEFT);
                            break;
                   }
                 gotoxy(53,POSY);
                 printf("You are in (%d,%d)",row+1,col+1);
                 gotoxy(a,b);
              }

             /*IF THE ENTERED CHAR IS IN BETWEEN 0 AND 10*/
             else if(c>'0'&&c<='9')
              {
                for(i=0;i<inc;i++)
                   if(*(ptr1+i)==row&&*(ptr2+i)==col)       /*CHECKS THE VALIDITY OF THE POSITION OF THE ENTERED CHARACTER*/
                     {
                      flag=1;
                      break;
                     }

                   if(flag==0)
                       {
                        if(str[row][col]!='0')
                          {
                            if(c!=str[row][col])
                             error(ptr1,ptr2,inc,row,col,str);
                          }
                        else
                           count--;

                          if(count==0)
                            {
                               str[row][col]=c;
                               if(sudofnl(level,row,col,str)==1)
                                  return 0;
                            }


                        str[row][col]=c;

                          /*FUNCTION CALL TO CHECK THE ERROR*/
                          if(error(NULL,NULL,0,row,col,str)==1)
                            {
                             SetColorAndBackground(92,0); //RED
                             putch(str[row][col]);
                             SetColorAndBackground(23,0);
                            }
                           else
                              putch(str[row][col]);           /*PRINTS THE CHARACTER*/

                          curmove(&a,&b,&row,&col,AFTERTEXT);
                        }
              }


     }
  return 0;
 }
/*END OF DATA FUNCTION*/


void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int sudofnl(int level,int row,int col,char str[9][9])
{
 int i,j,k,starti,startj;
 int flag=0,out=0;
 char sudoful[]="123456789";


 for(i=0;i<9;i++)
       {
         for(k=0;k<9;k++)
           {
              flag=0;
              for(j=0;j<9;j++)
                  if(sudoful[k]==str[i][j])
                   {
                    flag=1;
                    break;
                   }
              if(flag!=1)
               {
                out=1;
                break;
               }
           }
         if(out==1)
           break;
       }

 if(out==0)
   {
      for(j=0;j<9;j++)
       {
         for(k=0;k<9;k++)
           {
              flag=0;
              for(i=0;i<9;i++)
                  if(sudoful[k]==str[i][j])
                   {
                    flag=1;
                    break;
                   }
              if(flag!=1)
                {
                  out=1;

                  break;
                }
           }
         if(out==1)
          break;
       }
    }

   if(out==0)
     {
         for(startj=0;startj<9;)
          {
           for(starti=0;starti<9;)
             {
              for(k=0;k<9;k++)
                 {
                  flag=0;
                  for(i=starti;i<starti+3;i++)
                    {
                     for(j=startj;j<startj+3;j++)
                       if(sudoful[k]==str[i][j])
                        {
                          flag=1;
                          break;
                        }
                      if(flag==1)
                        break;
                    }
                   if(flag!=1)
                    {
                      out=1;
                      break;
                    }
                 }
              if(out==1)
                break;
              starti+=3;
             }
           if(out==1)
             break;
           startj+=3;
          }
     }

   if(out==0)
      {
        putch(str[row][col]);
        gotoxy(53,POSY+3);
        printf("CONGRATULATIONS!!!!!");

        if(level<3)
          {
           gotoxy(53,POSY+5);
           printf("You have completed level %d",level);
           gotoxy(POSX-2,21);
           printf("Press any key to proceed to next level");
           getch();
          }
        return 1;
      }

 return 0;
}

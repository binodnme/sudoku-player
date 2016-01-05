#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define POSX 23
#define POSY 2

void gotoxy(int x,int y);
int box(int,int);
int data(int,int,int,char [][],int *,int *,char [],char []);



int level(int status,char dir[20],char user[15])

{
    static int level;
    FILE *fr;
    int ran,i,j,inc,flag,databack;
    int *ptr1,*ptr2;
    int count=0;
    char str[9][9],temp[9][9];
    char ch;

    level=1;

   /*GETS THE DATA EXISTING USER*/
    if(status==1)
        {
         fr=fopen(dir,"r");
         level=fgetc(fr);
             for(i=0;i<9;i++)
                for(j=0;j<9;j++)
                     temp[i][j]=fgetc(fr);
         fclose(fr);
        }


    while(level<4)
     {

      /*TO OPEN THE FILE OF SPECIFIED LEVEL*/
        switch(level)
               {
                case 1:
                    fr=fopen("level/level1.txt","r");
                         if(status!=1)
                          {
                           srand((unsigned)time(NULL));
                           ran=1+rand()%5;
                          }
                         break;

                case 2:
                    fr=fopen("level/level2.txt","r");
                      if(status!=1)
                          {
                           srand((unsigned)time(NULL));
                           ran=1+rand()%5;
                          }
                      break;
                case 3:
                    fr=fopen("level/level3.txt","r");
                        if(status!=1)
                          {
                           srand((unsigned)time(NULL));
                           ran=1+rand()%5;
                          }
               }

        if(status!=1)
          {
           for(i=1;i<ran;i++)
             {
              while(1)
                if(fgetc(fr)=='\n')
                   break;
              }


          }

          if(status==1)
           {
            while(1)
             {
               flag=0;

                for(i=0;i<9;i++)
                  {
                   for(j=0;j<9;j++)
                     {
                       if((ch=fgetc(fr))!='0')
                         if(ch!=temp[i][j])
                          {
                           count++;
                           flag=1;
                           fseek(fr,count*83,0);
                           break;
                          }
                     }
                   if(flag==1)
                    break;
                  }


            if(flag==0)
             {
              if(count==0)
                rewind(fr);
              else
                fseek(fr,-81,1);
              break;
             }
         }
       }

       /*STORE THE DATA TO THE 2D CHAR ARRAY FROM FILE*/
       for(i=0;i<9;i++)
          for(j=0;j<9;j++)
             str[i][j]=fgetc(fr);


        /*TO CLOSE FILE*/
       fclose(fr);

       /*AUTOSAVING THE DATA*/
       if(status==0)
        {
          fr=fopen(dir,"w");
          fputc(level,fr);
            for(i=0;i<9;i++)
              for(j=0;j<9;j++)
                fputc(str[i][j],fr);
          fclose(fr);
        }

          /*TO COUNT NON-ZERO VALUE IN THE DATA*/
          for(i=0;i<9;i++)
            for(j=0;j<9;j++)
               if(str[i][j]!='0')
                 inc++;

          /*ALLOCATING MEMORY TO STORE POSITION OF THE NON-ZERO VALUE OF THE DATA*/
           ptr1=(int *)malloc(inc*sizeof(int));
           ptr2=(int *)malloc(inc*sizeof(int));


          /*TO STORE THE POSITION OF THE NON-ZERO VALUE OF THE DATA*/
           inc=0;
           for(i=0;i<9;i++)
            for(j=0;j<9;j++)
              if(str[i][j]!='0')
                {
                 *(ptr1+inc)=i;
                 *(ptr2+inc)=j;
                  inc++;
                }

        box(POSX,POSY);

        databack=data(level,status,inc,str,ptr1,ptr2,user,dir);
        status=0;
         if(databack==1)
           return 0;


      level++;
     }
 gotoxy(53,POSY+7);
 printf("YOU HAVE COMPLETED ALL");
 getch();

 return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <direct.h>


typedef struct
  {
   char username[15];
   char password[15];
  }player;


int data(int,int,int,char [][],int *,int *);
int box(int,int);
int level(int ,char [] ,char []);
int recwrite();
int recread();
void gotoxy();

int main()
{
  int a;

  while(1)
   {
    gotoxy(15,4);
    printf("Welcome to sudoku.....\n\n");
    gotoxy(17,6);
    printf("1.new game\n");gotoxy(17,8);
    printf("2.load game\n");gotoxy(17,10);
    printf("3.Instructions\n");gotoxy(17,12);
    printf("4.Credits\n");gotoxy(17,14);
    printf("5.Exit\n");gotoxy(14,17);
    printf("CHOOSE YOUR OPTION (1/2/3/4/5)");

    a=getch();

    switch(a)
     {
        case '1':
                recwrite();
                break;
        case '2':
                recread();
                break;
        case '3':
                system("cls");
                printf("********************************************\n\n");
                printf("Enter the numbers from 1 to 9\n");
                printf("into the empty cells of the Sudoku\n");
                printf("such that all nine rows\n");
                printf(" all nine columns and\n");
                printf("all nine 3x3 boxes contain all nine digits.\n\n");
                printf("********************************************\n\n");
                printf("Use arrow keys to move the cursor to respective direction.\n\n");
                printf("********************************************\n\n");
                printf("The GREEN colored number cannot be replaced\n\n");
                printf("The RED colored number indicates the error\n\n");
                printf("The WHITE colored number indicates\n");
                printf("the absence of same number in corresponding row,column and 3*3 box\n");
                printf("at the time of input.");
                getch();
                break;
        case '4':
            system("cls");
            gotoxy(30,5);
            printf("BIBEK SHRESTHA");
            gotoxy(30,7);
            printf("BINOD KUMAR SHRESTHA");
            gotoxy(30,9);
            printf("BHUWAN BHATT");
            gotoxy(30,11);
            printf("KAPIL DAHAL");
            getch();
            break;
        case '5':
            exit(0);

     }

    system("cls");
   }
    return 0;
}
/*END OF MAIN FUNCTION*/

/*FUNCTION TO RECORD THE PLAYER'S NAME AND PASSWORD*/
int recwrite()
{
     FILE *fr;
     player p1,temp;
     char ch,dir[15]="users/";
     int i=0,len=0;

     system("cls");
     gotoxy(15,4);
     printf("Enter the name:");
     scanf("%s",p1.username);

     if((fr=fopen("record.bnd","rb"))!=NULL)
       while(fread(&temp,sizeof(player),1,fr)!=0)
        {
         if(strcmp(p1.username,temp.username)==0)
          {
           gotoxy(15,6);
           printf("user already exist.");
           fclose(fr);
           getch();
           return 0;
          }
        }
     fclose(fr);


     fr=fopen("record.bnd","ab");
         if(fr==NULL)
          {
           printf("cannot open file.");
           exit(-1);
          }

         gotoxy(15,6);
         printf("Enter the password:");

          while(1)
           {
                ch=getch();
                if(ch==8)
                 {
                  if(len>(strlen("Enter the password:")+15))
                    {
                      gotoxy(len-1,6);
                      printf(" ");
                      gotoxy(len-1,6);
                      i--;
                    }
                 }
                else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                      {
                       p1.password[i]=ch;
                       printf("*");
                       i++;
                      }
                 else if(i>0)
                     {
                      if(ch==13)
                      break;
                     }
                 len=15+strlen("Enter the password:")+i;
           }

         p1.password[i]='\0';

         fwrite(&p1,sizeof(player),1,fr);

     fclose(fr);
     strcat(dir,p1.username);
     mkdir(dir);
     strcat(dir,"/save.txt");
     level(0,dir,p1.username);

     return 0;
}


/*FUNCTION TO READ THE RECORD OF EXISTING PLAYER*/
int recread()
{
     int flag=0,i=0,len=0;
     FILE *fr;
     player p11;
     char name[15],pass[15],dir[15]="users/";
     char ch;

     system("cls");
     gotoxy(15,4);
     printf("Enter the name:");
     scanf("%s",name);
     gotoxy(15,6);
     printf("Enter the password:");
        while(1)
          {
           ch=getch();
            if(ch==8)
             {
              if(len>(strlen("Enter the password:")+15))
                {
                  gotoxy(len-1,6);
                  printf(" ");
                  gotoxy(len-1,6);
                  i--;
                }
             }
            else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                  {
                   pass[i]=ch;
                   printf("*");
                   i++;
                  }
             else if(i>0)
                 {
                  if(ch==13)
                  break;
                 }
             len=15+strlen("Enter the password:")+i;
          }

        pass[i]='\0';

     fr=fopen("record.bnd","rb");
        if(fr==NULL)
           {
            printf("FILE ERROR!!");
            exit(-5);
           }

     while(fread(&p11,sizeof(player),1,fr)!=0)
       if(strcmp(name,p11.username)==0)
        {
         if(strcmp(pass,p11.password)==0)
              {
                fclose(fr);
                strcat(dir,p11.username);
                strcat(dir,"/save.txt");
                flag=1;
                level(1,dir,p11.username);
              }
        }
     if(flag==0)
      {
       gotoxy(15,8);
       printf("No match found..");
       getch();
       fclose(fr);
      }

 return 0;
}

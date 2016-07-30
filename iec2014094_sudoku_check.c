/*NAME:-       "Ram Narayan Mishra"        EN:-"IEC2014094",         SECTION:-"C" */
              /*SUDOKU SOLUTION VALIDATOR*/
#include<stdio.h>
#include<pthread.h>
struct matrix
{
int row;
int col;
};
/*given sudoku puzzle for check*/
int sudoku[9][9]={{6,2,4,5,3,9,1,8,7},
                  {5,1,9,7,2,8,6,3,4},
                  {8,3,7,6,1,4,2,9,5},
                  {1,4,3,8,6,5,7,2,9},
                  {9,5,8,2,4,7,3,6,1},
                  {7,6,2,3,9,1,4,5,8},
                  {3,7,1,9,5,6,8,4,2},
                  {4,9,6,1,8,2,5,7,3},
                  {2,8,5,4,7,3,9,1,6}};
/*for row check of sudoku */
void *row_check(void *d)
{
  int n,m,h=0;
  int k,i,j;
  for(i=0;i<9;i++)
  {
    k=1;
    while(k<10)
    {
      for(j=0;j<9;j++)
      {
        if(sudoku[i][j]==k)
        {
          h++;
          break;
        }
      }
    k++;
    }
  }
  if(h==81)
  {
    n=1;
  }
  else
  {
  n=-1;
  }
  pthread_exit((void*)n);
}
/* for column check of sudoku*/
void *col_check(void *d)
{
  int n,m,h=0;
  int k,i,j;
  for(i=0;i<9;i++)
  {
    k=1;
   while(k<10)
   {
    for(j=0;j<9;j++)
    {
     if(sudoku[j][i]==k)
     {
       h++;
       break;
     }
   }
   k++;
  }
  }
 if(h==81)
 {
 n=1;
 }
 else
 {
 n=-1;
 }
pthread_exit((void*)n);
}
/*for square check of sudoku */
void *square_check(void *mn)
{
  struct matrix *my_data=(struct matrix *)mn;
  int l=(*my_data).row;
  int m=(*my_data).col;
  int i,j,p;
  int k,h=0;
  k=1;
  while(k<10)
  {
  for(i=l;i<l+3;i++)
  {
    for(j=m;j<m+3;j++)
      {
        if(sudoku[i][j]==k)
          {
             h++;
             goto jump;
          }
       }
     }
     jump:
     k++;
  }
  if(h==9)
  {
  p=1;
  }
  else
  {
  p=-1;
  }
  pthread_exit((void*)p);
}
int main()
{
  struct matrix *p;
  p=(struct matrix*)malloc(sizeof(struct matrix));
  pthread_t thread[11];
  int i,j,k;
  void *b;
/*create three thread one for row check,column check and another for square check*/
  pthread_create(&thread[0],NULL,row_check,NULL);
  pthread_create(&thread[1],NULL,col_check,NULL);
  i=2;
  for(j=0;j<=6;j=j+3)
  { 
    for(k=0;k<=6;k=k+3)
    {
      (*p).row=j;
      (*p).col=k;
      pthread_create(&thread[i],NULL,square_check,(void*)p);
      i++;
     }
  }
/*join all thread return value and add them */
  int s=0;
  for(i=0;i<11;i++)
  {
    pthread_join(thread[i],&b);
    s=s+(int)b;
  }
/* if sudoku is valid sum is 3 because all three thread return 1*/
  if(s==11)
  {
    printf("valid Sudoku puzzle\n");
  }
  else
  {
    printf("invalid Sudoku puzzle\n");
  }
  pthread_exit(NULL);
}


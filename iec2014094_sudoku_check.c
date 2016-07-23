/*NAME:-       "Ram Narayan Mishra"        EN:-"IEC2014094",         SECTION:-"C" */
              /*SUDOKU SOLUTION VALIDATOR*/
#include<stdio.h>
#include<pthread.h>
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
goto aam;
}
}
aam:
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
goto jump;
}
}
jump:
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
int i,j,l,p,m;
int k,h=0;
for(l=0;l<=6;l=l+3)
{
for(m=0;m<=6;m=m+3)
{
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
}
}
if(h==81)
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
pthread_t thread[3];
int i;
void *b;
/*create three thread one for row check,column check and another for square check*/
pthread_create(&thread[0],NULL,row_check,NULL);
pthread_create(&thread[1],NULL,col_check,NULL);
pthread_create(&thread[2],NULL,square_check,NULL);
/*join all thread return value and add them */
int s=0;
for(i=0;i<3;i++)
{
pthread_join(thread[i],&b);
s=s+(int)b;
}
/* if sudoku is valid sum is 3 because all three thread return 1*/
if(s==3)
{
printf("valid Sudoku puzzle\n");
}
else
{
printf("invalid Sudoku puzzle\n");
}
pthread_exit(NULL);
}


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int sud[9][9]={{6,2,4,5,3,9,1,8,7},{5,1,9,7,2,8,6,3,4},{8,3,7,6,1,4,2,9,5},{1,4,3,8,6,5,7,2,9},{9,5,8,2,4,7,3,6,1},{7,6,2,3,9,1,4,5,8},{3,7,1,9,5,6,8,4,2},{4,9,6,1,8,2,5,7,3},{2,8,5,4,7,3,9,1,6}};
struct matrix
{
int row;
int col;
};
void *row_col_check(void *d)
{
int n,m,h=0;
m=(int)d;
int k,i,j;
for(i=0;i<9;i++)
{
k=1;
while(k<10)
{
for(j=0;j<9;j++)
{
if(m==0 &&sud[i][j]==k)
{
h++;
goto aam;
}
else if(m==1 && sud[j][i]==k)
{
h++;
goto aam;
}
}
aam:
k++;
}
}
if(h==9*9)
{
n=1;
}
else
{
n=-1;
}
pthread_exit((void*)n);
}
void *sq_check(void *mn)
{
struct matrix *my_data=(struct matrix *)mn;
int i=(*my_data).row;
int j=(*my_data).col;
int n,m,p;
n=i+3;
m=j+3;
int k,h=0;
for(k=1;k<10;k++)
{
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
if(sud[i][j]==k)
{
h++;
i=n;j=m;
}
}
}

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
int i,a;
void *b;
int t,l,k;
for(i=0;i<2;i++)
{
t=i;
a=pthread_create(&thread[i],NULL,row_col_check,(void*)t);
if(a)
{
printf("error");
}
}
while(i<11)
{
for(l=0;l<=6;l=l+3)
{
for(k=0;k<=6;k=k+3)
{
(*p).row=l;
(*p).col=k;

a=pthread_create(&thread[i],NULL,sq_check,(void*)p);
if(a)
{
printf("error");
}
}
}
i++;
}
int s=0;
for(i=0;i<11;i++)
{
pthread_join(thread[i],&b);
s=s+(int)b;
}
if(s==11)
{
printf("valid\n");
}
else
{
printf("invalid\n");
}
pthread_exit(NULL);
}


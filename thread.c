#include<stdio.h>
#include<pthread.h>
#define size 2
void *sum(void *d)
{
int i,n=0;
int su;
su=(int)d;
for(i=su-4;i<=su;i++)
{
n=n+i;
}
pthread_exit((void*)n);
}
int main()
{
pthread_t thread[2];
int i,a;
void *b;
int t;
for(i=0;i<2;i++)
{
t=5*(i+1);
a=pthread_create(&thread[i],NULL,sum,(void*)t);

if(a)
{
printf("error");
}
}
int s=0;
for(i=0;i<2;i++)
{
pthread_join(thread[i],&b);
s=s+(int)b;
}
printf("sum=%d",s);
pthread_exit(NULL);
}


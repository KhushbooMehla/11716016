#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#define MAX 32767  

struct process
{
	int a;                                // arrival time
	int b;                                // burst time 
	int pid;                              // process id
	int q;                                // queue it belongs
	int c;                                // completion time
	int w;                                //waiting time
	int t;                                //turn around time
	int temp_b;
};


void printScenario(struct process p[],int len)
{
	int i;
	printf("\n\n    --------------------------------------------------------------------------------------------------------------------------- \n");
	printf("    |  Process    |    Arrival Time    |   Burst Time  |      Completion Time     |     Waiting Time     |   Turn-Around Time \n");
	printf("    -------------------------------------------------------------------------------------------------------------------------- \n");
	for(i=0;i<len;i++)
	{
		printf("        P%d                 %d                   %d               %d                       %d                      %d\n",p[i].pid,p[i].a,p[i].temp_b,p[i].c,p[i].w,p[i].t);
	}
} 

void printQueue(int a[],int n)
{
	int i;
	printf(" Queue 2 : \n");
	for(i=0;i<n;i++)
	printf(" %d",a[i]);
	printf("\n");
}

int main()
{
	int n,i,j;
	double wait_time = 0, turnaround_time = 0;
    float average_waiting_time, average_turnaround_time;
	printf("\n\n\n\n -----------  | Question 10 : Multilevel Queue : SRTF [Pre-emptive] +  Round Robin (Time Quantum = 2 Units) |  -----------\n\n");
	printf("\n | Enter the number of processes  | :  ");
	scanf("%d",&n);
	struct process p[n+1];
	for(i=0;i<n;i++)
	{
		p[i].pid=i+1;
		printf("\n | Enter The Arrival Time of Process P%d  | :  ",i+1);
		scanf("%d",&p[i].a);
		printf("\n | Enter The Burst Time of Process P%d  | : ",i+1);
		scanf("%d",&p[i].b);
		if(i%2==0)
		p[i].q=1;
		else
		p[i].q=2;
		
		p[i].c=0;
		p[i].t=0;
		p[i].temp_b=p[i].b;
	}	
	p[n].b=MAX;
	
	// Calculation :
	// query 1 = SRTF 
	// query 2 = Round Robin with Time Quantum = 2 units.
	// Note : Priority of Query 1 > Query 2

	int q2[n/2];
	int kq=0;
	for(i=1;i<n;i+=2)
	{
		q2[kq++]=i;
	} 
	int time=0;int count=0;
	int min=n;int run=-1;
	int cc=0;
	while(count != n)
	{
		min = n;
		for(i=0;i<n;i++)
		{
			if(p[i].a <= time)
			{
				if(p[i].q == 1 && p[i].b>0)
				{
					// queue 1 : SRTF Pre-emptive
					if(p[i].b < p[min].b)
					{
						min = i;
						run = min;
					}
				}
			}
		}
		if(min == n)                 // No process in queue 1
		{
			for(i=0;i<n/2;i++)
			{
				if(p[q2[i]].b==0)
				continue;
				run = q2[i];
				// shifting;
				for(j=i+1;j<n/2;j++)
				{
					q2[j-1]=q2[j];
				}
				q2[(n/2)-1]=run;
				break;
			}
		}
		p[run].b--;
		if(p[run].b == 0)
		{
		 	count++;
		 	p[run].c = time + 1;
            wait_time = wait_time + p[run].c - p[run].a - p[run].temp_b;
            turnaround_time = turnaround_time + p[run].c - p[run].a;
		}
		time++;
	}
    for(i=0;i<n;i++)
    {
    	p[i].w = p[i].c - (p[i].a + p[i].temp_b);
    	p[i].t = p[i].c - (p[i].a);
	}
    average_waiting_time = wait_time / n; 
    average_turnaround_time = turnaround_time / n;
    printScenario(p,n);
    printf("\n\n     --- | Average Waiting Time | : ---\t| %lf |\n", average_waiting_time);
    printf("\n     --- | Average Turn-Around Time | : ---\t| %lf |\n", average_turnaround_time);
    getch();
}

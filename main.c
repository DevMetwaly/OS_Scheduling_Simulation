#include <stdio.h>
#include <stdlib.h>
#define MAX_BURST 10
#define PRIORITY_LEVELS 5
#define MAX_ARRIVAL 8
#define MAX_PROCESSES 5
#define MAX_TIME 200
#define preemptive 1
#define nonpreemptive 0
#define true 1
#define false 0
#define bool int
/* Define a PCB (Process Control Block) */
struct process{
	int pid;
	int burst;
	int priority;
	int arrival;
};
typedef struct process Process;

/* Process initialization */
Process process_init(int,int,int,int);
void sort_readyQ(Process [],int);
void sort_readyQ_2(Process [],int);
void sort_readyQ_3(Process [],int,int);

/* Scheduling Algorithm Prototypes */
void fcfs(int [],Process [],int);
void sjf(int [],int p,Process [],int);
void hpf(int [],int p,Process [],int);
void rr(int [],Process [],int);

/* Display Gantt Chart of processes */
void gannt_chart(int []);

int main(){
	int i;
	int totalburst=0;
	int pid;
	int burst;
	int priority;
	int arrival;
	int pGannt[MAX_TIME];
	int n; // number of processes
	/* Define the ready queue */
	Process readyQ[MAX_PROCESSES]; //Array is used to implement the ready queue

	/* Initialize a ready queue */
	srand(time(0));
	n = (rand() % MAX_PROCESSES) + 1;
	pid = 1;
	while (pid<=n){
		burst = (rand() % MAX_BURST) + 1;
		priority = (rand() % PRIORITY_LEVELS);
		arrival = (rand()% MAX_ARRIVAL);
		readyQ[pid-1] = process_init(pid,burst,priority,arrival);
		totalburst += readyQ[pid-1].burst;
		pid +=1;
	}
	sort_readyQ(readyQ,n); //sort by arrival time
	/* Display Processes */
	printf("Processes in the Ready Queue: \n");
	for(i=0;i<n;i++){
		printf("P[%d]: arrival time = %d, burst time = %d, priority = %d\n",readyQ[i].pid,readyQ[i].arrival,readyQ[i].burst,readyQ[i].priority);
	}
	printf("-----------------------------------------------------------\n");
	/* Start scheduling algorithms */
	printf("\nFirst Come First Served Scheduling Gannt Chart:\n");
	fcfs(pGannt,readyQ,n);
	gannt_chart(pGannt);
	printf("\nNon-Preemptive Shortest Job First Scheduling Gannt Chart:\n");
	sjf(pGannt,nonpreemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nPreemptive Shortest Job First Scheduling Gannt Chart:\n");
	sjf(pGannt,preemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nNon-Preemptive Priority Scheduling Gannt Chart:\n");
	hpf(pGannt,nonpreemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nPreemptive Priority Scheduling Gannt Chart:\n");
	hpf(pGannt,preemptive,readyQ,n);
	gannt_chart(pGannt);
	printf("\nRound Robin Scheduling Gannt Chart:\n");
	rr(pGannt,readyQ,n);
	gannt_chart(pGannt);

	return 0;
}

Process process_init(int pid, int burst, int priority, int arrival){

	Process proc;
	proc.pid = pid;
	proc.burst = burst;
	proc.priority = priority;
	proc.arrival = arrival;
	return proc;
}

void sort_readyQ(Process readyQ[],int n){
	Process tempP;
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(readyQ[i].arrival > readyQ[j].arrival){
				tempP = readyQ[i];
				readyQ[i] = readyQ[j];
				readyQ[j] = tempP;
			}
		}
	}
}

void sort_readyQ_2(Process readyQ[],int n){
	Process tempP;
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(readyQ[i].burst > readyQ[j].burst){
				tempP = readyQ[i];
				readyQ[i] = readyQ[j];
				readyQ[j] = tempP;
			}
		}
	}
}
void sort_readyQ_3(Process readyQ[],int n,int i){
	Process tempP;
	int j;
	for(;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(readyQ[i].priority > readyQ[j].priority){
				tempP = readyQ[i];
				readyQ[i] = readyQ[j];
				readyQ[j] = tempP;
			}
		}
	}
}

/* Display Gannt chart */
void gannt_chart(int pGannt[]){
	int i=0;
	int j;
	int f = 0;
	int c=0;
	int pNow;
	printf("-------------------------------------------------------------\n");
	if(pGannt[0]!=-1){pNow = pGannt[0];}
	i = 0;
	while( i <MAX_TIME && pGannt[i]!=-1){
		if(pGannt[i]==pNow){
			f = 0;
			c++;
			i++;
		}
		else{
			f=1;
		}
		if(f==1){
			printf("|");
			for(j=1;j<=((2*c-2)/2);j++){
				printf(" ");
			}
			printf("P%d",pNow);
			for(j=1;j<=((2*c-2)/2);j++){
				printf(" ");
			}
			c = 0;
			pNow = pGannt[i];
		}
	}
	printf("|");
	for(j=1;j<=((2*c-2)/2);j++){
		printf(" ");
	}
	printf("P%d",pNow);
	for(j=1;j<=((2*c-2)/2);j++){
		printf(" ");
	}
	printf("|\n");
	printf("-------------------------------------------------------------\n");
}
/* Scheduling Algorithm Implementations */
void fcfs(int pGannt[], Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	int j;
	int t;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
	i = 0;
	t = 0;
	while(i<n){
		if(t<p[i].arrival){
			pGannt[t]=0;
			t++;
		}
		else {
			for(j=0;j<p[i].burst;j++){
				pGannt[t+j]=p[i].pid;
			}
			t = t + j;
			i+=1;
		}
	}
}
void ready_run(){

}
void sjf(int pGannt[],int preemption, Process readyQ[],int n){
	printf("okay\n");
	Process p[MAX_PROCESSES];
	int i;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
	if(preemption == nonpreemptive){

		//your code here
		Process p2[MAX_PROCESSES];
		int mi=0;
		int maxProcess=0;
		int i = 0;
		int t = 0;
		int j;
		while(mi<n){

			for(j=i;j<n;j++){
				if(t>=p[j].arrival){
					p2[maxProcess++]=p[j];
					i++;
				}
				else{
					break;
				}
			}

			if(mi<maxProcess){
				sort_readyQ_2(p2,maxProcess);
				while(p2[mi].burst--){
					pGannt[t++]=p2[mi].pid;
				}
				mi++;
			}else{
				pGannt[t++]=0;
			}


		}


	}
	if(preemption == preemptive){
		Process p2[MAX_PROCESSES];	//new queue (p2) to sort processes by burst time
		int mi=0;	//index for p2
		int noOfprocesses=0;	//number of processes in p2
		int t=0;	//time statr at zero
		int i=0;	//index for the ready queue
		int j;
		//loop over the time or untill the processes finish
		for(;t<MAX_TIME && mi!=n;t++){
			//check if a new process arrived ? and add it to p2 queue
			for(j=i;j<n && p[j].arrival<=t;j++){
					p2[noOfprocesses++]=p[j];
					i++;
			}

			sort_readyQ_2(p2,noOfprocesses);

			if(mi<noOfprocesses){
				pGannt[t]=p2[mi].pid;
				p2[mi].burst--;
			}else{
				pGannt[t]=0;
			}

			//get a new process from p2
			if(p2[mi].burst==0){
				mi++;
			}


		}
	}
}
void hpf(int pGannt[],int preemption,Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}
    if(preemption == nonpreemptive){
		//your code here
		Process p2[MAX_PROCESSES];
		int mi=0;
		int maxProcess=0;
		i = 0;
		int t = 0;
		int j;
		while(mi<n){

			for(j=i;j<n;j++){
				if(t>=p[j].arrival){
					p2[maxProcess++]=p[j];
					i++;
				}
				else{
					break;
				}
			}

			if(mi<maxProcess){
				sort_readyQ_3(p2,maxProcess,mi);
				while(p2[mi].burst--){
					pGannt[t++]=p2[mi].pid;
				}
				mi++;
			}else{
				pGannt[t++]=0;
			}


		}


	}
	if(preemption == preemptive){
		Process p2[MAX_PROCESSES];	//new queue (p2) to sort processes by burst time
		int mi=0;	//index for p2
		int noOfprocesses=0;	//number of processes in p2
		int t=0;	//time statr at zero
		int i=0;	//index for the ready queue
		int j;
		//loop over the time or untill the processes finish
		for(;t<MAX_TIME && mi!=n;t++){
			//check if a new process arrived ? and add it to p2 queue
			for(j=i;j<n && p[j].arrival<=t;j++){
					p2[noOfprocesses++]=p[j];
					i++;
			}

			sort_readyQ_3(p2,noOfprocesses,mi);

			if(mi<noOfprocesses){
				pGannt[t]=p2[mi].pid;
				p2[mi].burst--;
			}else{
				pGannt[t]=0;
			}
			//get a new process from p2
			if(p2[mi].burst==0 && mi<noOfprocesses){
				mi++;
			}
		}
	}
}
//function used by RR to insert and shift the processes' array
void inse(Process p2[],int i,int noOfprocess,Process p){
    int j= (i==-1)? 0:i;
    //insert the new process before the current process (i)
    Process temp;
    for(;j<noOfprocess;j++){
        temp=p2[j];
        p2[j]=p;
        p=temp;
    }
}
void rr(int pGannt[],Process readyQ[],int n){
	Process p[MAX_PROCESSES];
	int i;
	// clear time units (they will be loaded with pid of running processes)
	for(i=0;i<MAX_TIME;i++){
		pGannt[i]=-1;
	}
	//Copy ready queue in a temp queue
	for(i=0;i<n;i++){
		p[i]=readyQ[i];
	}


    //array to hold the arrived processes
    //i -> p2[i] -> process which will be executed
    //noOfprocess -> size of the array
    Process p2[MAX_PROCESSES];
    int noOfprocesses=0;
    i=-1;

    int t=0;

    int ii=0;//no processes arrived to the system
    int j;
    bool fre=true;//processor is ready or (idle) to take a new process
    int time_slice=3;
    int time_slice_start=0;

    for(;t<MAX_TIME;t++){
        //check if new  processes arrived
        for(j=ii;j<n && p[j].arrival<=t;j++){
            //insert the new process before the current process
            inse(p2,i,++noOfprocesses,p[j]);
            i++;
            ii++;
        }

        //if processor is free
        if(fre){

            if(noOfprocesses==0){
                i=-1;
            }else{
                i=(++i%noOfprocesses);
            }
            //get the first process that has burst time > 0
            int x=noOfprocesses+1;
            bool f=0;
            while(x--){
                if(p2[i].burst != 0){
                    f=1;
                    fre=false;
                    break;
                }
                i=(++i%noOfprocesses);
            }
            if(f) time_slice_start=t;
            //if all processes have been executed
            else if (noOfprocesses==n) return;

        }
        //preemption caused by the time slice
        else if((t-time_slice_start)%time_slice == 0 ){
            if(noOfprocesses==0){
                i=-1;
            }else{
                i=(++i%noOfprocesses);
            }
            int x=noOfprocesses+1;
            bool f=0;
            while(x--){
                if(p2[i].burst != 0){
                    f=1;
                    fre=false;
                    break;
                }

                i=(++i%noOfprocesses);
            }
        }
        if(i==-1){
            pGannt[t]=0;
            fre=true;
        }
        else if(p2[i].burst != 0){
            pGannt[t]=p2[i].pid;
            if(--p2[i].burst==0){
                fre=true;
            }else{
                fre=false;
            }
        }
        else{
            pGannt[t]=0;
            fre=true;
        }



    }

}

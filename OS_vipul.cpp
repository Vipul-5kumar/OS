/*Write a program in C which reads input CPU bursts from a the first line of a text file named as CPU_BURST.txt.
 Validate the input numbers whether the numbers are positive intergers or not. Consider the numbers as CPU burst.
 If there are 5 positive integers in the first line of the text file then the program treat those argument as
  required CPU bust for P1, P2, P3, P4, and P5 process and calculate average waiting time and average turn around time.
 Consider used scheduling algorithm as SJF and same arrival time for all the processes*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define FILE_NAME "CPU_BURST.txt"

struct Process{
	int Arrival_Time,Burst_Time,Wait_Time,TurnAround_Time;
	char name[4];
};

struct Process initialize(int Arrival_Time,int Burst_Time,int name){
	struct Process M;
	M.Burst_Time = Burst_Time;
	M.Arrival_Time = Arrival_Time;
	sprintf(M.name,"P%d",name+1);

	return M;
}

int main(){
	
	FILE *fp = fopen(FILE_NAME,"r");

	if(!fp)
		return -1*printf("FILE OPEN ERROR!\n");

    int d,i,j,count=0;

    int *queue = (int*)malloc(sizeof(int));

    //inputs are space separated integers on a single line of a txt file located in the same directory
    while(EOF != fscanf(fp,"%d ",&d )){
    	printf("%d ",d);
    	queue = (int*)realloc(queue,(count+1)*sizeof(int));
    	queue[count++] = d;
    }
    fclose(fp);

	//int queue[] = {3,1,3,2,4,5};
	
	struct Process P[count];

	for(i=0; i<count; i++)
		P[i] = initialize(0,queue[i],i);

	//sort
	for(i=1; i<count; i++){
		for(j=0; j<count-i; j++){
			if(P[j].Burst_Time>P[j+1].Burst_Time){
				struct Process temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	
	//FCFS non-preemptive [same arrival time]
	//after sorting we can apply FCFS which will result in SJF]
	printf("\nOrder : ");

	int elapse_T=0;
	for(i=0; i<count; i++){
		P[i].Wait_Time = elapse_T;
		P[i].tat= P[i].Wait_Time+P[i].bt;
		elapse_T += P[i].Burst_Time;

		printf("%s ",P[i].name);
	}
	//sort again
	for(i=1; i<count; i++){
		for(j=0; j<count-i; j++){
			if(P[j].name[1]>P[j+1].name[1]){
				struct Process temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	printf("\n\n%7s|%8s|%6s|%5s|%s\n","PROCESS","ARRIVAL","BURST","WAIT","TURNAROUND");
	
	int total_Wait_Time=0,total_TurnAround_Time=0;
	
	for(i=0; i<count; i++){
		total_Wait_Time+=P[i].Wait_Time;
		total_TurnAround_Time+=P[i].TurnAround_Time;
		printf("%7s|%8d|%6d|%5d|%9d\n",P[i].name,P[i].Arrival_Time,P[i].Burst_Time,P[i].Wait_Time,P[i].TurnAround_Time);
	}
	
	printf("\n average waiting time     : %.2f\n",total_Wait_Time*1.0/count);
	printf("\n average turn around time : %.2f\n",total_TurnAround_Time*1.0/count);
	
	return 0*printf("\n succesful exit\n");
}

/*A uniprocessor system has n number of CPU intensive processes, each process has its own requirement of CPU burst.
The process with lowest CPU burst is given the highest priority. 
A late arriving higher priority process can preempt a currently running process with lower priority. 
Simulate a scheduler that is scheduling the processes in such a way that higher priority process
is never starved due to the execution of lower priority process.
 What should be its average waiting time and average turnaround time if no two processes are arriving at same time.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <bits/stdc++.h>
 
struct Process {
    int Process_id;
    int Burst_Time; 
    int Arrival_Time;
};

void findWaitingTime(Process proc[], int n,
                                int Wait_Time[])
{
    int Remain_Time[n];
    for (int i = 0; i < n; i++)
        Remain_Time[i] = proc[i].Burst_Time;
 
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) {
	
        for (int j = 0; j < n; j++) {
            if ((proc[j].Arrival_Time <= t) &&
            (Remain_Time[j] < minm) && Remain_Time[j] > 0) {
                minm = Remain_Time[j];
                shortest = j;
                check = true;
            }
        }
 
        if (check == false) {
            t++;
            continue;
        }

        Remain_Time[shortest]--;

        minm = Remain_Time[shortest];
        if (minm == 0)
            minm = INT_MAX;
 
        if (Remain_Time[shortest] == 0) {
 
            complete++;
 
            finish_time = t + 1;
 
            wt[shortest] = finish_time -
                        proc[shortest].Burst_Time -
                        proc[shortest].Arival_Time;
 
            if (Wait_Time[shortest] < 0)
                Wait_Time[shortest] = 0;
        }
        t++;
    }
}
void findTurnAroundTime(Process proc[], int n,
                        int Wait_Time[], int Total_TurnAround_Time[])
{
    for (int i = 0; i < n; i++)
        Total_TurnAround_Time[i] = proc[i].Burst_Time + Wait_Time[i];
}
 
void findavgTime(Process proc[], int n)
{
    int Wait_Time[n], Total_TurnAround_Time[n], total_Wait_Time = 0,
                    Total_TurnAround_Time = 0;

    findWaitingTime(proc, n, Wait_Time);

    findTurnAroundTime(proc, n, Wait_Time, Total_TurnAround_Time);
 
    Printf("Processes, Burst time, Waiting time, Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt = total_Wait_Time + Wait_Time[i];
        Total_TurnAround_Time= Total_TurnAround_Time + Total_TurnAround_Time[i];
        Printf( "proc[i].pid,proc[i].Burst_Time, Wait_Time[i]Total_TurnAround_Time[i]");
    }
 
    Printf( "\nAverage waiting time = (float)total_Wait_Time / (float)n");
    Printf( "\nAverage turn around time = (float)Total_TurnAround_Time / (float)n");
}
 
int main()
{
    Process proc[] = { { 1, 6, 1 }, { 2, 8, 1 },
                    { 3, 7, 2 }, { 4, 3, 3 } };
    int n = sizeof(proc) / sizeof(proc[0]);
 
    findavgTime(proc, n);
    return 0;
}

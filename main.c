/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description: basic example of multi processing with fork() 
 *
 *        Version:  1.0
 *        Created:  06/03/2020 01:54:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Leon Löchner 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESS 3

void errExit(char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(){
	pid_t *pids = malloc(NUM_PROCESS * sizeof(pid_t));
	for (int i = 0 ; i < NUM_PROCESS ; i++){
		pids[i] = fork();
		if (pids[i] < 0){
			errExit("fork failed");
		}
		if (pids[i] == 0 ){
			printf("child is running...\n");
			sleep(10);
			exit(0);
		}
	}
	printf("parent waiting for children...\n");
	int status, pid;
	while ((pid = wait(&status)) > 0){
		printf("child process %d terminated with status %d\n", pid, WEXITSTATUS(status));
	}
}

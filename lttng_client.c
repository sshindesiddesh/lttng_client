#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pid = fork();
	char spid[200];
	/* Child Process */
	if (pid == 0) {
		int cpid = getpid();
		int pgid = getpgid(cpid);
		printf("PID : %d PGID : %d\n", cpid, pgid);

		/*
		// Test consecutive forks are traced
		int new_pid = fork();
		if (new_pid == 0) {
			int new_cpid = getpid();
			int new_pgid = getpgid(new_cpid);
			printf("PID : %d PGID : %d\n", new_cpid, new_pgid);
			exit(0);		
		}
		waitpid(new_pid, NULL, 0);
		while (1);
		*/

		char *lttng_script = "/home/siddesh/fsl/lttng_client/lttng_setup.sh";
		sprintf(spid, "%s %d", lttng_script, pgid);
		printf("CHILD: Executing : %s\n", spid);
		/* Setup lttng */
		system(spid);

		/* Execute readtest */
		char *exec_file = "readtest";
		char* const argv[] = {exec_file, NULL};
		char* const env[] = {NULL};
		execve(exec_file, argv, env);
	/* Parent Process */
	}
	int status;
	waitpid(pid, &status, 0);
	system("sudo lttng stop nsession");
	system("sudo lttng view nsession > a.txt");
	system("script -c \"sudo lttng view nsession | grep warning\" -f | grep warning | cut -d \" \" -f 4 | paste -sd+ | bc");
	system("sudo lttng destroy nsession");
	printf("Parent\n");
	return 0;
}

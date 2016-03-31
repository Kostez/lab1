#include <general.h>

sigset_t mask;
int signal_c=0;
char str[30][40];
int global_n_signals;
void mode_posix(int n_signals) {
	global_n_signals = n_signals;
	int i = 0;
	/*
	for(; i< 30*40; i++){
		str[0][i] = ' ';
	}
	
	for(; i< 30; i++){
		str[0][i*40] = '\0';
	}
*/	
	struct sigaction sa;
	struct sigaction saChild;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_mode;
	
	saChild.sa_flags = SA_SIGINFO;
	saChild.sa_sigaction = handler_posix_child;
	
	i=SIGRTMIN;
	for(; i<SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	saChild.sa_mask = mask;
	
	sigaction(SIGCHLD, &saChild, 0);
	
	sigprocmask(SIG_BLOCK, &mask, NULL);
	
	int diapozon = SIGRTMAX-SIGRTMIN;
	
	pid_t pid = fork();
	switch(pid) {
		case -1:
		{
			perror("fork err");
			exit(1);
		};
		case 0:
		{
			srand(time(0));
			int k=0;
			for(; k < n_signals; k++) {
				union sigval svalue;
				int random_signal;
				svalue.sival_int = rand()%100;
				random_signal = SIGRTMIN+rand()%diapozon;
				sigqueue(getppid(),random_signal,svalue);
				printf("%d\n", random_signal);
				fprintf(stderr,"CHILD: \t %i | %i | %i | %i | %i\n", k, getpid(), getppid(), random_signal, svalue.sival_int);
			}
			break;
		};
		default:
		{
			while(1){
				sleep(10);
			}
			break;
		};
	}
}

void handler_posix_child(int signal, siginfo_t *siginfo, void *context){
		if(signal_c< global_n_signals){
			sleep(1);
		}
		printf("%d\n", signal_c);
		int i=0;
		for(;i<signal_c;i++){
			printf("%s\n", str[i]);
		}
		
		int status = 0;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	
	int i = signal_c++;
	
	sigprocmask(SIG_BLOCK, &mask, NULL);

	sprintf(str[i], "PARENT\t %i | %i | %i | %i | %i", i, getpid(), getppid(), signal, siginfo->si_value.sival_int);
//	signal_c++;

}

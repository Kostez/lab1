#include <getopt.h>

struct params_s {
	modes_lab1 mode;
	int amount;
	int signalname;
	int pid;
};

enum modes_e {
	std = 0,
	child,
	posix,
	kill,
	pipe
};

int main(int argc, char *argv[]) {
	
	struct params_s par;
	
	const char* short_options = "m:a::s::p::";
	const char* modes[] = {"std", "child", "posix", "kill", "pipe"};
	
	const struct option long_options[] = {
		{"mode",required_argument,NULL,'m'},
		{"amount",optional_argument,NULL,'a'},
		{"signal",optional_argument,NULL,'s'},
		{"pid",optional_argument,NULL,'p'},
	};
	
	int rez;
	int option_index;
	
	while ((rez=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1){
			switch(rez){
			case 'm': {
				if(strcmp() == 0) {
					
				}
				break;
			};
			case 'a': {
				par.amount = atoi(optarg);
				break;
			};
			case 's': {
				par.signalname = atoi(optarg);
				break;
			};
			case 'p': {
				par.pid = atoi(optarg);
				break;
			};
	}
}

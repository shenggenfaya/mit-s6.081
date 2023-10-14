#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	int p2c[2];//0 is read,1 is write
	int c2p[2];
	pipe(p2c);
	pipe(c2p);	

	char buf1[4];
	char buf2[4];
	
	int pid = fork();
	
	if(pid > 0){//parent process
		close(p2c[0]);
		close(c2p[1]);
		write(p2c[1],"ping",4);
		if(read(c2p[0],buf1,sizeof(buf1))==4 && strcmp(buf1,"pong")==0){
			printf("%d: received pong\n",getpid());
		}
		close(p2c[1]);
		close(c2p[0]);
		exit(0);		
	}else if(pid == 0){//child process
		close(p2c[1]);
                close(c2p[0]);
                if(read(p2c[0],buf2,sizeof(buf2))==4 && strcmp(buf2,"ping")==0){
			printf("%d: received ping\n",getpid());
		}
		write(c2p[1],"pong",4);
                close(c2p[1]);
                close(p2c[0]);
		exit(0); 
	}
	return 0;
}

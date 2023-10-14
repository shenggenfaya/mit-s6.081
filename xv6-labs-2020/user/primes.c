#include "kernel/types.h"
#include "user/user.h"

#define NUM 36
int flag;
int a;

void getPrime(int r,int w){
	int num[NUM];
	read(r,num,sizeof(num));
	flag = 0;
	for(int i=0;i<36;i++) {
		if(num[i] == 1){
			a = i;
			flag = 1;
			break;	
		}
	}
	if(!flag) exit(0);
	printf("prime %d\n",a);
	
	for(int i=a;i<36;i+=a){
		num[i] = 0;
		//printf("%d ",i); 
	}
	//printf("\n");
	
	int pid = fork();
	if(pid > 0){
		write(w,num,sizeof(num));
		wait(0);
		exit(0);
	}else if(pid == 0){
		getPrime(r,w);
		wait(0);
		exit(0);
	}
	
}

int main(int agrc, char* agrv[]){
	int num[NUM];
	for(int i=0;i<36;i++) num[i] = 1;
	num[0] = 0;
	num[1] = 0;
	int fd[2];
	pipe(fd);
	
	int pid = fork();
	if(pid > 0){
		//close(fd[0]);
		write(fd[1],num,sizeof(num));
		//close(fd[1]);
		wait(0);
		exit(0);
	}else if(pid == 0){
		getPrime(fd[0],fd[1]);
		wait(0);
		exit(0);
	}
	return 0;
}

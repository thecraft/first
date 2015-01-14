/*************************************************************************
	> File Name: test.c
	> Author: hobson
	> Mail: song1919@163.com 
	> Created Time: 2015年01月14日 星期三 12时26分22秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "bc_epoll.h"
#include "console.h"

void* thread_fun(void *obj) {
	while(1) {
		printf("run...\n");
		bc_epoll_process(obj);
	}
}

static void *obj;
int main()
{
	void *obj = NULL;
	struct epoll_event ev;
	pthread_t pid;
	int fd;
    int n,nread,i;
    char buff[1024]={0};
	int freq = 9600;

    if((fd=open_port(fd,1))<0)
    {
        perror("open_port error");
        return;
    }
    if((i=set_opt(fd,freq,8,'N',0))<0)
    {
        perror("set_opt error");
        return;
    }
    printf("fd=%d\n",fd);
/*
	sprintf(buff, "ATHBT\n");
	sprintf(buff, "ATRON\r\n");
	printf("%s\n", buff);
	n=write(fd,buff,strlen(buff));
	printf("write:%d\n", n);
	while(1) {
		memset(buff, 0, sizeof(buff));
		nread=read(fd,buff,1024);
		printf("nread=%d,%s\n",nread,buff);
		sleep(1);
	}
*/	
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;

	obj = bc_epoll_create();
	bc_epoll_add_evt(obj, &ev);
	
	pthread_create(&pid, NULL, thread_fun, obj);
	pthread_join(pid, NULL);

	close(fd);
	return 0;
}



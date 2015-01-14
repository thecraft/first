/*************************************************************************
	> File Name: bc_epoll.c
	> Author: hobson
	> Mail: song1919@163.com 
	> Created Time: 2015年01月13日 星期二 18时19分55秒
 ************************************************************************/
#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "bc_epoll.h"

#define MAXEPOLLSIZE 10000
#define MAXLINE 10240

typedef struct bc_epoll bc_epoll_t;

struct bc_epoll {
    int efd;
	struct epoll_event *evts;
    int evt_monitor;
    //agn_queue_head_t tmr_q;
};

void *bc_epoll_create() 
{
	bc_epoll_t *epoll = NULL;

	epoll = (bc_epoll_t*)malloc(sizeof(*epoll));
    memset(epoll, 0, sizeof(*epoll));

    epoll->efd = epoll_create(MAXEPOLLSIZE);
	epoll->evts = (struct epoll_event*)malloc(MAXEPOLLSIZE * sizeof(struct epoll_event*)); 
    epoll->evt_monitor = 0;
    //agn_queue_init(epoll->tmr_q);
 
	return (void*)epoll;
}

void bc_epoll_delete(void *epoll_obj)
{
	bc_epoll_t *epoll = (bc_epoll_t*)epoll_obj;
	if(epoll == NULL) {
		return;
	}
	free(epoll);
}

int bc_epoll_add_evt(void *epoll_obj, struct epoll_event *evt)
{
	int ret = -1;
	int fd = evt->data.fd;
	bc_epoll_t *epoll = (bc_epoll_t*)epoll_obj;

	if(epoll->evt_monitor >= MAXEPOLLSIZE) {
		return ret;
	}
    if (epoll_ctl(epoll->efd, EPOLL_CTL_ADD, fd, evt) < 0) {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", fd);
        return ret;
	}
	++epoll->evt_monitor;
	ret = 0;
	printf("hobson:here\n");
	return ret;
}

int bc_epoll_del_evt()
{
	int ret = -1;
	return ret;
}

int bc_epoll_process(void *epoll_obj)
{
	bc_epoll_t *epoll = (bc_epoll_t*)epoll_obj;
	int curfds = epoll->evt_monitor;
	int nfds = 0, n;
	struct epoll_event *evts = epoll->evts;

	for (;;) {
        /* 等待有事件发生 */
        nfds = epoll_wait(epoll->efd, evts, curfds, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }
        /* 处理所有事件 */
        for (n = 0; n < nfds; ++n)
        {
            if (handle(epoll->evts[n].data.fd) < 0) {
                epoll_ctl(epoll->efd, EPOLL_CTL_DEL, evts[n].data.fd, NULL);
				--epoll->evt_monitor;
           }
        }
    }
	return 0;    
}

int handle(int fd) 
{
    int nread;
    char buf[MAXLINE];
    nread = read(fd, buf, MAXLINE);

    if (nread == 0) {
        printf("client close the connection\n");
        close(fd);
        return -1;
    }
    if (nread < 0) {
        perror("read error");
        close(fd);
        return -1;
    }
	printf("read:%d[%.*s]\n", nread, nread, buf);
    //write(fd, buf, nread);//响应客户端
    return 0;
}



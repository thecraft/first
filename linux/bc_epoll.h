/*************************************************************************
	> File Name: bc_epoll.h
	> Author: hobson
	> Mail: song1919@163.com 
	> Created Time: 2015年01月14日 星期三 14时13分42秒
 ************************************************************************/

#ifndef BC_EPOLL_H_
#define BC_EPOLL_H_

#include <sys/epoll.h>

void *bc_epoll_create();
void bc_epoll_delete(void *epoll_obj);
int bc_epoll_add_evt(void *epoll_obj, struct epoll_event *evt);
int bc_epoll_del_evt();
int bc_epoll_process(void *epoll_obj);

#endif


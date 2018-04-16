#ifndef P_THREAD00_H_
	#define P_THREAD00_H_
#endif
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <string>
struct p_thread_{
	
};

class p_thread{
	private:
		int number_thread;
	public:
		void create_thread();
		void release_thread();
		void sleep_thread();
		void waitup_thread();

};

void p_thread::thread_Func(void *args)
{
	struct epoll_event *event_s_=args;
	
	for(int i=0;i<1000;i++)
	{
		struct epoll_event event_s=event_s_[i];
		if(event_s.events&EPOLLIN)//data input
		{
			int fd=event_s.data.fd;
			char str[2048];
			memset(&str,0,sizeof(str));
			while(recv(fd,str,sizeof(char)*2048,0)>0)
			{

			}
		
		epoll_ctl(epfd,EPOLL_CTL_MOD,event_s[i].data.fd,&my_event);
	}
	else if(event_s[i].events&EPOLLOUT)
	{

	}
	else if(event_s[i].events&EPOLLHUP)
	{

	}
	else
	{

	}

	}
	
	

}

void p_thread::create_thread()
{
	pthread_t * pthread_id = new pthread_t[number_thread];
		for(int i=0;i<number_thread;i++)
		{
			pthread_create(&pthread_id[i],NULL,thread_Func,NULL);
		}

}
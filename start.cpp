#include "my_include.h"
#ifndef MAX_USER_
	#define MAX_USER_
	#define MAX_USER 5000
#endif

#ifndef MAX_EPOLL_WAIT_
	#define MAX_EPOLL_WAIT_
	#define MAX_EPOLL_WAIT 1000
#endif
using namespace std;
list <int> list_fd;
static struct epoll_event event_s[MAX_USER];
//聊天室服务器
//初步目标，实现聊天功能，使用epoll，先匿名，后注册
string int_tostring(int number)
{
	return (stringstream()<<number).str();
}

void send_all(SOCKET fd)
{
	int len=0;
	char message[2048];
	bzero(message,2048);
	char message1[2058];
	bzero(message1,2058);
	string str;
	int recv_num=0;
	//ioctl(fd, FIONBIO, 1);
	list<int>::iterator iter;
	
	/*for(iter=list_fd.begin();iter!=list_fd.end();iter++)
	{
			cout<<"iter"<<*iter<<endl;
	}*/
	
	if((recv_num=recv(fd,message,2048,0))>0)
	{
		str.append(int_tostring(fd));
		str.append(":");
		str+=message;
		int length = str.copy(message,recv_num);
		message[length]='\0';
		//cout<<"recv_num:"<<recv_num<<endl;
		for(iter=list_fd.begin();iter!=list_fd.end();iter++)
		{
			send(*iter,message1,sizeof(message1),0);
		}
		if(recv_num>0)
		{
			cout<<message1<<endl;
			//sleep(100000);
		}
		
	}
	if(recv_num==-1)
	{
		cout<<"fd:"<<*list_fd.begin()<<endl;
		perror("recv error:");
	}
	if(recv_num==0)
	{
		close(fd);
		list_fd.remove(fd);
	}

}

void send_all(SOCKET fd,char * send_ch,int send_len)
{
	list<int>::iterator iter;
	for(iter=list_fd.begin();iter!=list_fd.end();iter++)
	{
			
		if(send(*iter,send_ch,send_len,0)==-1)
		{
			perror("send_all error:");
		}
	}

}



//监听请求，如果有accept，先判断聊天室存在与否，存在，则加入，不存在，则创建。
int main()
{

	server start;
	SOCKET accept_fd=0;
	SOCKET server_listen=socket(AF_INET,SOCK_STREAM,0);
	
	int nfds=0;
	start.init_environment(server_listen);
	int epfd=epoll_create(MAX_USER);
	struct epoll_event my_event;
	char welcome_speak[]="Welcome to Speak!";

	my_event.events=EPOLLIN|EPOLLHUP;
	my_event.data.fd=server_listen;


	if(epoll_ctl(epfd,EPOLL_CTL_ADD,server_listen,&my_event))
	{
		perror("epoll error:");
	}
	struct epoll_event event_s[MAX_USER];
	for(int i=0;i<MAX_USER;i++)
	{
		bzero(&event_s[i],sizeof(my_event));
	}
	//ioctl(server_listen, FIONBIO, 1);
	cout<<"server fd:"<<server_listen<<endl;
	while(1)
	{
		nfds=epoll_wait(epfd,event_s,MAX_USER,50);

		/*for(int loop=0;loop<nfds;loop++)
		{
			//cout<<nfds<<endl;
			if(event_s[loop].data.fd==server_listen)
			{
				cout<<"event_s["<<loop<<"].data.fd"<<event_s[loop].data.fd<<endl;
			}
		}*/



		for(int loop=0;loop<nfds;loop++)
		{
			if(event_s[loop].data.fd==server_listen)
			{
				accept_fd=accept(server_listen,NULL,NULL);
				if(accept_fd==-1)
				{
					perror("accept fail");
				}
				my_event.data.fd=accept_fd;
				cout<<"accept fd:"<<accept_fd<<endl;
				epoll_ctl(epfd,EPOLL_CTL_ADD,accept_fd,&my_event);
				list_fd.push_back(accept_fd);
				send_all(accept_fd,welcome_speak,sizeof(welcome_speak));
			}
			else if(event_s[loop].events&EPOLLIN)
			{
				//cout<<"GET data!"<<endl;
				send_all(event_s[loop].data.fd);
				//epoll_ctl(epfd,EPOLL_CTL_MOD,server_listen,&my_event);
			}
			else if(event_s[loop].events&EPOLLHUP)
			{
				list_fd.remove(event_s[loop].data.fd);
			}

		}


	}
	close(epfd);
	close(server_listen);
	start.clear_server();

	



	return 0;
	
}
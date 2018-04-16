#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <unistd.h>
#include <list>
#include <string.h>
#include <stringstream>
using namespace std;

int main()
{
	int client_fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(65520);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(client_fd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("error for connect");
	}
	char ch[2048];
	char recv_ch[2048];
	bzero(recv_ch,2048);
	bzero(ch,2048);
	int recv_h=0;
	//ioctl(client_fd, FIONBIO, 1);
	while(1)
	{
		cout<< "Please input:"<<endl;
		cin.get();
		scanf("%s",ch);
		cout<<"this send:"<<ch<<endl;
		if(send(client_fd,ch,2048,0)<=0)
		{
			perror("error send:");
		}
		
		if((recv_h=recv(client_fd,recv_ch,2048,0))>0)
		{
			cout<<"recv_ch:"<< recv_ch<<endl;
		}
		if(recv_h==-1)
		{
			perror("recv error:");
		}
		//break;	
	}
	return 0;

}
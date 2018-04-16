#ifndef SERVER00_H_
	#define SERVER00_H_
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
#ifndef MAX_USER_
	#define MAX_USER_
	#define MAX_USER 100001
#endif

#ifndef PORT_
	#define PORT_
	#define port 65520
#endif

#ifndef SOCKET_
	#define SOCKET_ 
	#define SOCKET int
#endif

class server
{
    private:
    	struct sockaddr_in* local;
        SOCKET server_listen;

    public:
    	void init_environment(SOCKET server_li);
    	int server_accept();
    	void fd_node();
    	void clear_server();

};

void server::init_environment(SOCKET server_li)
{
	local=new struct sockaddr_in;
	server_listen=server_li;

	local->sin_family=AF_INET;
    local->sin_port=htons(port);
    local->sin_addr.s_addr=htonl(INADDR_ANY);
    if((bind(server_listen,(struct sockaddr*)local,sizeof(struct sockaddr))))
    {
    	perror("server bind error!\n");
    }
    if((listen(server_listen,1024)))
    {
    	perror("server listen error!\n");
    }

}

int server::server_accept()
{
	int accept_fd=accept(server_listen,NULL,NULL);
	if(accept_fd==-1)
	{
		perror("accept fail");
		return 0;
	}
	else if(accept_fd>0)
	{
		return accept_fd;
	}
	else
	{
		return 0;
	}
	return 0;
}

void server::clear_server()
{
	if(local)
	{
		delete local;
	}
	
}
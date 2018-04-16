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
#include <list>
#include <string.h>
#include <stdlib.h>
#include <string>
/*
#ifndef P_THREAD_
	#define P_THREAD_
	#include "p_thread.h"
#endif*/

#ifndef SERVER_
	#define SERVER_
	#include "server.h"
#endif

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
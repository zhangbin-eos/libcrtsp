
/******************************************************************************
Copyright (C) 2019 Zhangbin All rights reserved.

LIG SOURCE FILE
******************************************************************************
File Name	  : rtsp-server.c
Version 	  : Initial Draft
Author		  : zhangbin.eos@foxmail.com
Created 	  : 2/07/2019
Last Modified :
Description   :
Function List :

**************************************************************************/

/*=============include================================*/
#include "libcrtsp-log.h"

#include "rtsp-server.h"
#include "rtsp-msg.h"
#include "rtsp.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <pthread.h>


/*=============STATIC DEF=============================*/
#define THIS_MODULE_NAME "rtsp-server"

#ifdef RTSP_DEBUG_ENABLE
	#define pr_rtsp_server_log(lv,fmt,args...)                pr_log(lv,THIS_MODULE_NAME,fmt,##args)
#else
	#define pr_rtsp_server_log(lv,fmt,args...)                /* do nothing */
#endif

/*=============STATIC ENUM============================*/

/*=============STATIC STRUCT==========================*/
struct rtsp
{
	int rtsp_socket;
};

/*=============STATIC FUNC_DEF========================*/
int accept_connect(int socket_ser_fd);

/*=============STATIC VALUE===========================*/
//=============STATIC INLINLE=========================*/

/*=============EXTERN VALUE===========================*/

/*=============EXTERN FUNC============================*/
int rtsp_server_open(char *root, int port)
{
	struct sockaddr_in sev_addr;
	int sev_fd;
	int s32res;
	int reuse;

	/*
	   需要注册信号处理
	 */
	bzero(&sev_addr, sizeof(sev_addr));
	sev_addr.sin_family = AF_INET;
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sev_addr.sin_port = htons(554);

	sev_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == sev_fd)
	{
		pr_log_error("socket set up fail,please check it\n");
		return -1;
	}

	s32res =
	    bind(sev_fd, (const struct sockaddr *)(&sev_addr),
		 sizeof(sev_addr));

	if (-1 == s32res)
	{
		pr_log_error("bind socket error ,please check it\n");
		return -1;
	}

	//打开端口复用，防止退出占用
	reuse = 1;
	s32res =
	    setsockopt(sev_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	s32res = listen(sev_fd, 3);

	if (-1 == s32res)
	{
		pr_log_error("listen the socket fail,please check it\n");
		return -1;
	}

	/*
	   接收客户端的链接
	 */
	accept_connect(sev_fd);

	return sev_fd;
}

int rtsp_server_close(void)
{
	//1. close sub process
	//2. close sub threads
	//3. close server socket
}

/*=============STATIC FUNC----===================== ==*/
int connect_process(int socket_client_fd)
{
	char buff[4096];
	int s32res;
	struct rtsp_msg * msg;
	while (1)
	{
		s32res=recv(socket_client_fd, buff, sizeof(buff), 0);
		if (s32res == 0)
		{
			continue;
		}
		else if (s32res == -1)
		{
			pr_log_error("Error in receiving response from server \n");
			exit(1);
		}
		buff[s32res]=0;
		printf("recv \n{%s}\n",buff);
		/*分析接收到的请求*/
		
		msg = rtsp_msg_new( s32res );
		if (rtsp_msg_parse(msg)<0)
		{
			rtsp_msg_free( msg );
			return -1;
		}
		pr_log_info("client request: '%s' '%s' '%s'",
				msg->sl.req.method, msg->sl.req.uri,
				msg->proto_id );
	
		s32res = rtsp_msg_handle( msg );
		
		rtsp_msg_free( msg );
	}
}

static void *accept_thread(void *param)
{
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_size;

	int socket_client_fd;
	int socket_server_fd;

	socket_server_fd = *(int *)param;
	pid_t childPid;

	cli_addr_size = sizeof(cli_addr);

	while (1)
	{
		socket_client_fd =
		    accept(socket_server_fd, (struct sockaddr *)(&cli_addr),
			   &(cli_addr_size));

		if (-1 == socket_client_fd)
		{
			printf("accept client connect error,please check it\n");
		}

		/*
		   为新的链接创建子进程
		 */
		 
		if ((childPid = fork()) == 0)
		{
			char process_name[128]={0};
			
			sprintf(process_name,"",cli_addr.sin_addr);
			
                	prctl(PR_SET_NAME,proc_info->name,NULL,NULL,NULL);
			connect_process(socket_client_fd);
		}

		close(socket_client_fd);	//关闭客户端套接字
	}

}

int accept_connect(int socket_ser_fd)
{
	pthread_attr_t a;
	pid_t pid;
	int s32res;

	pthread_attr_init(&a);

#ifndef PTHREAD_CREATE_DETACHED
#define 	PTHREAD_CREATE_DETACHED 1
#endif

	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
	s32res =
	    pthread_create(&pid, &a, accept_thread, (void *)&socket_ser_fd);

	if (s32res != 0)
	{
		printf(" pthread_create error ");
		return -1;
	}
	return s32res;
}

//end rtsp-server.c

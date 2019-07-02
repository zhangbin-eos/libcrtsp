/******************************************************************************
 LIG HEAD FILE
 ******************************************************************************
  File Name 	: rtsp-server.h
  Version		: Initial Draft
  Author		: zhangbin
  Created		: 2/07/2019
  Last Modified :
  Description	:
  Function List :

**************************************************************************/
#ifndef __RTSP_SERVER_H__
#define __RTSP_SERVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

	/*=============include================================*/

	/*=============EXTERN DEF=============================*/

	/*=============EXTERN ENUM============================*/

	/*=============EXTERN STRUCT==========================*/

	/*=============EXTERN VALUE===========================*/

	/*=============EXTERN FUNC============================*/

	/*******************************
	-Function Name :rtsp_server_open
	-Description   :
	-Call          :
	-Called By     :
	-Input	Param  :
	-Return Value  :
	-Author        : zhangbin.eos@foxmail.com 2019/7/2
	*********************************/
	extern int rtsp_server_open(char *root, int port);

	extern int rtsp_server_close(void);

#ifdef __cplusplus
}

#endif

#endif				//__RTSP_SERVER_H__

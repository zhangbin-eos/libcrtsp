/******************************************************************************
  Copyright (C) 2019 Liguo Ltd. All rights reserved.

  LIG SOURCE FILE
 ******************************************************************************
  File Name     : test_rtsp_server.c
  Version       : Initial Draft
  Author        : zhangbin.eos@foxmail.com
  Created       : 2/07/2019
  Last Modified :
  Description   :
  Function List :

**************************************************************************/

/*=============include================================*/
#include "rtsp-server.h"

/*=============STATIC DEF=============================*/

/*=============STATIC ENUM============================*/

/*=============STATIC STRUCT==========================*/

/*=============STATIC FUNC_DEF========================*/

/*=============STATIC VALUE===========================*/

//=============STATIC INLINLE=========================*/

/*=============EXTERN VALUE===========================*/

/*=============MAIN FUNC============================*/
int main(int argc, char **argv)
{
	rtsp_server_open("/",554);
	while(1);
	rtsp_server_close();
	return 0;
}

/*=============STATIC FUNC----===================== ==*/

//end test_rtsp_server.c

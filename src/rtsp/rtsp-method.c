/******************************************************************************
  Copyright (C) 2019 Liguo Ltd. All rights reserved.

  LIG SOURCE FILE
 ******************************************************************************
  File Name     : rtsp-method.c
  Version       : Initial Draft
  Author        : zhangbin.eos@foxmail.com
  Created       : 2/07/2019
  Last Modified :
  Description   :
  Function List :

**************************************************************************/

/*=============include================================*/
#include "rtsp-method.h"
#include "libcrtsp-log.h"


/*=============STATIC DEF=============================*/
#define THIS_MODULE_NAME "rtsp-method"

#ifdef RTSP_MSG_DEBUG_ENABLE
	#define pr_rtsp_method_log(lv,fmt,args...)                pr_log(lv,THIS_MODULE_NAME,fmt,##args)
#else
	#define pr_rtsp_method_log(lv,fmt,args...)                /* do nothing */
#endif


/*=============STATIC ENUM============================*/


/*=============STATIC STRUCT==========================*/


struct rtsp_method {

	const char * name;
	int (func*)(void*);
}



/*=============STATIC FUNC_DEF========================*/

static int handle_DESCRIBE( void * arg );
static int handle_GET_PARAMETER( void * arg );
static int handle_OPTIONS( void * arg );
static int handle_PAUSE( void * arg );
static int handle_PLAY( void * arg );
static int handle_PLAY_NOTIFY( void * arg );
static int handle_REDIRECT( void * arg );
static int handle_SETUP( void * arg );
static int handle_SET_PARAMETER( void * arg );
static int handle_TEARDOWN( void * arg );
static int handle_unknown( void * arg );

/*=============STATIC VALUE===========================*/

static const struct rtsp_method m_rtsp_method_list[]=
{
	{"DESCRIBE", handle_DESCRIBE},
	{"GET_PARAMETER", handle_GET_PARAMETER},
	{"OPTIONS", handle_OPTIONS},
	{"PAUSE", handle_PAUSE},
	{"PLAY", handle_PLAY},
	{"PLAY_NOTIFY", handle_PLAY_NOTIFY},
	{"REDIRECT", handle_REDIRECT},
	{"SETUP", handle_SETUP},
	{"SET_PARAMETER", handle_SET_PARAMETER},
	{"TEARDOWN", handle_TEARDOWN},
	{"unknown", handle_unknown},
};

#define arry_len(arry)		(sizeof(arry)/sizeof(arry[0]))
//=============STATIC INLINLE=========================*/


/*=============EXTERN VALUE===========================*/




/*=============EXTERN FUNC============================*/

int rtsp_method_find( struct rtsp_msg *msg )
{
	int ret;
	int method_index=0;

	sizeof(m_rtsp_method_list)/sizeof(m_rtsp_method_list[0])
	
	for (;method_index<arry_len(m_rtsp_method_list);method_index++)
	{
		
		if( ! strcasecmp( msg->sl.req.method,
			m_rtsp_method_list[method_index].name) )
		{
			return = m_rtsp_method_list[method_index].func((void*)msg);
		}
	}
	
	return m_rtsp_method_list[arry_len(m_rtsp_method_list)-1].func((void*)msg);
}


/*=============STATIC FUNC=======================*/

static int handle_DESCRIBE( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;
}

static int handle_GET_PARAMETER( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_OPTIONS( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");

	return 0;

}


static int handle_PAUSE( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}


static int handle_PLAY( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_PLAY_NOTIFY( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_REDIRECT( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_SETUP( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_SET_PARAMETER( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_TEARDOWN( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

static int handle_unknown( void * arg )
{
	struct rtsp_msg *msg  = (struct rtsp_msg *)arg;
	pr_rtsp_method_log(LOG_DEBUG,"\n");
	return 0;

}

//end rtsp-method.c


/******************************************************************************
 LIG HEAD FILE
 ******************************************************************************
  File Name     : libcrtsp-log.h
  Version       : Initial Draft
  Author        : zhangbin
  Created       : 2/07/2019
  Last Modified :
  Description   :
  Function List :

**************************************************************************/
#ifndef __LIBCRTSP_LOG_H__
#define __LIBCRTSP_LOG_H__
#ifdef __cplusplus
extern "C" {
#endif

/*=============include================================*/
#include <syslog.h>
#include <stdio.h>

/*=============EXTERN DEF=============================*/
#define DEBUG_TO_NULL    0
#define DEBUG_TO_STDOU   1
#define DEBUG_TO_SYSLOG  2


//#define DEBUG_SWITCH DEBUG_TO_SYSLOG
#define DEBUG_SWITCH DEBUG_TO_STDOU


#if DEBUG_SWITCH==DEBUG_TO_SYSLOG
	#define pr_log_open()       openlog("core",LOG_NDELAY|LOG_PID,LOG_USER)
	#define pr_log_close()      closelog()

	#define pr_log(lvl,M,fmt,args...)	\
		syslog(lvl|LOG_USER,M"  func=[%s]"fmt,__FUNCTION__,##args)
		
	#define pr_log_debug(fmt,args...)	\
			pr_log(LOG_DEBUG,THIS_MODULE_NAME,fmt,##args)
	#define pr_log_info(fmt,args...)	\
			pr_log(LOG_INFO,THIS_MODULE_NAME,fmt,##args)
	#define pr_log_warning(fmt,args...)	\
			pr_log(LOG_WARNING,THIS_MODULE_NAME,fmt,##args)
	#define pr_log_error(fmt,args...)	\
			pr_log(LOG_ERR,THIS_MODULE_NAME,fmt,##args)

#elif DEBUG_SWITCH==DEBUG_TO_STDOU
	#include "stdio.h"
	#define pr_log_open()
	#define pr_log_close()
	#define pr_log(lvl,M,fmt,args...)	\
		fprintf(stdout,"<%d>"M"  func=[%s]"fmt,lvl,__FUNCTION__,##args)

	#define pr_log_debug(fmt,args...)	\
			pr_log(LOG_DEBUG,THIS_MODULE_NAME,fmt,##args)
	#define pr_log_info(fmt,args...)	\
			pr_log(LOG_INFO,THIS_MODULE_NAME,fmt,##args)
	#define pr_log_warning(fmt,args...)	\
			fprintf(stderr,"<%d>"THIS_MODULE_NAME"  func=[%s]"fmt,LOG_WARNING,__FUNCTION__,##args)
	#define pr_log_error(fmt,args...)	\
			fprintf(stderr,"<%d>"THIS_MODULE_NAME"  func=[%s]"fmt,LOG_ERR,__FUNCTION__,##args)

#else
	#define pr_log_open()
	#define pr_log_close()
	#define pr_log(lvl,M,fmt,args...)
	#define pr_log_debug(fmt,args...)
	#define pr_log_info(fmt,args...)
	#define pr_log_warning(fmt,args...)
	#define pr_log_error(fmt,args...)

#endif

#define RTSP_DEBUG_ENABLE
#define RTSP_MSG_DEBUG_ENABLE

#ifdef __cplusplus
}
#endif

#endif //__LIBCRTSP_LOG_H__


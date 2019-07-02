/******************************************************************************
 LIG HEAD FILE
 ******************************************************************************
  File Name     : rtsp-msg.h
  Version       : Initial Draft
  Author        : zhangbin
  Created       : 2/07/2019
  Last Modified :
  Description   :
  Function List :

**************************************************************************/
#ifndef __RTSP_MSG_H__
#define __RTSP_MSG_H__
#ifdef __cplusplus
extern "C" {
#endif

/*=============include================================*/

/*=============EXTERN DEF=============================*/

/*=============EXTERN ENUM============================*/

/*=============EXTERN STRUCT==========================*/

struct hdrf {
	char *name;
	char *value;
};

#define MAX_FIELDS	32

struct rtsp_msg {
	unsigned char *msg;
	int max_len;
	int msg_len;
	struct hdrf fields[MAX_FIELDS];
	int header_count;
	enum { PMSG_REQ, PMSG_RESP } type;
	char *proto_id;
	union {
		struct {
			char *method;
			char *uri;
		} req;
		struct {
			int code;
			char *reason;
		} stat;
	} sl;
};


/*=============EXTERN VALUE===========================*/

/*=============EXTERN FUNC============================*/


/*******************************
-Function Name :rtsp_msg_parse
-Description   :
-Call	       :
-Called By     :
-Input	Param  :
-Return Value  :
-Author        : zhangbin.eos@foxmail.com 2018/9/7
*********************************/
extern int rtsp_msg_parse(struct rtsp_msg * rtsp_msg)



#ifdef __cplusplus
}
#endif

#endif //__RTSP_MSG_H__


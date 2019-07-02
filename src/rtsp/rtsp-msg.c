/******************************************************************************
  Copyright (C) 2019 Liguo Ltd. All rights reserved.

  LIG SOURCE FILE
 ******************************************************************************
  File Name     : rtsp-msg.c
  Version       : Initial Draft
  Author        : zhangbin.eos@foxmail.com
  Created       : 2/07/2019
  Last Modified :
  Description   :
  Function List :

**************************************************************************/

/*=============include================================*/
#include "rtsp-msg.h"
#include "rtsp-method.h"
#include "libcrtsp-log.h"

#include <ctype.h>

/*=============STATIC DEF=============================*/

#define THIS_MODULE_NAME "rtsp-msg"

#ifdef RTSP_MSG_DEBUG_ENABLE
	#define pr_rtsp_msg_log(lv,fmt,args...)                pr_log(lv,THIS_MODULE_NAME,fmt,##args)
#else
	#define pr_rtsp_msg_log(lv,fmt,args...)                /* do nothing */
#endif

/*=============STATIC ENUM============================*/


/*=============STATIC STRUCT==========================*/

/*=============STATIC FUNC_DEF========================*/
static int inline delim( char *d, int len, char term1, char term2 )
{
	int s;

	for( s = 0; s < len; ++s )
		if( d[s] == term1 || d[s] == term2 ||
			       d[s] == '\r' || d[s] == '\n' )
			break;
	return s;
}


/*=============STATIC VALUE===========================*/


//=============STATIC INLINLE=========================*/


/*=============EXTERN VALUE===========================*/


/*=============EXTERN FUNC============================*/


struct rtsp_msg *rtsp_msg_new( int size )
{
	struct rtsp_msg *msg;
	void *v;

	if( ! ( v = malloc( sizeof( struct rtsp_msg ) + size ) ) )
	{
		pr_rtsp_msg_log( LOG_ERR, "unable to allocate memory for message" );
		return NULL;
	}
	msg = (struct rtsp_msg *)v;
	msg->msg = v + sizeof( struct rtsp_msg );
	msg->max_len = size;
	msg->msg_len = 0;
	msg->header_count = 0;
	msg->proto_id = NULL;
	return msg;
}

void rtsp_msg_free( struct rtsp_msg *msg )
{
	free( msg );
}

void rtsp_msg_clean( struct rtsp_msg *msg )
{
	msg->msg_len = 0;
	msg->header_count = 0;
	msg->proto_id = NULL;
	memset(msg->msg,0,msg->max_len);
}

int rtsp_msg_parse(struct rtsp_msg * msg)
{
	int i = 0;
	unsigned char *d = msg->msg;
	int len = msg->msg_len;

	msg->header_count = 0;

	/* Was it all whitespace? */
	if( len - i < 4 ) return -1;

	/* Check for a slash in the first word */
	for( i = 0; i < len && d[i] != ' ' && d[i] != '/'; ++i );
	if( i == len ) return -1;

	/* Responses begin with "PROTO/" */
	if( d[i] == '/' )
	{
		msg->type = PMSG_RESP;
		/* The first word is the protocol name and version */
		msg->proto_id = d;
		i = delim( d, len, ' ', 0 );
		/* Check for a space following the version number */
		if( d[i] != ' ' ) return -1;
		d[i++] = 0;
		while( i < len && d[i] == ' ' ) ++i;
		/* The next word is the 3-digit response code, then a space */
		if( len - i < 4 || ! isdigit( d[i] ) || ! isdigit( d[i+1] )
				|| ! isdigit( d[i+2] ) || d[i+3] != ' ' )
			return -1;
		msg->sl.stat.code = atoi( d + i );
		i += 4;
		while( i < len && d[i] == ' ' ) ++i;
		/* The rest of the line is the textual response */
		msg->sl.stat.reason = d + i;
		i += delim( d + i, len - i, 0, 0 );
		d[i++] = 0;
	} else
	{
		msg->type = PMSG_REQ;
		/* The first word is the method */
		msg->sl.req.method = d;
		i = delim( d, len, ' ', 0 );
		/* Then a space */
		if( i >= len || d[i] != ' ' ) return -1;
		d[i++] = 0;
		while( i < len && d[i] == ' ' ) ++i;
		/* The second word is the URI */
		msg->sl.req.uri = d + i;
		i += delim( d + i, len - i, ' ', 0 );
		/* Then a space */
		if( i >= len || d[i] != ' ' ) return -1;
		d[i++] = 0;
		while( i < len && d[i] == ' ' ) ++i;
		/* The last word is the protocol name and version */
		msg->proto_id = d + i;
		i += delim( d + i, len - i, 0, 0 );
		d[i++] = 0;
	}
	/* Skip any trailing space */
	while( i < len && d[i] == ' ' ) ++i;
	/* Skip the \r if we didn't kill it already */
	if( i < len && d[i] == '\r' ) ++i;
	/* We should be at the end of the line now */
	if( i >= len || d[i++] != '\n' ) return -1;

	/* Now, parse all the header lines */
	for(;;)
	{
		/* There may be a \r here if we're at the end of the headers */
		if( i < len && d[i] == '\r' ) ++i;
		/* If there's no more data, we're done */
		if( i == len ) return len;
		/* If there's a newline, we're at the end of the headers */
		if( d[i] == '\n' ) return i + 1;
		/* XXX headers beginning with whitespace are continuations */
		if( d[i] == '\t' || d[i] == ' ' ) return -1;
		/* The first thing on the line is the header name */
		msg->fields[msg->header_count].name = d + i;
		/* The name ends with optional spaces then a colon */
		i += delim( d + i, len - i, ' ', ':' );
		if( i >= len ) return -1;
		/* If the optional spaces are present, skip them */
		if( d[i] == ' ' )
		{
			d[i++] = 0;
			while( i < len && d[i] == ' ' ) ++i;
		}
		/* Make sure the colon is present */
		if( i >= len || d[i] != ':' ) return -1;
		d[i++] = 0;
		/* Skip any whitespace after the colon */
		while( i < len && ( d[i] == ' ' || d[i] == '\t' ) ) ++i;
		/* Everything else on the line is the header data */
		msg->fields[msg->header_count].value = d + i;
		i += delim( d + i, len - i, 0, 0 );
		d[i++] = 0;
		/* We should be at the end of the line now */
		if( i >= len || d[i++] != '\n' ) return -1;
		++msg->header_count;
	}

}


int rtsp_msg_handle( struct rtsp_msg *msg )
{
	return rtsp_method_find( msg);
}

/*=============STATIC FUNC----===================== ==*/



//end rtsp.c


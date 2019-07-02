
TARGET_TEST_RTSP_SERVER=test_rtsp_server
OBJS_TEST_RTSP_SERVER= test_rtsp_server.o\
$(foreach dir, ../src/rtsp/ ,$(patsubst %.c,%.o,$(wildcard $(dir)/*.c))) 

VPATH=../include/ ../src/rtsp/ ../src/rtp/ ../src/rtcp/ ../src/stream/


#-----------------------------------
CFLAGS= -I../include/
LDFLAGS= -pthread 



all:$(TARGET_TEST_RTSP_SERVER)

$(TARGET_TEST_RTSP_SERVER):$(OBJS_TEST_RTSP_SERVER)
	$(CC) $(LDFLAGS) -o $(TARGET_TEST_RTSP_SERVER) $(OBJS_TEST_RTSP_SERVER)

$(OBJS_TEST_RTSP_SERVER):%.o:%.c
	$(CC)  $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(TARGET_TEST_RTSP_SERVER) $(OBJS_TEST_RTSP_SERVER)

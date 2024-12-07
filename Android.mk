LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
 
LOCAL_SRC_FILES := MyThread.cpp \
	Main.cpp \
	
   
LOCAL_SHARED_LIBRARIES :=libandroid_runtime \
	libcutils \
	libutils \
        liblog 
	
LOCAL_MODULE := android_thread
 
	
LOCAL_PRELINK_MODULE := false
 
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
 
LOCAL_SRC_FILES := thread_posix.c 
	
LOCAL_MODULE := linux_thread
LOCAL_SHARED_LIBRARIES :=liblog  
	
LOCAL_PRELINK_MODULE := false
 
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := SocketClient.c

LOCAL_MODULE := rootclient
LOCAL_SHARED_LIBRARIES :=liblog

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := SocketServer.c

LOCAL_MODULE := rootServer
LOCAL_SHARED_LIBRARIES :=liblog

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := unix_client.c

LOCAL_MODULE := unixClient
LOCAL_SHARED_LIBRARIES :=liblog

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := unix_server.c

LOCAL_MODULE := unixServer
LOCAL_SHARED_LIBRARIES :=liblog

LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)

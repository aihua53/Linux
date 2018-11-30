# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	src/main.cpp \
#	src/test.c \


LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/inc 

LOCAL_LDLIBS    := -lm -llog
	
#LOCAL_CFLAGS += -pie -fPIE
#LOCAL_LDFLAGS += -pie -fPIE
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE:= setuid
include $(BUILD_EXECUTABLE)

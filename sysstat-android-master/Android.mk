# Copyright 2006-2014 The Android Open Source Project

LOCAL_PATH := $(call my-dir)

logcatLibs := liblog libbase libcutils libpcrecpp libutils \
	libhidlbase libhidltransport libipccommproto libsysutils

include $(CLEAR_VARS)

LOCAL_MODULE := mpstat
LOCAL_SRC_FILES := mpstat.c common.c rd_stats.c
LOCAL_SHARED_LIBRARIES :=  $(logcatLibs)

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_MODULE := pidstat
LOCAL_SRC_FILES := pidstat.c  common.c rd_stats.c
LOCAL_SHARED_LIBRARIES :=  $(logcatLibs)

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_MODULE := iostat
LOCAL_SRC_FILES := common.c rd_stats.c iostat.c ioconf.c
LOCAL_SHARED_LIBRARIES :=  $(logcatLibs)

include $(BUILD_EXECUTABLE)




include $(CLEAR_VARS)

LOCAL_MODULE := sar
LOCAL_SRC_FILES := common.c  ioconf.c sar.c sa_common.c activity.c
LOCAL_SHARED_LIBRARIES :=  $(logcatLibs)

include $(BUILD_EXECUTABLE)



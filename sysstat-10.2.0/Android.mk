BUILD_BLKTRACE := false

ifeq ($(BUILD_BLKTRACE), true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := mpstat.c
LOCAL_C_INCLUDES := external/sysstat-10.2.0/
LOCAL_CFLAGS := -O2 -g -W -Wall -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
LOCAL_MODULE := mpstat
LOCAL_MODULE_TAGS :=
LOCAL_SYSTEM_SHARED_LIBRARIES := libc
include $(BUILD_EXECUTABLE)


endif

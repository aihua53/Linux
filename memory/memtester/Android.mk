LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE := memtester
LOCAL_C_INCLUDES := ./inc
LOCAL_SRC_FILES := ./memtester.c \
	./tests.c 
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

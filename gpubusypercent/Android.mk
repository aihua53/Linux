LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE := getgpubusypercent
LOCAL_SRC_FILES := ./get_gpubusypercent.cpp
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

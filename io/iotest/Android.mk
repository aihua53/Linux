LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE := iotest
LOCAL_SRC_FILES := ./io.c
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

# LOCAL_PATH := $(call my-dir)
# include $(CLEAR_VARS)
# LOCAL_MODULE_TAGS:= optional
# LOCAL_MODULE := iotest2
# LOCAL_SRC_FILES := ./io_test.cpp
# LOCAL_MODULE_CLASS := EXECUTABLES
# LOCAL_MODULE_TAGS := optional
# include $(BUILD_EXECUTABLE)
# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := randomdevs
LOCAL_SRC_FILES := randomdevs.c
LOCAL_CFLAGS := -g
#LOCAL_LDLIBS    += -llog
#LOCAL_LDLIBS    += -lOpenSLES
#LOCAL_LDLIBS    += -landroid
include $(BUILD_EXECUTABLE)
#include $(BUILD_SHARED_LIBRARY)

USER_LOCAL_PATH:=$(LOCAL_PATH)
LOCAL_PATH:= $(call my-dir)

PATH_TO_OPENCV_SRC 	:= /home/lexhuang/opencv

include $(CLEAR_VARS)
include $(PATH_TO_OPENCV_SRC)/platforms/build_android_arm/OpenCV.mk
LIBTOF_HEAD_ABS:= include
LIBTOF_SRC_ABS:= src

LOCAL_MODULE := libtof
LOCAL_C_INCLUDES += \
		$(LIBTOF_HEAD_ABS)
LOCAL_SRC_FILES += \
		#$(LIBTOF_SRC_ABS)/capture.cpp \
		$(LIBTOF_SRC_ABS)/cnumpy.cpp \
		$(LIBTOF_SRC_ABS)/Device.cpp \
		$(LIBTOF_SRC_ABS)/Globals.cpp \
		$(LIBTOF_SRC_ABS)/regProg.cpp \
		$(LIBTOF_SRC_ABS)/tofmanager.cpp \
		$(LIBTOF_SRC_ABS)/voxelfw.cpp \
		$(LIBTOF_SRC_ABS)/voxelxu.cpp

# Optional compiler flags.
#LOCAL_LDLIBS   = -lz -lm
#LOCAL_CFLAGS   = -Wall -pedantic -std=c99 -g

include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH:=$(USER_LOCAL_PATH)

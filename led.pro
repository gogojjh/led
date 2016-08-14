TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include/opencv \
/usr/local/include/opencv2 \
/usr/local/include \
/home/gogojjh/QT/led/include

LIBS += /usr/local/lib/libopencv_core.so.2.4
LIBS += /usr/local/lib/libopencv_highgui.so.2.4
LIBS += /usr/local/lib/libopencv_calib3d.so.2.4
LIBS += /usr/local/lib/libopencv_gpu.so.2.4
LIBS += /usr/local/lib/libopencv_imgproc.so.2.4
LIBS += /usr/local/lib/libopencv_legacy.so.2.4
LIBS += /usr/local/lib/libopencv_ml.so.2.4
LIBS += /usr/local/lib/libopencv_objdetect.so.2.4
LIBS += /usr/local/lib/libopencv_ocl.so.2.4
LIBS += /usr/local/lib/libopencv_contrib.so.2.4
LIBS += /usr/local/lib/libopencv_core.so.2.4
LIBS += /usr/local/lib/libopencv_features2d.so.2.4
LIBS += /usr/local/lib/libopencv_flann.so.2.4
LIBS += /usr/local/lib/libopencv_photo.so.2.4
LIBS += /usr/local/lib/libopencv_stitching.so.2.4
LIBS += /usr/local/lib/libopencv_superres.so.2.4
LIBS += /usr/local/lib/libopencv_video.so.2.4
LIBS += /usr/local/lib/libopencv_videostab.so.2.4
LIBS += /usr/local/lib/libopencv_contrib.so.2.4
LIBS += /usr/local/lib/libopencv_core.so.2.4
LIBS += /usr/local/lib/libopencv_features2d.so.2.4
LIBS += /usr/local/lib/libopencv_nonfree.so.2.4

SOURCES += \
    src/main.cpp \
    src/base.cpp \
    src/contour.cpp \
    src/orbmatching.cpp

HEADERS += \
    include/led/base.h \
    include/led/contour.h \
    include/led/orbmatching.h


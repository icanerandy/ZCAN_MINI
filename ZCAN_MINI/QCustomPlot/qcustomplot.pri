
# 添加后必须重新编译rebuild，不然无法生效
Qt += opengl
DEFINES += QCUSTOMPLOT_USE_OPENGL

LIBS += -LD:/Qt/5.15.2/mingw81_32/lib  -llibfreeglut.dll -lopengl32

HEADERS += \
    $$PWD/qcustomplot.h \
    $$PWD/datatracer.h

SOURCES += \
    $$PWD/qcustomplot.cc \
    $$PWD/datatracer.cc

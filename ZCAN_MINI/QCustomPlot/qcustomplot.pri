
# 添加后必须重新编译rebuild，不然无法生效
Qt += opengl
DEFINES += QCUSTOMPLOT_USE_OPENGL

LIBS += -LD:/Software/Qt/Qt5.9.1/5.9.1/mingw53_32/lib  -lfreeglut -lopengl32

HEADERS += \
    $$PWD/qcustomplot.h \
    $$PWD/datatracer.h

SOURCES += \
    $$PWD/qcustomplot.cc \
    $$PWD/datatracer.cc

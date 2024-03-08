
# 添加后必须重新编译rebuild，不然无法生效
Qt += opengl
DEFINES += QCUSTOMPLOT_USE_OPENGL

mingw {
    LIBS += -LD:/Qt/5.15.2/mingw81_32/lib  -llibfreeglut.dll -lopengl32
}

msvc {
    LIBS += -LD:/Qt/5.15.2/msvc2019/lib  -lfreeglut -lopengl32
}

HEADERS += \
    $$PWD/myplot.h \
    $$PWD/plotdata.h \
    $$PWD/qcustomplot.h \
    $$PWD/replot.h

SOURCES += \
    $$PWD/myplot.cpp \
    $$PWD/plotdata.cpp \
    $$PWD/qcustomplot.cpp \
    $$PWD/replot.cpp

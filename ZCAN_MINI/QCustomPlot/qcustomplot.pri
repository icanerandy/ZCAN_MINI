
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
    $$PWD/deviationplot.h \
    $$PWD/deviationreplot.h \
    $$PWD/lineplot.h \
    $$PWD/linereplot.h \
    $$PWD/myplot.h \
    $$PWD/qcustomplot.h

SOURCES += \
    $$PWD/deviationplot.cpp \
    $$PWD/deviationreplot.cpp \
    $$PWD/lineplot.cpp \
    $$PWD/linereplot.cpp \
    $$PWD/myplot.cpp \
    $$PWD/qcustomplot.cpp

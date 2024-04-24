# HEADERS += $$PWD/components/*
@HEADERS = $$files($$PWD/components/*)@

# SOURCES += $$PWD/components/*
@SOURCES = $$files($$PWD/components/*)@

INCLUDEPATH += $$PWD/components/

CONFIG(debug, debug | release) {
    PRE_TARGETDEPS += $$PWD/staticlib/debug/components.lib

    LIBS += -L$$PWD/staticlib/debug/  -lcomponents
}
CONFIG(release, debug | release) {
    PRE_TARGETDEPS += $$PWD/staticlib/release/components.lib

    LIBS += -L$$PWD/staticlib/release/  -lcomponents
}

RESOURCES += \
    $$PWD/resources.qrc

INCLUDEPATH += $$PWD/include

mingw {
    LIBS += -L$$PWD/lib -llibVector_DBC.dll
}

msvc {
    LIBS += -L$$PWD/lib -lVector_DBC
}


INCLUDEPATH += $$PWD/include


@HEADERS = $$files($$PWD/include/spdlog/*.h)@

HEADERS += \
    $$PWD/include/spdlog_common.h

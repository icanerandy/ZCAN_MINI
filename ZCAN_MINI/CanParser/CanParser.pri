
# HEADERS += \
#     $$PWD/CANDatabase.h \
#     $$PWD/CANDatabaseAnalysis.h

# mingw {
#     LIBS += -L$$PWD/lib -llibcpp-can-parser.dll
# }

# msvc {
#     LIBS += -L$$PWD/lib -lcpp-can-parser
# }



HEADERS += \
           $$PWD/CANDatabase.h \
           $$PWD/CANDatabaseAnalysis.h \
           $$PWD/DBCParser.h \
           $$PWD/ParsingUtils.h \
           $$PWD/Tokenizer.h

SOURCES += \
           $$PWD/CANDatabase.cpp \
           $$PWD/CANFrame.cpp \
           $$PWD/CANFrameAnalysis.cpp \
           $$PWD/CANSignal.cpp \
           $$PWD/DBCParser.cpp \
           $$PWD/ParsingUtils.cpp \
           $$PWD/Tokenizer.cpp

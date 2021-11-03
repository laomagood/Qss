QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qss
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += /utf-8
CONFIG += c++11

#应用图标
RC_ICONS += logo.ico

#-------------------------------------
# Output directory
CONFIG(debug, debug|release) {
    output = debug
}
CONFIG(release, debug|release) {
    output = release
}

DESTDIR     = bin
OBJECTS_DIR = $$output
MOC_DIR     = $$output
RCC_DIR     = $$output
UI_DIR      = $$output

include(./util/util.pri)
include(./gui/gui.pri)
#include(./function/function.pri)
#-------------------------------------

SOURCES += \
    main.cpp

win32:
{
    # [1] 拷贝相关DLL
    SrcDir = $$PWD\\bin\\*.*
    DstDir = $$OUT_PWD\\bin\\

    # 将"/"替换为"\"
    # replace函数的第一个参数必须是大写
    SrcDir = $$replace(SrcDir, /, \\)
    DstDir = $$replace(DstDir, /, \\)

    message('------>')
    message('$$SrcDir')
    message('$$DstDir')

    system(xcopy $$SrcDir $$DstDir /y /e)

    # [2] 删除.exp .lib
    LibFile = $$OUT_PWD\\bin\\plugins\\*.lib
    ExpFile = $$OUT_PWD\\bin\\plugins\\*.exp
    LibFile = $$replace(LibFile, /, \\)
    ExpFile = $$replace(ExpFile, /, \\)
    QMAKE_POST_LINK += system(del $$LibFile)
    QMAKE_POST_LINK +=system(del $$ExpFile)
}

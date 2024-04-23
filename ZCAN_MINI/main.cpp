
#include <stdlib.h>
#include <crtdbg.h>
#include <QFile>
#include "main_window.h"
#include <QApplication>
#include <QFontDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("E:/repository/ZCAN_MINI/ZCAN_MINI/resources/style.qss");/*QSS文件所在的路径*/
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QString strFile = file.readAll();
        a.setStyleSheet(strFile);
        file.close();/*记得关闭QSS文件*/
    }

    // QFont font = QFontDialog::getFont(nullptr);
    // a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}

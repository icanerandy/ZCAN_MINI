#include "main_window.h"
#include <QApplication>
#include <QFontDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFont font;
//    bool ok = false;
//    font = QFontDialog::getFont(&ok, font, 0, "", QFontDialog::DontUseNativeDialog);
//    a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}

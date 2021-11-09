#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include "util/QssHelper.h"
#include "gui/form.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Form w;
    w.show();

    return a.exec();
}

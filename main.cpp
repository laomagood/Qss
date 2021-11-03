#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include "util/Util.h"
#include "util/QssHelper.h"
#include "gui/form.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Form w;
    w.show();
    QssHelper::instance()->setSkinStyle("blue");

//    QString strQssFile("./qss/Ma.qss");
//    Util::setSkinStyle(strQssFile);

//    QssHelper::instance()->getAllQssName();

//    qDebug() << QColor("#00BB9E").green();
    return a.exec();
}

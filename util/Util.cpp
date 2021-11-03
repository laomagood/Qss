#include "Util.h"
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QSettings>
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QApplication>
#include <QtEndian>
#include <QTimer>

QString Util::sizeToString(qint64 size)
{
    int count = 0;
    double f_size = size;
    while (f_size >= 1024) {
        f_size /= 1024;
        count++;
    }

    QString suffix;
    switch (count) {
    case 0 : suffix = " B"; break;
    case 1 : suffix = " KB"; break;
    case 2 : suffix = " MB"; break;
    case 3 : suffix = " GB"; break;
    case 4 : suffix = " TB"; break;
    }

    return QString::number(f_size, 'f', 2).append(suffix);
}

QString Util::getIniFilePath()
{
    // 获取配置文件中的文件夹路径config.ini
    QString strIniFilePath = QCoreApplication::applicationDirPath() + "/config" + "/config.ini";
    QFileInfo iniFileInfo(strIniFilePath);
    if(!iniFileInfo.isFile()) {
        qDebug() << "配置文件缺失";
        return QString();
    }

    return strIniFilePath;
}

QString Util::getQss(QString filePath)
{
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    if (file.isOpen()) {
        QString qssString = QLatin1String(file.readAll());
        file.close();
        return qssString;
    }
    return QString();
}

void Util::autoRunWithSystem(bool isAutoRun, QString appName, QString appPath)
{
    QSettings *reg = new QSettings(
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                QSettings::NativeFormat);

    if (isAutoRun) {
        reg->setValue(appName, appPath);
    } else {
        reg->setValue(appName, "");
    }
}

void Util::moveFormToCenter(QWidget *frm)
{
    int frmX = frm->width();
    int frmY = frm->height();

    QScreen *pScreen = QGuiApplication::screens().first();

    int deskWidth = pScreen->geometry().width();
    int deskHeight = pScreen->geometry().height();

    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

void Util::setSkinStyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString PaletteColor = qss.mid(13, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

unsigned char Util::checkSum(unsigned char *buf, int len)
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < len; i++) {
        sum += buf[i];
    }

    if(sum > 0xff) {
        sum = ~sum;
        sum += 1;
    }
    return (sum&0xff);
}

void Util::delayMSec(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

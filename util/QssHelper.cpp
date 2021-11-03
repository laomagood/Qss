#include "QssHelper.h"
#include <QDebug>
#include <QDirIterator>
#include <QApplication>
#include <QPalette>


QssHelper *QssHelper::instance()
{
    static QssHelper instance;
    return &instance;
}

QStringList QssHelper::getAllQssName() const
{
    QStringList filePath;

    QString strPath = "./qss/ini";
    QStringList filters;
    filters << "*.ini";

    QDirIterator iterator(strPath, filters, QDir::Files | QDir::NoSymLinks);
    while(iterator.hasNext()) {
        QFileInfo info(iterator.next());
        // filePath.append(info.filePath()); //文件目录+文件名
        filePath.append(info.baseName());
    }
    qDebug() << filePath;
    return filePath;
}

void QssHelper::setSkinStyle(const QString &t_name)
{
    getIniFileColor(t_name);
    replaceColorQssFile();
}

void QssHelper::getIniFileColor(QString t_nama)
{
    QString strPath = "./qss/ini/" + t_nama + ".ini";

    QSettings settings(strPath, QSettings::IniFormat);

    m_strPanelColor   = settings.value(QString("PanelColor")).toString();
    m_strTextColor    = settings.value(QString("TextColor")).toString();
    m_strBorderColor  = settings.value(QString("BorderColor")).toString();
    m_strNormalColor  = settings.value(QString("NormalColor")).toString();
    m_strDarkColor    = settings.value(QString("DarkColor")).toString();
    m_strHighColor    = settings.value(QString("HighColor")).toString();

    m_strCustomColor1 = settings.value(QString("CustomColor1")).toString();
    m_strCustomColor2 = settings.value(QString("CustomColor2")).toString();
    m_strCustomColor3 = settings.value(QString("CustomColor3")).toString();
    m_strCustomColor4 = settings.value(QString("CustomColor4")).toString();
}

void QssHelper::replaceColorQssFile()
{
    QString qss;

    QFile file("./qss/app.qss");
    if (file.open(QFile::ReadOnly)) {
        qss = QLatin1String(file.readAll());
    }

    qss.replace("PANELCOLOR",  m_strPanelColor );
    qss.replace("TEXTCOLOR",   m_strTextColor  );
    qss.replace("BORDERCOLOR", m_strBorderColor);
    qss.replace("NORMALCOLOR", m_strNormalColor);
    qss.replace("DARKCOLOR",   m_strDarkColor  );
    qss.replace("HIGHCOLOR",   m_strHighColor  );
    qss.replace("CUSTOMCOLOR1",m_strCustomColor1);
    qss.replace("CUSTOMCOLOR2",m_strCustomColor2);
    qss.replace("CUSTOMCOLOR3",m_strCustomColor3);
    qss.replace("CUSTOMCOLOR4",m_strCustomColor4);

    QString PaletteColor = qss.mid(13, 7);
    qApp->setPalette(QPalette(QColor(PaletteColor)));
    qApp->setStyleSheet(qss);
}

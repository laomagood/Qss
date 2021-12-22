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

QMap<QString, QString> QssHelper::getAllQssName() const
{
    QMap<QString, QString> map;

    // [1] 获取主题名称
    QStringList strList;
    QString strPath = "./qss/ini";
    QStringList filters;
    filters << "*.ini";

    QDirIterator iterator(strPath, filters, QDir::Files | QDir::NoSymLinks);
    while(iterator.hasNext()) {
        QFileInfo info(iterator.next());
        // filePath.append(info.filePath()); //文件目录+文件名
        strList.append(info.baseName());
    }

    // [2] 获取颜色
    for(auto str : strList) {
        QString strPath = "./qss/ini/" + str + ".ini";
        QSettings settings(strPath, QSettings::IniFormat);
        QString strColor = settings.value(QString("PanelColor")).toString();

        map.insert(str, strColor);
    }

    return map;
}

void QssHelper::setSkinStyle(const QString &t_name)
{
    getIniFileColor(t_name);
    replaceColorQssFile();

    QMap<QString, QString> map = getAllQssName();
    QString strColor = map.value(t_name);
    QPair<QString, QString> pair(t_name, strColor);
    emit skinChanged(pair);
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
    m_strDisabledColor= settings.value(QString("DisabledColor")).toString();
    m_strCheckedColor = settings.value(QString("CheckedColor")).toString();

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

    qss.replace("PANELCOLOR",  m_strPanelColor      ,Qt::CaseSensitive);
    qss.replace("TEXTCOLOR",   m_strTextColor       ,Qt::CaseSensitive);
    qss.replace("BORDERCOLOR", m_strBorderColor     ,Qt::CaseSensitive);
    qss.replace("NORMALCOLOR", m_strNormalColor     ,Qt::CaseSensitive);
    qss.replace("DARKCOLOR",   m_strDarkColor       ,Qt::CaseSensitive);
    qss.replace("HIGHCOLOR",   m_strHighColor       ,Qt::CaseSensitive);
    qss.replace("DISABLEDCOLOR",m_strDisabledColor  ,Qt::CaseSensitive);
    qss.replace("CHECKEDCOLOR", m_strCheckedColor   ,Qt::CaseSensitive);

    qss.replace("CUSTOMCOLOR1",m_strCustomColor1    ,Qt::CaseSensitive);
    qss.replace("CUSTOMCOLOR2",m_strCustomColor2    ,Qt::CaseSensitive);
    qss.replace("CUSTOMCOLOR3",m_strCustomColor3    ,Qt::CaseSensitive);
    qss.replace("CUSTOMCOLOR4",m_strCustomColor4    ,Qt::CaseSensitive);

    QString PaletteColor = qss.mid(13, 7);
    qApp->setPalette(QPalette(QColor(PaletteColor)));
    qApp->setStyleSheet(qss);
}

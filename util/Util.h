#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QString>
#include <QDir>

/**
 * @brief The Util class
 * 工具类函数（静态）
 */

class Util : public QObject
{
public:
    // 文件大小转String
    static QString sizeToString(qint64 size);
    // 获取配置文件路径
    static QString getIniFilePath();
    // 读取qss文件
    static QString getQss(QString filePath);
    // 设置指定样式
    static void setSkinStyle(const QString &qssFile);
    //设置为开机启动
    static void autoRunWithSystem(bool isAutoRun, QString appName, QString appPath);
    //窗体居中显示
    static void moveFormToCenter(QWidget *frm);
    // 校验和
    static unsigned char checkSum(unsigned char *buf, int len);
    // 延时
    static void delayMSec(int msec);
};

#endif // UTIL_H

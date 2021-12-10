#pragma once

#include <QObject>
#include <QSettings>
#include <QColor>


class QssHelper : public QObject
{
    Q_OBJECT
public:
    static QssHelper *instance() ;

    QMap<QString, QString> getAllQssName() const;       // 获取所有Qss<主题名称， 颜色>
    void setSkinStyle(const QString &t_name);           // 设置皮肤

signals:
    void skinChanged(QString);                          // 皮肤更新信号（主题名称）

private:
    QssHelper() = default;
    ~QssHelper() = default;
private:
    void getIniFileColor(QString t_file);               // 获取配置文件颜色
    void replaceColorQssFile();                         // 替换Qss文件颜色
    void replaceColorImages();                          // 替换Icon图片颜色

private:
    QString m_strPanelColor  ;                          // 面板颜色
    QString m_strTextColor   ;                          // 文本颜色
    QString m_strBorderColor ;                          // 边框颜色
    QString m_strNormalColor ;                          // 普通颜色
    QString m_strDarkColor   ;                          // 加深颜色
    QString m_strHighColor   ;                          // 高亮颜色
    QString m_strDisabledColor;                         // 使能失效颜色
    QString m_strCheckedColor;                          // 选中颜色

    QString m_strCustomColor1;                          // 自定义颜色
    QString m_strCustomColor2;                          // 自定义颜色
    QString m_strCustomColor3;                          // 自定义颜色
    QString m_strCustomColor4;                          // 自定义颜色
};

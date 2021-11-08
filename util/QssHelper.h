#pragma once

#include <QObject>
#include <QSettings>
#include <QColor>


class QssHelper : public QObject
{
    Q_OBJECT
public:
    static QssHelper *instance() ;

    QStringList getAllQssName() const;                  // 获取所有Qss名称
    void setSkinStyle(const QString &t_name);           // 设置皮肤

signals:
    void skinChanged();                                 // 皮肤更新信号

private:
    QssHelper() = default;
    ~QssHelper() = default;
private:
    void getIniFileColor(QString t_file);
    void replaceColorQssFile();
    void replaceColorImages();

private:
    QString m_strPanelColor  ;                          // 面板颜色
    QString m_strTextColor   ;                          // 文本颜色
    QString m_strBorderColor ;                          // 边框颜色
    QString m_strNormalColor ;                          // 普通颜色
    QString m_strDarkColor   ;                          // 加深颜色
    QString m_strHighColor   ;                          // 高亮颜色
    QString m_strCustomColor1;                          // 自定义颜色
    QString m_strCustomColor2;                          // 自定义颜色
    QString m_strCustomColor3;                          // 自定义颜色
    QString m_strCustomColor4;                          // 自定义颜色
};

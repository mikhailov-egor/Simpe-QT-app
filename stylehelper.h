#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>
#include <QJsonObject>
#include <QSize>

class StyleHelper
{
public:
    StyleHelper();
    ~StyleHelper();

    bool setAppTheme(const QString &filePath);
    QString getWindowIconPath();
    QString getWindowTitleStyle();
    QString getMinimizeButtonStyle();
    QString getMaximizeButtonStyle();
    QString getNormalButtonStyle();
    QString getCloseButtonStyle();
    QString getWindowButtonQSS(const QJsonObject &obj, const QString &file);

    static QSize winIconSize;
    static QSize winBtnSize;

private:
    struct AppTheme {
        QString name;
        QString windowIconPath;
        QString windowTitleQSS;
        QString minimizeBtnQSS;
        QString maximizeBtnQSS;
        QString normalBtnQSS;
        QString closeBtnQSS;
    };

    AppTheme *pAppTheme;

    QString jsonToQSS(const QJsonObject &obj);
};

#endif // STYLEHELPER_H

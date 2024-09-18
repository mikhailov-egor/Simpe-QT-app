#include "stylehelper.h"
#include <QFile>
#include <QJsonDocument>

QSize StyleHelper::winIconSize = {16, 16};
QSize StyleHelper::winBtnSize = {30, 26};

StyleHelper::StyleHelper()
{
    pAppTheme = new AppTheme;
}

StyleHelper::~StyleHelper()
{
    delete pAppTheme;
}

bool StyleHelper::setAppTheme(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error: didn't managed to open file: " << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if(!doc.isObject()) {
        qDebug() << error.errorString() << error.offset << error.error;
        return false;
    }
    QJsonObject root = doc.object();
    pAppTheme->name = root.value("name").toString();

    if(root.value("windowTitle").isObject()) {
        QJsonObject windowTitle = root.value("windowTitle").toObject();
        pAppTheme->windowIconPath = windowTitle.value("icon").toString();
        pAppTheme->windowTitleQSS += "QWidget{background-color:" + windowTitle.value("background-color").toString() + "}"
                                     + "QWidget#menuWidget{min-width:250px;}";
    }
    if(root.value("mainMenu").isObject()) {
        QJsonObject mainMenu = root.value("mainMenu").toObject();
        pAppTheme->windowTitleQSS += "QMenuBar{}"
                                    "QMenuBar::item{color:" + mainMenu.value("color").toString() + ";"
                                    "padding:" + mainMenu.value("item-padding").toString() + "}"
                                    "QMenuBar::item:selected{background:"
                                    + mainMenu.value("item-selected-background-color").toString() + ";}"
                                    "QMenuBar::item:pressed{background:"
                                     + mainMenu.value("item-pressed-background-color").toString() + ";}";
    }
    if(root.value("windowButtons").isObject()) {
        QJsonObject windowButtons = root.value("windowButtons").toObject();
        if(windowButtons.value("minimize-button").isObject()) {
            QJsonObject minimizeButton = windowButtons.value("minimize-button").toObject();
            pAppTheme->minimizeBtnQSS = getWindowButtonQSS(minimizeButton, "minWindowButton");
        }

        if(windowButtons.value("maximize-button").isObject()) {
            QJsonObject maximizeButton = windowButtons.value("maximize-button").toObject();
            pAppTheme->maximizeBtnQSS = getWindowButtonQSS(maximizeButton, "maxWindowButton");
        }

        if(windowButtons.value("normal-button").isObject()) {
            QJsonObject normalButton = windowButtons.value("normal-button").toObject();
            pAppTheme->normalBtnQSS = getWindowButtonQSS(normalButton, "maxWindowButton");
        }

        if(windowButtons.value("close-button").isObject()) {
            QJsonObject closeButton = windowButtons.value("close-button").toObject();
            pAppTheme->closeBtnQSS = getWindowButtonQSS(closeButton, "closeWindowButton");
        }
    }
    return true;
}

QString StyleHelper::getWindowIconPath()
{
    return pAppTheme->windowIconPath;
}

QString StyleHelper::getWindowTitleStyle()
{
    return pAppTheme->windowTitleQSS;
}

QString StyleHelper::getMinimizeButtonStyle()
{
    return pAppTheme->minimizeBtnQSS;
}

QString StyleHelper::getMaximizeButtonStyle()
{
    return pAppTheme->maximizeBtnQSS;
}

QString StyleHelper::getNormalButtonStyle()
{
    return pAppTheme->normalBtnQSS;
}

QString StyleHelper::getCloseButtonStyle()
{
    return pAppTheme->closeBtnQSS;
}

QString StyleHelper::getWindowButtonQSS(const QJsonObject &obj, const QString &name)
{
    return "QPushButton#" + name + "{"
            + jsonToQSS(obj.value("normal").toObject())
            + "}"
            + "QPushButton#" + name + "::hover{"
            + jsonToQSS(obj.value("hover").toObject())
            + "}"
            + "QPushButton#" + name + "::pressed{"
            + jsonToQSS(obj.value("pressed").toObject())
            + "}";
}

QString StyleHelper::jsonToQSS(const QJsonObject &obj)
{
    QString qss;
    QStringList keys = obj.keys();
    for(const QString &key : keys)
        qss += key + ":" + obj.value(key).toString() + ";";
    return qss;
}



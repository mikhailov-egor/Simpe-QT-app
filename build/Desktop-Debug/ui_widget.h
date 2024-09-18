/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *mainWidget;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *iconLabel;
    QWidget *menuWidget;
    QSpacerItem *horizontalSpacer;
    QPushButton *minWindowButton;
    QPushButton *maxWindowButton;
    QPushButton *closeWindowButton;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *Albums;
    QVBoxLayout *verticalLayout_7;
    QListWidget *listWidgetAlbums;
    QWidget *My;
    QVBoxLayout *verticalLayout_8;
    QPushButton *createPlaylistButton;
    QListWidget *listWidgetPlaylists;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *albumIcon;
    QVBoxLayout *verticalLayout_2;
    QWidget *tracksWidget;
    QVBoxLayout *verticalLayout_6;
    QLabel *albumTitleLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *albumDescriptionLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *albumDateLabel;
    QListWidget *tracksListWidget;
    QWidget *soundPlayerWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *trackBack;
    QPushButton *trackStop;
    QPushButton *trackForward;
    QSlider *durationSlider;
    QSpacerItem *horizontalSpacer_3;
    QSlider *volumeSlider;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        mainWidget = new QWidget(Widget);
        mainWidget->setObjectName("mainWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainWidget->sizePolicy().hasHeightForWidth());
        mainWidget->setSizePolicy(sizePolicy);
        mainWidget->setMinimumSize(QSize(0, 0));
        mainWidget->setBaseSize(QSize(0, 0));
        mainWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(50, 50, 50);"));
        verticalLayout_4 = new QVBoxLayout(mainWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(mainWidget);
        frame->setObjectName("frame");
        frame->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(95, 95, 95);\n"
"min-height:25px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        frame->setMidLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 4, 0);
        iconLabel = new QLabel(frame);
        iconLabel->setObjectName("iconLabel");

        horizontalLayout->addWidget(iconLabel);

        menuWidget = new QWidget(frame);
        menuWidget->setObjectName("menuWidget");
        menuWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(menuWidget);

        horizontalSpacer = new QSpacerItem(344, 22, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        minWindowButton = new QPushButton(frame);
        minWindowButton->setObjectName("minWindowButton");

        horizontalLayout->addWidget(minWindowButton);

        maxWindowButton = new QPushButton(frame);
        maxWindowButton->setObjectName("maxWindowButton");

        horizontalLayout->addWidget(maxWindowButton);

        closeWindowButton = new QPushButton(frame);
        closeWindowButton->setObjectName("closeWindowButton");

        horizontalLayout->addWidget(closeWindowButton);


        verticalLayout_4->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        frame_2 = new QFrame(mainWidget);
        frame_2->setObjectName("frame_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setMinimumSize(QSize(200, 300));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(67, 67, 67);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        tabWidget = new QTabWidget(frame_2);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(71, 71, 71);"));
        Albums = new QWidget();
        Albums->setObjectName("Albums");
        verticalLayout_7 = new QVBoxLayout(Albums);
        verticalLayout_7->setObjectName("verticalLayout_7");
        listWidgetAlbums = new QListWidget(Albums);
        listWidgetAlbums->setObjectName("listWidgetAlbums");

        verticalLayout_7->addWidget(listWidgetAlbums);

        tabWidget->addTab(Albums, QString());
        My = new QWidget();
        My->setObjectName("My");
        verticalLayout_8 = new QVBoxLayout(My);
        verticalLayout_8->setObjectName("verticalLayout_8");
        createPlaylistButton = new QPushButton(My);
        createPlaylistButton->setObjectName("createPlaylistButton");
        createPlaylistButton->setStyleSheet(QString::fromUtf8("background-color: rgb(63, 63, 63);"));

        verticalLayout_8->addWidget(createPlaylistButton);

        listWidgetPlaylists = new QListWidget(My);
        listWidgetPlaylists->setObjectName("listWidgetPlaylists");

        verticalLayout_8->addWidget(listWidgetPlaylists);

        tabWidget->addTab(My, QString());

        verticalLayout_5->addWidget(tabWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);


        verticalLayout_3->addWidget(frame_2);

        widget = new QWidget(mainWidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMinimumSize(QSize(200, 200));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(172, 172, 172);"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        albumIcon = new QLabel(widget);
        albumIcon->setObjectName("albumIcon");
        albumIcon->setStyleSheet(QString::fromUtf8("background-color: rgb(65, 65, 65);"));

        horizontalLayout_3->addWidget(albumIcon);


        verticalLayout_3->addWidget(widget);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(4, 0, 4, -1);
        tracksWidget = new QWidget(mainWidget);
        tracksWidget->setObjectName("tracksWidget");
        tracksWidget->setMinimumSize(QSize(150, 0));
        tracksWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(104, 104, 104);"));
        verticalLayout_6 = new QVBoxLayout(tracksWidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        albumTitleLabel = new QLabel(tracksWidget);
        albumTitleLabel->setObjectName("albumTitleLabel");

        verticalLayout_6->addWidget(albumTitleLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        albumDescriptionLabel = new QLabel(tracksWidget);
        albumDescriptionLabel->setObjectName("albumDescriptionLabel");
        albumDescriptionLabel->setStyleSheet(QString::fromUtf8("min-width:350px;\n"
"min-height:100px;"));

        horizontalLayout_4->addWidget(albumDescriptionLabel);

        horizontalSpacer_2 = new QSpacerItem(98, 28, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        albumDateLabel = new QLabel(tracksWidget);
        albumDateLabel->setObjectName("albumDateLabel");

        horizontalLayout_4->addWidget(albumDateLabel);


        verticalLayout_6->addLayout(horizontalLayout_4);

        tracksListWidget = new QListWidget(tracksWidget);
        tracksListWidget->setObjectName("tracksListWidget");

        verticalLayout_6->addWidget(tracksListWidget);


        verticalLayout_2->addWidget(tracksWidget);

        soundPlayerWidget = new QWidget(mainWidget);
        soundPlayerWidget->setObjectName("soundPlayerWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(soundPlayerWidget->sizePolicy().hasHeightForWidth());
        soundPlayerWidget->setSizePolicy(sizePolicy4);
        soundPlayerWidget->setMinimumSize(QSize(500, 100));
        soundPlayerWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(63, 63, 63);"));
        horizontalLayout_5 = new QHBoxLayout(soundPlayerWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        trackBack = new QPushButton(soundPlayerWidget);
        trackBack->setObjectName("trackBack");
        trackBack->setStyleSheet(QString::fromUtf8("min-height:50px;\n"
"min-width:50px;"));

        horizontalLayout_5->addWidget(trackBack);

        trackStop = new QPushButton(soundPlayerWidget);
        trackStop->setObjectName("trackStop");
        trackStop->setStyleSheet(QString::fromUtf8("min-height:50px;\n"
"min-width:50px;"));

        horizontalLayout_5->addWidget(trackStop);

        trackForward = new QPushButton(soundPlayerWidget);
        trackForward->setObjectName("trackForward");
        trackForward->setStyleSheet(QString::fromUtf8("min-height:50px;\n"
"min-width:50px;"));

        horizontalLayout_5->addWidget(trackForward);

        durationSlider = new QSlider(soundPlayerWidget);
        durationSlider->setObjectName("durationSlider");
        durationSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(durationSlider);

        horizontalSpacer_3 = new QSpacerItem(93, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        volumeSlider = new QSlider(soundPlayerWidget);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(volumeSlider);


        verticalLayout_2->addWidget(soundPlayerWidget);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(mainWidget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        iconLabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        minWindowButton->setText(QString());
        maxWindowButton->setText(QString());
        closeWindowButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Albums), QCoreApplication::translate("Widget", "Albums", nullptr));
        createPlaylistButton->setText(QCoreApplication::translate("Widget", "Create Playlist", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(My), QCoreApplication::translate("Widget", "My", nullptr));
        albumIcon->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        albumTitleLabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        albumDescriptionLabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        albumDateLabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        trackBack->setText(QString());
        trackStop->setText(QString());
        trackForward->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

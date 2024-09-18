#include "widget.h"
#include "ui_widget.h"
#include "stylehelper.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pSettings = new QSettings("settings.ini", QSettings::IniFormat, this);
    readSettings();

    setMainMenu();
    pStyleHelper = new StyleHelper;
    setTheme();
    setWindowProperties();

    loadData();

    pMediaPlayer = new QMediaPlayer();
    pao = new QAudioOutput(pMediaPlayer);
}

Widget::~Widget()
{
    delete ui;
    writeSettings();
}

void Widget::setWindowProperties()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *pShadow = new QGraphicsDropShadowEffect(this);
    pShadow->setBlurRadius(9);
    pShadow->setOffset(0);
    ui->mainWidget->setGraphicsEffect(pShadow);

    this->setMouseTracking(true);
    ui->mainWidget->setMouseTracking(true);
    ui->frame->setMouseTracking(true);

    connect(ui->maxWindowButton, &QPushButton::clicked, this, &Widget::slotMaxButton);
    connect(ui->closeWindowButton, &QPushButton::clicked, this, &Widget::close);

    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &Widget::showTabs);

    connect(ui->listWidgetAlbums, &QListWidget::itemClicked, this, &Widget::slotChangeActiveAlbum);
    connect(ui->listWidgetPlaylists, &QListWidget::itemClicked, this, &Widget::slotChangeActiveAlbum);
    connect(ui->tracksListWidget, &QListWidget::itemClicked, this, &Widget::slotChangeActiveTrack);

    connect(ui->createPlaylistButton, &QPushButton::clicked, this, [this]() {
        slotModifyPlaylist(ModificationPlaylist::Create);
    });

    ui->tracksListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tracksListWidget, &QListWidget::customContextMenuRequested, this, &Widget::slotCustomMenuTracksRequested);

    ui->listWidgetPlaylists->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidgetPlaylists, &QListWidget::customContextMenuRequested, this, &Widget::slotCustomMenuAlbumsRequested);

    ui->trackBack->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
    ui->trackForward->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
    ui->trackStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

}

void Widget::setMainMenu()
{
    QMenuBar *pMenuBar = new QMenuBar(ui->menuWidget);

    QMenu *pMenuFile = new QMenu("&File");
    QAction *pActOpen = new QAction("&Open");
    QAction *pActClose = new QAction("&Close");
    pMenuFile->addAction(pActOpen);
    pMenuFile->addAction(pActClose);

    QMenu *pMenuEdit = new QMenu("&Edit");

    pMenuBar->addMenu(pMenuFile);
    pMenuBar->addMenu(pMenuEdit);

    connect(pActOpen, &QAction::triggered, this, &Widget::slotOpen);
    connect(pActClose, &QAction::triggered, this, &Widget::slotClose);
}

void Widget::setTheme()
{
    pStyleHelper->setAppTheme(":/files/themes/standart.json");
    ui->iconLabel->setPixmap(QPixmap(pStyleHelper->getWindowIconPath()));
    ui->iconLabel->setFixedSize(StyleHelper::winIconSize);
    ui->frame->setStyleSheet(pStyleHelper->getWindowTitleStyle());

    ui->minWindowButton->setFixedSize(StyleHelper::winBtnSize);
    ui->minWindowButton->setStyleSheet(pStyleHelper->getMinimizeButtonStyle());

    ui->maxWindowButton->setFixedSize(StyleHelper::winBtnSize);
    ui->maxWindowButton->setStyleSheet(pStyleHelper->getMaximizeButtonStyle());

    ui->closeWindowButton->setFixedSize(StyleHelper::winBtnSize);
    ui->closeWindowButton->setStyleSheet(pStyleHelper->getCloseButtonStyle());
}

void Widget::mousePressEvent(QMouseEvent *pme)
{
    if(pme->button() == Qt::LeftButton) {
        mousePreviousPosition = pme->pos();
        mouseClickType = checkCollision(pme->globalPosition());
        if(!isMaximized())
            changeCursor();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *pme)
{
    if(pme->button() == Qt::LeftButton) {
        mouseClickType = MouseType::None;
        changeCursor();
    }

}

void Widget::mouseMoveEvent(QMouseEvent *pme)
{
    QPointF position = pme->globalPosition();
    if(!isMaximized()) {
        changeCursor(checkCollision(position));
    }

    switch(mouseClickType) {
    case MouseType::Top:
        if(!isMaximized()) {
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(x(), y() + deltaY, width(), height() - deltaY);
        }
        break;
    case MouseType::Bottom:
        if(!isMaximized()) {
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(x(), y(), width(), height() + deltaY);
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::Left:
        if(!isMaximized()) {
            int deltaX = mapToGlobal(pme->pos()).x() - x();
            setGeometry(mapToGlobal(pme->pos()).x(), y(), width() - deltaX, height());
        }
        break;
    case MouseType::Right:
        if(!isMaximized()) {
            int deltaX = pme->pos().x() - mousePreviousPosition.x();
            setGeometry(x(), y(), width() + deltaX, height());
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::TopLeft:
        if(!isMaximized()) {
            int deltaX = mapToGlobal(pme->pos()).x() - x();
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(mapToGlobal(pme->pos()).x(), y() + deltaY, width() - deltaX, height() - deltaY);
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::TopRight:
        if(!isMaximized()) {
            int deltaX = pme->pos().x() - mousePreviousPosition.x();
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(x(), y() + deltaY, width() + deltaX, height() - deltaY);
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::BottomLeft:
        if(!isMaximized()) {
            int deltaX = mapToGlobal(pme->pos()).x() - x();
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(mapToGlobal(pme->pos()).x(), y(), width() - deltaX, height() + deltaY);
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::BottomRight:
        if(!isMaximized()) {
            int deltaX = pme->pos().x() - mousePreviousPosition.x();
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(x(), y(), width() + deltaX, height() + deltaY);
            mousePreviousPosition = pme->pos();
        }
        break;
    case MouseType::MainTop:
        if(!isMaximized()) {
            int deltaX = pme->pos().x() - mousePreviousPosition.x();
            int deltaY = pme->pos().y() - mousePreviousPosition.y();
            setGeometry(x() + deltaX, y() + deltaY, width(), height());
        } else {
            this->showNormal();
            this->layout()->setContentsMargins(9, 9, 9, 9);
            setGeometry(x(), y(), width(), height());
        }
        break;
    case MouseType::None:
        break;
    }
}

MouseType Widget::checkCollision(const QPointF &mousePos)
{
    float winX = this->x();
    float winY = this->y();
    float winWidth = this->width();
    float winHeight = this->height();
    QRectF rectTop(winX + 20, winY, winWidth - 40, 9);
    QRectF rectBottom(winX + 20, winY + winHeight - 9, winWidth - 40, 9);
    QRectF rectLeft(winX, winY + 20, 9, winHeight - 40);
    QRectF rectRight(winX + winWidth - 9, winY + 20, 9, winHeight - 40);
    QRectF rectMainTop(winX + 10, winY + 10, winWidth - 20, 30);
    QRectF rectTopLeft(winX, winY, 15, 15);
    QRectF rectTopRight(winX +winWidth - 15, winY, 15, 15);
    QRectF rectBottomLeft(winX, winY + winHeight - 15, 15, 15);
    QRectF rectBottomRight(winX + winWidth - 15, winY + winHeight - 15, 15, 15);

    if(rectTop.contains(mousePos)) {
        return MouseType::Top;
    } else if(rectBottom.contains(mousePos)) {
        return MouseType::Bottom;
    } else if(rectLeft.contains(mousePos)) {
        return MouseType::Left;
    } else if(rectRight.contains(mousePos)) {
        return MouseType::Right;
    } else if(rectMainTop.contains(mousePos)) {
        return MouseType::MainTop;
    } else if(rectTopLeft.contains(mousePos)) {
        return MouseType::TopLeft;
    } else if(rectTopRight.contains(mousePos)) {
        return MouseType::TopRight;
    } else if(rectBottomLeft.contains(mousePos)) {
        return MouseType::BottomLeft;
    } else if(rectBottomRight.contains(mousePos)) {
        return MouseType::BottomRight;
    }
    return MouseType::None;
}

void Widget::changeCursor()
{
    changeCursor(mouseClickType);
}

void Widget::changeCursor(MouseType mouseClickType)
{
    switch(mouseClickType) {
    case MouseType::Top:
    case MouseType::Bottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case MouseType::Left:
    case MouseType::Right:
        setCursor(Qt::SizeHorCursor);
        break;
    case MouseType::TopLeft:
    case MouseType::BottomRight:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case MouseType::TopRight:
    case MouseType::BottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case MouseType::MainTop:
    case MouseType::None:
        setCursor(QCursor());
        break;
    default:
        setCursor(QCursor());
        break;
    }
}

void Widget::readSettings()
{
//    pSettings->value("maximize").toBool() ? showMaximized() : showNormal();
    setGeometry(pSettings->value("geometry", QRect(200, 200, 300, 300)).toRect());
}

void Widget::writeSettings()
{
    pSettings->setValue("geometry", geometry());
//    pSettings->setValue("maximize", ui->mainWidget->isMaximized());
}

void Widget::loadData()
{
    if(!db.connectDB()) {
        QMessageBox messageBox(QMessageBox::Warning,
                               "The connection to DB was not established",
                               "Can't save the data",
                               QMessageBox::Yes,
                               this
                               );
        messageBox.setStandardButtons(QMessageBox::Apply);
        messageBox.exec();
        return;
    }

    showTabs();
}

void Widget::showTabs()
{
    ui->listWidgetAlbums->clear();
    Albums albums = db.getAlbums(1);
    for(Album &alb : albums) {
        QListWidgetItem *pItem = new QListWidgetItem(alb.title);
        ui->listWidgetAlbums->addItem(pItem);
    }

    ui->listWidgetPlaylists->clear();
    Albums playlists = db.getAlbums(0);
    for(Album &playlist : playlists) {
        QListWidgetItem *pItem = new QListWidgetItem(playlist.title);
        ui->listWidgetPlaylists->addItem(pItem);
    }
}

void Widget::slotMaxButton()
{
    if(isMaximized()){
        this->layout()->setContentsMargins(9, 9, 9, 9);
        ui->maxWindowButton->setStyleSheet(pStyleHelper->getMaximizeButtonStyle());
        showNormal();
    } else {
        this->layout()->setContentsMargins(0, 0, 0, 0);
        ui->maxWindowButton->setStyleSheet(pStyleHelper->getNormalButtonStyle());
        showMaximized();
    }
}

void Widget::slotOpen()
{
    qDebug() << "slot open";
}

void Widget::slotClose()
{
    close();
}

void Widget::slotChangeActiveAlbum(QListWidgetItem *pCur)
{
    if(pCur == nullptr)
        return;

    Tracks tracks = db.getTracks(pCur->text());
    ui->tracksListWidget->clear();
    for(Track &track : tracks) {
        QListWidgetItem *pItem = new QListWidgetItem(track.title);
        ui->tracksListWidget->addItem(pItem);
    }

    Album alb = db.getAlbum(pCur->text());

    QFont font("Times New Roman", 20, QFont::Bold);
    ui->albumTitleLabel->setText(alb.title);
    ui->albumTitleLabel->setAlignment(Qt::AlignCenter);
    ui->albumTitleLabel->setFont(font);

    ui->albumDescriptionLabel->setText(alb.description);
    ui->albumDateLabel->setText(alb.creation_date);
    QPixmap pix = (alb.exist_image) ? QPixmap(alb.image) : QPixmap(":/files/image/no_image.jpg");
    pix = pix.scaled(ui->albumIcon->width(), ui->albumIcon->height());
    ui->albumIcon->setPixmap(pix);
}

void Widget::slotChangeActiveTrack(QListWidgetItem *pCur)
{
    if(pCur == nullptr)
        return;

    QString albumTitleLabel = ui->albumTitleLabel->text();
    Track track = db.getTrack(albumTitleLabel, pCur->text());
    Album album = db.getAlbum(albumTitleLabel);
    QPixmap pix = (track.image != "") ? track.image : album.image;
    pix = pix.scaled(ui->albumIcon->width(), ui->albumIcon->height());
    ui->albumIcon->setPixmap(pix);

    pao->setVolume(50);
    pMediaPlayer->setAudioOutput(pao);
    QString fileName = track.music_file;
    pMediaPlayer->setSource(QUrl(fileName));
    qDebug() << fileName;

}

void Widget::slotModifyPlaylist(ModificationPlaylist modificationType)
{
    QString operation;

    if(modificationType == ModificationPlaylist::Create) operation = "Create";
    else if(modificationType == ModificationPlaylist::Edit) operation = "Edit";
    else {
        db.playlist.title = ui->albumTitleLabel->text();
        db.modifyPlaylist(2);
        QMessageBox::information(this, "Success", "The list of playlists have been modified successfully");
        showTabs();
        return;
    }

    QDialog *pDia = new QDialog;

    pDia->setWindowTitle(operation + " Playlist");
    pDia->setModal(true);

    QLabel *plbl = new QLabel(operation + " Playlist");

    QLabel *plblTitle = new QLabel("&Title:");
    QLineEdit *ptxtTitle = new QLineEdit;
    plblTitle->setBuddy(ptxtTitle);

    QLabel *plblDescription = new QLabel("&Description:");
    QLineEdit *ptxtDescription = new QLineEdit;
    plblDescription->setBuddy(ptxtDescription);

    QLabel *plblImage = new QLabel("Image:");
    QPushButton *pcmdImage = new QPushButton("Select image");
    QHBoxLayout *phbxLayout = new QHBoxLayout;
    phbxLayout->addWidget(plblImage);
    phbxLayout->addWidget(pcmdImage);
    connect(pcmdImage, &QPushButton::clicked, this, &Widget::slotImageButton);

    if(operation == "Edit") {
        Album album = db.getAlbum(ui->albumTitleLabel->text());
        ptxtTitle->setText(album.title);
        ptxtDescription->setText(album.description);
    }

    QPushButton *pcmdSubmit = new QPushButton("&" + operation);
    connect(pcmdSubmit, &QPushButton::clicked, this, [this, ptxtTitle, ptxtDescription, pDia, operation]() {
        if(!ptxtTitle->text().isEmpty()) {
            db.playlist.title = ptxtTitle->text();
            db.playlist.description = ptxtDescription->text();
            db.playlist.albumId = db.getAlbumId(ui->listWidgetPlaylists->currentItem()->text());
            if(operation == "Create") db.modifyPlaylist(0);
            else db.modifyPlaylist(1);
            showTabs();
            QMessageBox::information(this, "Success", "The list of playlists have been modified successfully");
            pDia->close();
        }
        else
            QMessageBox::warning(this, "Error", "Cannot modify the list of playlists without the title");
    });

    // Layout setup
    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(plbl);
    pvbxLayout->addWidget(plblTitle);
    pvbxLayout->addWidget(ptxtTitle);
    pvbxLayout->addWidget(plblDescription);
    pvbxLayout->addWidget(ptxtDescription);
    pvbxLayout->addLayout(phbxLayout);
    pvbxLayout->addWidget(pcmdSubmit);

    pDia->setLayout(pvbxLayout);
    pDia->show();
}

void Widget::slotImageButton()
{
    QString image = QFileDialog::getOpenFileName(this, tr("Open image"), "E:/QT2/projects/Yeat/files/image", tr("Images (*.jpg)"));
    if(image != "") db.playlist.exist_image = true;
    db.playlist.image = ":" + image.mid(20);
}

void Widget::slotCustomMenuAlbumsRequested(QPoint pos)
{
    QMenu *pMenu = new QMenu(this);

    QAction *pActEdit = new QAction("Edit", this);
    if(ui->listWidgetPlaylists->currentItem()->text() == "Like")
        pActEdit->setEnabled(false);
    connect(pActEdit, &QAction::triggered, this, [this]() {
        slotModifyPlaylist(ModificationPlaylist::Edit);
    });
    pMenu->addAction(pActEdit);

    QAction *pActRemove = new QAction("Remove", this);
    if(ui->listWidgetPlaylists->currentItem()->text() == "Like")
        pActRemove->setEnabled(false);
    connect(pActRemove, &QAction::triggered, this, [this]() {
        slotModifyPlaylist(ModificationPlaylist::Remove);
    });
    pMenu->addAction(pActRemove);

    pMenu->popup(ui->listWidgetPlaylists->viewport()->mapToGlobal(pos));
}

void Widget::slotCustomMenuTracksRequested(QPoint pos)
{
    QMenu *pMenu = new QMenu(this);

    QAction *pActAdd = new QAction("Add to playlist", this);
    connect(pActAdd, &QAction::triggered, this, &Widget::slotAddToPlaylist);
    pMenu->addAction(pActAdd);

    QAction *pActLike = new QAction("Like", this);
    connect(pActLike, &QAction::triggered, this, &Widget::slotLikeTrack);
    if(ui->albumTitleLabel->text() == "Like")
        pActLike->setEnabled(false);
    pMenu->addAction(pActLike);

    QAction *pActRemove = new QAction("Remove", this);
    connect(pActRemove, &QAction::triggered, this, &Widget::slotRemoveFromPlaylist);
    showTabs();
    pMenu->addAction(pActRemove);

    if(ui->tabWidget->currentWidget()->objectName() == "Albums")
        pActRemove->setEnabled(false);
    pMenu->popup(ui->tracksListWidget->viewport()->mapToGlobal(pos));
}

void Widget::slotAddToPlaylist()
{
    int row = ui->tracksListWidget->selectionModel()->currentIndex().row();
    QString track = ui->tracksListWidget->currentItem()->text();
    QString fromAlbum = ui->albumTitleLabel->text();
    if(row >= 0) {
        QDialog *pDia = new QDialog;
        pDia->setWindowTitle("Add To Playlist");
        pDia->setModal(true);
        pDia->setMinimumSize(200, 200);

        QListWidget *pListWidget = new QListWidget(pDia);
        Albums playlists = db.getAlbums(0);
        for(Album &playlist : playlists) {
            if(playlist.title == "Like") continue;
            QListWidgetItem *pItem = new QListWidgetItem(playlist.title);
            pListWidget->addItem(pItem);
        }

        connect(pListWidget, &QListWidget::itemClicked, this, [this, pListWidget, track, fromAlbum]() {
            QString toAlbum = pListWidget->currentItem()->text();
            db.addTrackToPlaylist(toAlbum, track, fromAlbum);
        });

        pDia->show();
    }
}

void Widget::slotLikeTrack()
{
    QString track = ui->tracksListWidget->currentItem()->text();
    QString fromAlbum = ui->albumTitleLabel->text();

    db.addTrackToPlaylist("Like", track, fromAlbum);
}

void Widget::slotRemoveFromPlaylist()
{
    int row = ui->tracksListWidget->selectionModel()->currentIndex().row();
    if(row >= 0) {
        db.removeTrackFromPlaylist(ui->albumTitleLabel->text(), ui->tracksListWidget->currentItem()->text());
        showTabs();
        return; // for that to close context menu after removing
    }
}

void Widget::on_durationSlider_sliderMoved(int /* position */)
{

}

void Widget::on_volumeSlider_sliderMoved(int position )
{
    qDebug() << position;
    pao->setVolume(position);
}

void Widget::on_trackBack_clicked()
{

}

void Widget::on_trackForward_clicked()
{

}


void Widget::on_trackStop_clicked()
{
    pMediaPlayer->play();
}


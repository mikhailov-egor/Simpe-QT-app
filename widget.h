#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "database.h"
#include <QtMultimedia>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
class QMouseEvent;
class QSettings;
QT_END_NAMESPACE

class StyleHelper;
class QListWidgetItem;
class QListWidget;

enum MouseType {
    Top,
    Bottom,
    Left,
    Right,
    MainTop,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    None
};

enum ModificationPlaylist {
    Create,
    Edit,
    Remove
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *pme);
    void mouseReleaseEvent(QMouseEvent *pme);
    void mouseMoveEvent(QMouseEvent *pme);

private:
    Ui::Widget *ui;

    MouseType mouseClickType;
    QPoint mousePreviousPosition;
    QSettings *pSettings;
    StyleHelper *pStyleHelper;
    DataBase db;
    QMediaPlayer *pMediaPlayer;
    QAudioOutput *pao;

    void setWindowProperties();
    void setMainMenu();
    void setTheme();

    MouseType checkCollision(const QPointF &mousePos);

    void changeCursor();
    void changeCursor(MouseType mouseClickType);

    void readSettings();
    void writeSettings();

    void loadData();
    void showTabs();

private slots:
    void slotMaxButton();
    void slotOpen();
    void slotClose();

    void slotChangeActiveAlbum(QListWidgetItem *pCur);
    void slotChangeActiveTrack(QListWidgetItem *pCur);

    void slotModifyPlaylist(ModificationPlaylist modificationType);
    void slotImageButton();

    void slotCustomMenuTracksRequested(QPoint pos);
    void slotAddToPlaylist();
    void slotLikeTrack();
    void slotRemoveFromPlaylist();

    void slotCustomMenuAlbumsRequested(QPoint pos);

    void on_durationSlider_sliderMoved(int position);
    void on_volumeSlider_sliderMoved(int position);
    void on_trackBack_clicked();
    void on_trackForward_clicked();
    void on_trackStop_clicked();
};
#endif // WIDGET_H

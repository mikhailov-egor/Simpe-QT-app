#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite/sqlite3.h"
#include <QFile>
#include <QDebug>
#include <QPixmap>
#include <QDateTime>

struct Track {
    int id;
    QString album;
    QString title;
    QString image;
    QString music_file;
};

struct Album {
    int albumId;
    QString title;
    QString description;
    QString creation_date;
    bool yeat_album;
    bool exist_image;
    QString image;
};

using Tracks = QVector<Track>;
using Albums = QVector<Album>;

class DataBase : public QObject
{
public:
    Album playlist;

    explicit DataBase(QObject *pobj = nullptr);
    bool connectDB();

    int getAlbumId(const QString &title);

    Albums getAlbums(bool yeat_album);
    Album getAlbum(const QString &title);

    Tracks getTracks(const QString &title);
    Track getTrack(const QString &album, const QString &title);

    void modifyPlaylist(int operation);

    void addTrackToPlaylist(const QString &album, const QString &title, const QString &fromAlbum);
    void removeTrackFromPlaylist(const QString &album, const QString &title);

private:
    sqlite3 *pdb;
    const QString fileName = "tracks.db";

    bool openDB();
    bool restoreDB();
    void closeDB();
};

#endif // DATABASE_H

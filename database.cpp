#include "database.h"

DataBase::DataBase(QObject *pobj) : QObject(pobj) {}

bool DataBase::connectDB()
{
    if(!QFile(fileName).exists()) {
        qDebug() << fileName << " doesn't not exist";
        return restoreDB();
    }
    return openDB();
}

int DataBase::getAlbumId(const QString &title)
{
    Album alb;
    std::string sql = "SELECT id FROM albums WHERE title = '" + title.toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        return -1;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW)
        alb.albumId = sqlite3_column_int(stmt, 0);

    return alb.albumId;
}

Albums DataBase::getAlbums(bool yeat_album)
{
    Albums albums;
    std::string sql = "SELECT * FROM albums WHERE yeat_album = '" + QString::number(yeat_album).toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        return albums;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        Album album;
        album.albumId = sqlite3_column_int(stmt, 0);
        album.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        album.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        album.creation_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        albums.append(album);
    }

    return albums;
}

Album DataBase::getAlbum(const QString &title)
{
    Album alb;
    std::string sql = "SELECT description, creation_date, exist_image, image FROM albums WHERE title = '" + title.toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        return alb;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        alb.title = title;
        alb.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        alb.creation_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        alb.exist_image = sqlite3_column_int(stmt, 2);
        alb.image = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }

    return alb;
}

Tracks DataBase::getTracks(const QString &title)
{
    Tracks tracks;
    std::string sql = "SELECT id, title, image FROM tracks WHERE album = '" + title.toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        return tracks;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        Track track;
        track.id = sqlite3_column_int(stmt, 0);
        track.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));;
        track.image = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        track.music_file = ":/files/music/" + track.title + ".mp3";
        tracks.append(track);
    }

    return tracks;
}

Track DataBase::getTrack(const QString &album, const QString &title)
{
    Track track;
    std::string sql = "SELECT id, image FROM tracks WHERE album = '" + album.toStdString() + "' AND title = '" + title.toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        return track;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        track.id = sqlite3_column_int(stmt, 0);
        track.title = title;
        track.image = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        track.music_file = ":/files/music/" + track.title + ".mp3";
    }

    return track;
}

void DataBase::modifyPlaylist(int operation)
{
    std::string creation_date = QDateTime::currentDateTime().toString("yyyy-MM-dd").toStdString();
    std::string sql;

    playlist.exist_image = !playlist.image.isEmpty();

    std::string title =	playlist.title.toStdString();
    std::string desc = playlist.description.toStdString();
    std::string img = playlist.image.toStdString();
    std::string albumId = QString::number(playlist.albumId).toStdString();

    switch(operation) {
    case 0:
        sql = "INSERT INTO albums(title, description, creation_date, image, exist_image) "
               "VALUES('" + title + "', '" + desc + "', '" + creation_date + "', '" + img;
        if(playlist.exist_image) sql += "', 1);";
        else sql += "', 0);";
        qDebug() << sql;
        break;
    case 1:
        sql = "UPDATE albums SET title = '" + title + "', description = '" + desc + "', creation_date = '"
              + creation_date + "', image = '" + img;
        if(playlist.exist_image) sql += "', exist_image = 1 ";
        else sql += "', exist_image = 0 ";
        sql += "WHERE id = " + albumId + ";";
        break;
    case 2:
        sql = "DELETE FROM albums WHERE title = '" + title + "';";
    }

    char *zErrMsg = 0;
    int rc = sqlite3_exec(pdb, sql.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        qDebug() << sqlite3_errmsg(pdb);
    }
}

void DataBase::addTrackToPlaylist(const QString &album, const QString &title, const QString &fromAlbum)
{
    std::string sql = "SELECT image FROM tracks WHERE title = '" + title.toStdString() + "' AND album = '" + fromAlbum.toStdString() + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        qDebug() << sqlite3_errmsg(pdb);
    }

    Track track;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        track.image = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        track.album = fromAlbum;
    }
    QString image = track.image;
    if(image == "") {
        std::string sql = "SELECT image FROM albums WHERE title = '" + track.album.toStdString() + "'";
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(pdb, sql.c_str(), -1, &stmt, NULL);
        if(rc != SQLITE_OK) {
            qDebug() << "the connection to DB was not established";
            qDebug() << sqlite3_errmsg(pdb);
        }

        while(sqlite3_step(stmt) == SQLITE_ROW)
            image = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }




    sql = "INSERT INTO tracks(album, title, image) "
          "VALUES('" + album.toStdString() + "', '" + title.toStdString() + "', '" + image.toStdString() + "');";
    char *zErrMsg = 0;
    rc = sqlite3_exec(pdb, sql.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        qDebug() << sqlite3_errmsg(pdb);
    }
}

void DataBase::removeTrackFromPlaylist(const QString &album, const QString &title)
{
    std::string sql = "DELETE FROM tracks WHERE title = '" + title.toStdString() + "' AND album = '" + album.toStdString() + "'";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(pdb, sql.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        qDebug() << "the connection to DB was not established";
        qDebug() << sqlite3_errmsg(pdb);
    }
}

bool DataBase::openDB()
{
    if(sqlite3_open(fileName.toStdString().c_str(), &pdb) == SQLITE_OK) {
        qDebug() << "the connection to DB was established";
        return true;
    }
    qDebug() << "the connection to DB was not established";
    return false;
}

bool DataBase::restoreDB()
{
    if(!openDB())
        return false;

    QString sql[] = {"CREATE TABLE albums("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "title TEXT NOT NULL,"
                    "description TEXT,"
                    "creation_date TEXT NOT NULL,"
                    "yeat_album BOOL DEFAULT 0 NOT NULL,"
                    "exist_image BOOL DEFAULT 0 NOT NULL,"
                    "image TEXT"
                    ");"

                    "CREATE TABLE tracks("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "album TEXT NOT NULL,"
                    "title TEXT NOT NULL,"
                    "image TEXT"
                    ");"

                    "INSERT INTO albums(title, description, creation_date, exist_image)"
                    "VALUES('Like', 'Here you can see the tracks that you liked', '2024-09-09', 0);"

                    "INSERT INTO albums(title, description, creation_date, exist_image, image, yeat_album)"
                    "VALUES('Afterlyfe', "
                    "'Afterlyfe is the third studio album by American rapper Yeat.\n"
                    "It was released by Geffen Records, Field Trip Recordings, and Twizzy Rich.\n"
                    "The follow-up to his EP Lyfë, it contains a sole guest appearance from YoungBoy Never Broke Again as well as Yeats alter egos Kranky Kranky & Luh Geeky.',"
                    "'2019-09-18', 1, ':/files/image/afterlyfe.jpg', 1);"

                    "INSERT INTO tracks(album, title)"
                    "VALUES('Afterlyfe', 'Shhh');"

                    "INSERT INTO tracks(album, title)"
                    "VALUES('Afterlyfe', 'How it go');"

                    "INSERT INTO tracks(album, title, image)"
                    "VALUES('Afterlyfe', '123', ':/files/image/background.jpg');"

                    "INSERT INTO albums(title, description, creation_date, exist_image, image, yeat_album)"
                    "VALUES('LyfeStyle', "
                    "'LyfëStyle (originally titled 3093) is Yeats upcoming fifth studio album, following up February 2024s 2093',"
                    "'-', 1, ':/files/image/lyfestyle.jpg', 1);"

                    "INSERT INTO tracks(album, title)"
                    "VALUES('LyfeStyle', 'Lyfe');"
    };

    char *zErrMsg = 0;
    for(QString &query : sql) {
        if(sqlite3_exec(pdb, query.toStdString().c_str(), nullptr, 0, &zErrMsg) == SQLITE_OK)
            qDebug() << "Request " << query << " was completed successfuly";
        else {
            qDebug() << "Request " << query << " was not completed";
            qDebug() << "Error: " << zErrMsg;
            return false;
        }
    }
    qDebug() << "The DB was created successfuly";
    return true;
}

void DataBase::closeDB()
{
    sqlite3_close(pdb);
}


















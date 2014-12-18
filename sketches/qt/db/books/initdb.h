#ifndef INITDB_H
#define INITDB_H

#include <QtSql/QtSql>

void addBook(QSqlQuery& q, const QString& title, int year, const QVariant& authorId, const QVariant& genreId, int rating);
QVariant addGenre(QSqlQuery& q, const QString& name);
QVariant addAuthor(QSqlQuery& q, const QString& name, const QDate& birthdate);
QSqlError initDb();

#endif // INITDB_H


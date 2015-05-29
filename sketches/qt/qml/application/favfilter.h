#ifndef FAVFILTER_H
#define FAVFILTER_H
#include <QString>

class FavFilter
{
public:
    FavFilter();
    QString getTitle() { return _title; }
    void setTitle(const QString& title) {_title = title; }
private:
    QString _title;
};

#endif // FAVFILTER_H

#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <QWidget>

class OptionsPage : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsPage(QWidget *parent = 0);

    virtual QIcon getIcon() = 0;
    virtual QString getTitle() = 0;

};

#endif // OPTIONSPAGE_H

#ifndef GRAUCHYWIDGET_H
#define GRAUCHYWIDGET_H

#include <QWidget>

enum CommandFlag
{
    None = 0,
    ShowView = 1,
    ShowOptions = 2,
    ResetPosition = 4,
    ResetSkin = 8,
    Exit = 32
};

Q_DECLARE_FLAGS(CommandFlags, CommandFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(CommandFlags)


class GrauchyWidget : public QWidget
{
	Q_OBJECT

public:
    GrauchyWidget(CommandFlags command);
    ~GrauchyWidget();

private:
    void initialize();
};

#endif // GRAUCHYWIDGET_H

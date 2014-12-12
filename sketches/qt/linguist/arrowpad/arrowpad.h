#ifndef ARROWPAD
#define ARROWPAD

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class ArrowPad : public QWidget
{
    Q_OBJECT
public:
    ArrowPad(QWidget* parent = 0);

private:
   QPushButton* upButton;
   QPushButton* downButton;
   QPushButton* leftButton;
   QPushButton* rightButton;
};

#endif // ARROWPAD


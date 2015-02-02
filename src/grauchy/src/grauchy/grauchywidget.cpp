#include "grauchywidget.h"

GrauchyWidget::GrauchyWidget(CommandFlags command)
#ifdef Q_OS_MAC
    : QWidget(NULL, Qt::FramelessWindowHint)
#else
    : QWidget(NULL, Qt::FramelessWindowHint | Qt::Tool)
#endif
{
    initialize();
}

GrauchyWidget::~GrauchyWidget()
{

}

void GrauchyWidget::initialize()
{
    setObjectName("grauchy");
    setWindowTitle(tr("Grauchy"));

}



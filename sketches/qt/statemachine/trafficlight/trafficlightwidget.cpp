#include "trafficlightwidget.h"
#include <QVBoxLayout>

TrafficLightWidget::TrafficLightWidget(QWidget *parent)
    : QWidget(parent)
{
        QVBoxLayout* vbox = new QVBoxLayout(this);
        m_red = new LightWidget(Qt::red);
        vbox->addWidget(m_red);
        m_yellow = new LightWidget(Qt::yellow);
        vbox->addWidget(m_yellow);
        m_green = new LightWidget(Qt::green);
        vbox->addWidget(m_green);

        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setPalette(pal);
        setAutoFillBackground(true);
}


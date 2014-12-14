#ifndef TRAFFICLIGHTWIDGET_H
#define TRAFFICLIGHTWIDGET_H

#include <QWidget>
#include "lightwidget.h"

class TrafficLightWidget : public QWidget
{
public:
    TrafficLightWidget(QWidget* parent=0);

    LightWidget* redLight() const { return m_red; }
    LightWidget* yellowLight() const { return m_yellow; }
    LightWidget* greenLight() const { return m_green; }

private:
    LightWidget* m_red;
    LightWidget* m_yellow;
    LightWidget* m_green;
};

#endif // TRAFFICLIGHTWIDGET_H

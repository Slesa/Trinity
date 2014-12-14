#include "lightwidget.h"

void LightWidget::paintEvent(QPaintEvent *)
{
    if(!m_on) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawEllipse(0, 0, width(), height());
}


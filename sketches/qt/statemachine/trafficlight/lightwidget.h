#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>
#include <QPainter>

class LightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    LightWidget(const QColor& color, QWidget* parent=0)
        : QWidget(parent), m_color(color), m_on(false)
    {}

    bool isOn() const { return m_on; }
    void setOn(bool on)
    {
        if(on==m_on) return;
        m_on = on;
        update();
    }

public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }

protected:
    virtual void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
private:
    QColor m_color;
    bool m_on;
};

#endif // LIGHTWIDGET_H

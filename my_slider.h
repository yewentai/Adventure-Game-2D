#ifndef MY_SLIDER_H
#define MY_SLIDER_H

#include <QSlider>
#include <QDebug>

class MySlider : public QSlider {
    Q_OBJECT

            signals:
            void sliderDragged(int);

public:
    MySlider(QWidget *parent = nullptr)
            : QSlider(parent) {
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        QSlider::mouseMoveEvent(event);
        emit sliderDragged(this->value());
    }
};

#endif // MY_SLIDER_H

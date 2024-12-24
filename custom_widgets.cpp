#include "custom_widgets.h"
#include <QMessageBox>
#include <QString>

Custom_Widgets::Custom_Widgets()
{

}

QLabel_Custom_Widgets::QLabel_Custom_Widgets(QMouseEvent *event)
{

}

void QLabel_Custom_Widgets::mousePressEvent(QMouseEvent *event)
{
    // Вызываем базовую реализацию
    QLabel::mousePressEvent(event);

    // Получаем координаты
    int x = event->pos().x();
    int y = event->pos().y();

    QImage originImage(":/photo/img/rrrr.png");
    int originalWidth = originImage.width();
    int originalHeight = originImage.height();

    // Получаем размеры QLabel
    int labelWidth = this->width();
    int labelHeight = this->height();

    // Масштабируем координаты
    float scaleX = static_cast<float>(originalWidth) / labelWidth;
    float scaleY = static_cast<float>(originalHeight) / labelHeight;
    int scaledX = static_cast<int>(x * scaleX);
    int scaledY = static_cast<int>(y * scaleY);

    // Испускаем сигнал с масштабированными координатами
    emit coordinatesClicked(scaledX, scaledY);

    emit clicked();
}

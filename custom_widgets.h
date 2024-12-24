#ifndef CUSTOM_WIDGETS_H
#define CUSTOM_WIDGETS_H
#include <QLabel>
#include <QMouseEvent>

class Custom_Widgets
{
public:
    Custom_Widgets();
};

class QLabel_Custom_Widgets : public QLabel
{
    Q_OBJECT
public:
    QLabel_Custom_Widgets(QMouseEvent *event);
signals:
    void clicked();
    void coordinatesClicked(int x, int y);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    using QLabel::QLabel;


};


#endif // CUSTOM_WIDGETS_H

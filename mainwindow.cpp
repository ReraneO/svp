#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom_widgets.h"
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include <QQueue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    origin.load(":/photo/img/rrrr.png");
    view = QImage(origin);
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(QPixmap::fromImage(view).scaled(w, h, Qt::KeepAspectRatio));
    connect(ui->label, SIGNAL(clicked()), this, SLOT(QLabel_Custom_Clik_Event()));

    connect(ui->label, &QLabel_Custom_Widgets::coordinatesClicked, this, &MainWindow::QLabel_Custom_Clik_Event);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    QString numE = ui->numE->text();
    int num = ui->numE->text().toInt();
    if (num > 255 || num < 0) {
        QMessageBox::about(this, "Е:", "Неккоректное значение (0 < E < 255");
    }
    else {
        QMessageBox::about(this, "Е:", numE);
    }
}
void MainWindow::QLabel_Custom_Clik_Event(int x, int y)
{

    view = QImage(origin);
    QMessageBox::about(this, "Е:", "Клик совершен<3 ");


    int wi = ui->label->width();
    int he = ui->label->height();


    if (x < 0 || x >= wi || y < 0 || y >= he) {
        return;
    }

    QColor clickColor = view.pixelColor(x, y);
    int clickColorInt = qGray(clickColor.rgb());

    int numE = ui->numE->text().toInt();

    int minGray = clickColorInt - numE;
    int maxGray = clickColorInt + numE;
    if (minGray < 0) {
        minGray = 0;
    }
    if (maxGray > 255) {
        maxGray = 255;
    }

    QQueue<QPoint> pixelsToCheck;
    pixelsToCheck.enqueue(QPoint(x, y));


    while (!pixelsToCheck.isEmpty()) {
        QPoint currentPoint = pixelsToCheck.dequeue();
        int curX = currentPoint.x();
        int curY = currentPoint.y();

        // Проверяем границы
        if (curX < 0 || curX >= wi || curY < 0 || curY >= he) {
            continue; // Пиксел вне границ
        }

        // Получаем текущий цвет пикселя
        QColor currentColor = view.pixelColor(curX, curY);
        int currentGrayValue = qGray(currentColor.rgb());

        // Проверяем, находится ли уровень серого текущего пикселя в заданном диапазоне
        if (currentGrayValue >= minGray && currentGrayValue <= maxGray) {
            // Закрашиваем пиксель желтым цветом
            view.setPixelColor(curX, curY, QColor(255, 255, 0)); // Жёлтый

            // Debug: выводим информацию о закрашенном пикселе
            qDebug() << "Закрашиваем пиксель:" << curX << curY << "цвет:" << QColor(255, 255, 0);

            // Добавляем соседние пиксели в очередь
            pixelsToCheck.enqueue(QPoint(curX + 1, curY)); // Вправо
            pixelsToCheck.enqueue(QPoint(curX - 1, curY)); // Влево
            pixelsToCheck.enqueue(QPoint(curX, curY + 1)); // Вниз
            pixelsToCheck.enqueue(QPoint(curX, curY - 1)); // Вверх
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(view).scaled(wi, he, Qt::KeepAspectRatio));
}



void MainWindow::on_pushButton_2_clicked()
{
    int wi = ui->label->width();
    int he = ui->label->height();
    ui->label->setPixmap(QPixmap::fromImage(origin).scaled(wi, he, Qt::KeepAspectRatio));
}


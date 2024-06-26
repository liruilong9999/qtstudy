#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("painter");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPointF center(width()/2,height()/2);
    QPainter painter(this);

    QPen pen(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(QPointF(12,10),QPointF(440,550));

}


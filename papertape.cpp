#include "papertape.h"

PaperTape::PaperTape(QGraphicsItem *parent): QGraphicsObject(parent)
{
    ani = new QPropertyAnimation(this, "pos");
    this->setStr("hello");
    this->adjustPos();
}

QRectF PaperTape::boundingRect() const
{
    return QRectF(0 ,0 ,str.size()*width, height);
}

void PaperTape::setStr(QString str)
{
    this->str = str;
    lastLenth = lenth;
    lenth = str.size();
//    this->adjustPos();
    this->update();
}

int PaperTape::getWidth()
{
    return lenth*width;
}

void PaperTape::standBy(int index)
{
//    ani->setStartValue(this->pos());
    ani->setEndValue(QPointF(-(index+0.5)*width, this->pos().y()));
    ani->setDuration(230);
    ani->start();
}

void PaperTape::adjustPos()
{
    setPos(-str.size()*width/2, -height);
}

void PaperTape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBackground(QBrush(Qt::white));
    painter->eraseRect(/*-lastLenth*width/2, -height, width*1000, height*/boundingRect());
    painter->setBrush(QBrush("lightblue"));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, lenth*width, height);
    painter->setPen(Qt::black);
    painter->setPen(Qt::DotLine);
    painter->setFont(QFont("Microsoft Yahei", 13));
    for(int i=0; i<lenth; i++)
    {
        if(i!=0)
        {
            // 画分割线
            painter->drawLine(0+i*width, 0,  0+i*width,  height);
        }
        // 画字符
        painter->drawText(i*width+width/2-4, height/2+8, str.at(i));
    }
    setToolTip(this->str);
//    setPos(-str.size()*width/2, -height);
}

#ifndef PAPERTAPE_H
#define PAPERTAPE_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPropertyAnimation>

class PaperTape : public QGraphicsObject
{
    Q_PROPERTY(QPoinF pos READ pos WRITE setPos)
public:
    PaperTape(QGraphicsItem *parent = Q_NULLPTR);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;
    void setStr(QString str);
    int getWidth();
    void standBy(int index);
    void adjustPos();

private:
    int height = 50;
    int width = 50;
    QString str;
    int lenth=0, lastLenth=0;
    QPropertyAnimation *ani;
};

#endif // PAPERTAPE_H

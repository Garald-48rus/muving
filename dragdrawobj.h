#ifndef DRAGDRAWOBJ_H
#define DRAGDRAWOBJ_H

#include <QGraphicsItem>
#include <QPainter>

class dragDrawObj: public QGraphicsItem
{
public:
    dragDrawObj();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // DRAGDRAWOBJ_H

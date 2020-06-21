#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsItem>
#include <QVector>
#include "common.h"

class field: public QGraphicsItem
{
public:
    field(int, int, int);

     QRectF boundingRect() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

       void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
       void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

       void enableHoverPos(QPointF);
       void disableHover();

       bool fieldIsEmpty(const QPointF&);//функция проверки пустая ли ячейка под курсором
       eCellType getFieldType(const QPointF&);//функция узнает какой елемент под курсором

       eCellType take_field(QPointF);//фунция забирает елемент из ячейки
       void set_field(QPointF, eCellType);//функция кладет елемент в ячейку

       void boundingRectOnSceneCalc();
       qreal xtl();
       qreal ytl();
       qreal xbr();
       qreal ybr();

protected:
  virtual void init_cells() = 0;
  virtual void _draw_cells(QPainter *);

protected:
     int     mLines{0};
     int     mColumns{0};     
    QVector <eCellType> mvFields;

private:
     QPointF  mMousePos;
     QRectF  mBoundingSceneRect;
     bool    mHover{false};
     int     mCellWidth{0};
     int     mFieldWidth{0};
     int     mFieldHeight{0};


};

#endif // FIELD_H

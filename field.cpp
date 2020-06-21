#include "field.h"
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

field::field(int aLines, int aColumns, int aCellWidth)

    :mLines(aLines)//линии
    ,mColumns(aColumns)//колонки
    ,mCellWidth(aCellWidth)//высота линий
    ,mFieldWidth(aColumns * aCellWidth)//ширина поля
    ,mFieldHeight(aLines * aCellWidth)//высота поля
{
    setAcceptHoverEvents(true);//обработка движения мыши
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);//обработка зажатия кнопки мыши
}
//------------------------------------------------------
QRectF field::boundingRect() const
{
    return QRectF (0, 0, mFieldWidth, mFieldHeight);//возвращаю высоту и ширину поля
}

//---------------------------------------
void field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //рисую поле
    for(int l = 0; l <= mLines; ++l)
       painter->drawLine(QLineF(0, l*mCellWidth, mFieldWidth, l*mCellWidth));

     for(int c = 0; c <= mColumns; ++c)
       painter->drawLine(QLineF(c*mCellWidth, 0, c*mCellWidth, mFieldHeight));

     _draw_cells(painter);

     if(mHover)//если курсор над прлем подсвечиваю его
      {
        int x = mMousePos.x()/mCellWidth;
        int y = mMousePos.y()/mCellWidth;

        painter->setPen(QColor(255, 0, 0));
        painter->drawRoundedRect(x*mCellWidth,
                                 y*mCellWidth,
                                 mCellWidth,
                                 mCellWidth,
                                 2, 2);
      }
}
//------------------------------------------------------------------------------
void field::_draw_cells(QPainter *painter)
{
    if(mvFields.empty()) return;

  if(mvFields.size() == 0)
    return;
  for(int l = 0; l < mLines; ++l)
  {
    for(int c = 0; c < mColumns; ++c)
    {
      switch(mvFields[l*mColumns + c])
      {
        case eCellType::EMPTY:
        {
          break;
        }
        case eCellType::TYPE_1:
        {
          painter->drawText(c*mCellWidth + 15, l*mCellWidth + 20,"Type 1");
          break;
        }
        case eCellType::TYPE_2:
        {
          painter->drawText(c*mCellWidth + 15, l*mCellWidth + 20,"Type 2");
          break;
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
bool field::fieldIsEmpty(const QPointF &aPos)
{
  return getFieldType(aPos) == eCellType::EMPTY;
}
//------------------------------------------------------------------------------
eCellType field::getFieldType(const QPointF &aPos)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  return mvFields[l*mColumns+c];
}
//------------------------------------------------------------------------------
eCellType field::take_field(QPointF aPos)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  eCellType res = mvFields[l*mColumns+c];
  mvFields[l*mColumns+c] = eCellType::EMPTY;
  return res;
}
//------------------------------------------------------------------------------
void field::set_field(QPointF aPos, eCellType aType)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  mvFields[l*mColumns+c] = aType;
}
//------------------------------------------------------------------------------
void field::boundingRectOnSceneCalc()//вычесляю координаты ячейки
{
  QPointF pos  = scenePos();
  QRectF  rect = boundingRect();

  QPointF topLeft{pos.x() + rect.x(), pos.y() + rect.y()};
  QPointF bottomRight{topLeft.x() + rect.width(),topLeft.y() + rect.height()};

  mBoundingSceneRect.setTopLeft(topLeft);
  mBoundingSceneRect.setBottomRight(bottomRight);
}
//------------------------------------------------------------------------------
qreal field::xtl()
{
  return mBoundingSceneRect.topLeft().x();
}
//------------------------------------------------------------------------------
qreal field::ytl()
{
  return mBoundingSceneRect.topLeft().y();
}
//------------------------------------------------------------------------------
qreal field::xbr()
{
  return mBoundingSceneRect.bottomRight().x();
}
//------------------------------------------------------------------------------
qreal field::ybr()
{
  return mBoundingSceneRect.bottomRight().y();
}
//------------------------------------------------------------------------------
void field::hoverMoveEvent(QGraphicsSceneHoverEvent *apEvent)//когда курсор на элементе
{
  mMousePos = apEvent->pos();
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::hoverLeaveEvent(QGraphicsSceneHoverEvent*)//когда курсор уходит с элемента
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::enableHoverPos(QPointF aPos)//функция включает флаг когда мы над объектом
{
  mHover = true;
  mMousePos = mapFromScene(aPos);//меняю координаты курсора
  QGraphicsItem::update();//обновляю сцену
}
//------------------------------------------------------------------------------
void field::disableHover()//функция выключает флаг когда
{

  mHover = false;
  QGraphicsItem::update();
}

#include "mainscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QApplication>
#include "dragdropinfo.h"


bool distanceIsMoving(QPointF aPoint)
{
  return aPoint.manhattanLength() > QApplication::startDragDistance();
}
//---------------------------------------

mainScene::mainScene()
{
     setItemIndexMethod(QGraphicsScene::NoIndex);//отключаю индексирование чтобы рисоввалось быстрее

    _init_main_field();
    _init_primary_field();

    mDragDrawObj.hide();//скрывает объект
    addItem(&mDragDrawObj);
}
//-------------------------------------------
void mainScene::_init_main_field()
{
  mMainField.boundingRectOnSceneCalc();  //пересчитываю координаты на сцене
  addItem(&mMainField);//добавляю на сцену основное поле
}
//------------------------------------------------------------------------------
void mainScene::_init_primary_field()
{

  mPrimaryField.setPos(710, 490);//позиция доп.поля
  mPrimaryField.boundingRectOnSceneCalc();
  addItem(&mPrimaryField);//добовляю доп.поле

}
//---------------------------------------------------------------
void mainScene::mousePressEvent(QGraphicsSceneMouseEvent *apEvent)
{
    if(apEvent->button() == Qt::LeftButton)
      {
        const QPointF &pos  = apEvent->scenePos();

        dragDropinfo &ddi = dragDropinfo::instance();

        if(_is_moving_hover_main_field(pos))
        {
          if(!mMainField.fieldIsEmpty(pos))
            ddi.push({eDragInfo::MainField, mMainField.getFieldType(pos), pos});
        }
        else if(_is_moving_hover_primary_field(pos))
        {
          if(!mPrimaryField.fieldIsEmpty(pos))
            ddi.push({eDragInfo::PrimaryField, mPrimaryField.getFieldType(pos), pos});
        }
        if(!ddi.isEmpty())
        {
          mDragDrawObj.show();
          mDragDrawObj.setPos(apEvent->scenePos());
          mMouseLeftClickPos = apEvent->scenePos();

          mLeftBtnPressed = true;
        }
        QGraphicsScene::mousePressEvent(apEvent);
      }
}
//-----------------------------------------------
void mainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *apEvent)//движение курсора
{

    bool mainHover    = _is_moving_hover_main_field(apEvent->scenePos());
      bool primaryHover = _is_moving_hover_primary_field(apEvent->scenePos());

      if(!mainHover && !primaryHover)
        return;

      dragDropinfo &ddi = dragDropinfo::instance();

      if(mLeftBtnPressed)
      {
        if(!ddi.isEmpty())
        {
          if(distanceIsMoving(apEvent->pos() - mMouseLeftClickPos))
          {
            mDragDrawObj.setPos(apEvent->scenePos());

            if(mainHover)
              mMainField.enableHoverPos(apEvent->scenePos());

            if(primaryHover)
              mPrimaryField.enableHoverPos(apEvent->scenePos());
          }
        }
      }
      else
        QGraphicsScene::mouseMoveEvent(apEvent);

}
//---------------------------------------------------

bool mainScene::_is_moving_hover_main_field(const QPointF &aPos)//проверяю над каким полем курсор
{
  return (aPos.x() >= mMainField.xtl())
      && (aPos.x() <= mMainField.xbr())
      && (aPos.y() >= mMainField.ytl())
      && (aPos.y() <= mMainField.ybr());
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_primary_field(const QPointF &aPos)
{
  return (aPos.x() >= mPrimaryField.xtl())
      && (aPos.x() <= mPrimaryField.xbr())
      && (aPos.y() >= mPrimaryField.ytl())
      && (aPos.y() <= mPrimaryField.ybr());
}
//----------------------------------------------------------------------
void mainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{

    const QPointF &pos = apEvent->scenePos();

     dragDropinfo &ddi = dragDropinfo::instance();
     if(!ddi.isEmpty())
     {
       if(_is_moving_hover_main_field(pos))
       {
         if(ddi.object().from == eDragInfo::PrimaryField)
         {
           if(mMainField.fieldIsEmpty(pos))
           {
             _move_from_primary_to_main(ddi.object(), pos);
             mPrimaryField.disableHover();
           }
         }
       }
       else if(_is_moving_hover_primary_field(pos))
       {
         if(ddi.object().from == eDragInfo::MainField)
         {
           if(mPrimaryField.fieldIsEmpty(pos))
           {
             _move_from_main_to_primary(ddi.object(), pos);
             mMainField.disableHover();
           }
         }
       }
       ddi.reset();
     }

     mDragDrawObj.hide();
     mLeftBtnPressed = false;
     QGraphicsScene::mouseReleaseEvent(apEvent);

     update();
}
//------------------------------------------------------------------------------

void mainScene::_move_from_main_to_primary(sDragData aFrom, QPointF aPos)
{
  eCellType t = mMainField.take_field(aFrom.drag_pos);
  mPrimaryField.set_field(aPos, t);
}
//------------------------------------------------------------------------------
void mainScene::_move_from_primary_to_main(sDragData aFrom, QPointF aPos)
{
  eCellType t = mPrimaryField.take_field(aFrom.drag_pos);
  mMainField.set_field(aPos, t);
}

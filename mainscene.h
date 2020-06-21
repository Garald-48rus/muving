#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include "mainfield.h"
#include "primaryfield.h"
#include "dragdrawobj.h"

class mainScene: public QGraphicsScene
{
public:
    mainScene();

      void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
      void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
      void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

private:
  void _init_main_field();
  void _init_primary_field();

private:
      bool  mLeftBtnPressed{false};//флаг зажата ли кнопка мыши

      QPointF       mMouseLeftClickPos;
      mainField      mMainField;
      primaryField   mPrimaryField;
      dragDrawObj   mDragDrawObj;

      bool _is_moving_hover_main_field(const QPointF&);
      bool _is_moving_hover_primary_field(const QPointF&);


      void _move_from_main_to_primary(sDragData , QPointF );
      void _move_from_primary_to_main(sDragData , QPointF );
};

#endif // MAINSCENE_H

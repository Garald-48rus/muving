#ifndef DRAGDROPINFO_H
#define DRAGDROPINFO_H

#include "common.h"

class dragDropinfo
{
public:
    dragDropinfo();
    ~dragDropinfo();


public:
  static dragDropinfo &instance();

  bool isEmpty();

  void push(sDragData);

  sDragData pop();

  void reset();

  sDragData object()const;

private:
  sDragData mObjectInfo{eDragInfo::Unknown, eCellType::EMPTY, {0,0}};
};

#endif // DRAGDROPINFO_H

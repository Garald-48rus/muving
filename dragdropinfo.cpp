#include "dragdropinfo.h"

dragDropinfo::dragDropinfo()
{

}
//------------------------------------------------------------------------------
dragDropinfo::~dragDropinfo()
{
}
//------------------------------------------------------------------------------
dragDropinfo &dragDropinfo::instance()
{
  static dragDropinfo res;
  return res;
}
//------------------------------------------------------------------------------
bool dragDropinfo::isEmpty()
{
  return mObjectInfo.from == eDragInfo::Unknown;
}
//------------------------------------------------------------------------------
void dragDropinfo::push(sDragData aInfo)
{
  mObjectInfo = aInfo;
}
//------------------------------------------------------------------------------
sDragData dragDropinfo::pop()
{
  sDragData res = mObjectInfo;
  reset();
  return res;
}
//------------------------------------------------------------------------------
void dragDropinfo::reset()
{
  mObjectInfo.from = eDragInfo::Unknown;
}
//------------------------------------------------------------------------------
sDragData dragDropinfo::object()const
{
  return mObjectInfo;
}

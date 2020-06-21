#ifndef GRAPHICVIEWEXAMPLE_H
#define GRAPHICVIEWEXAMPLE_H

#include <QGraphicsView>
#include "mainscene.h"


class GraphicViewExample: public QGraphicsView
{
public:
    GraphicViewExample();

private:

    mainScene mScene;
};

#endif // GRAPHICVIEWEXAMPLE_H

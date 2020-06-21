#include <QApplication>
#include <graphicviewexample.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphicViewExample mScene;
    mScene.show();

    return a.exec();
}

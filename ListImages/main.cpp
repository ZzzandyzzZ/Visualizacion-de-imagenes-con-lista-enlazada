#include "mainwindow.h"
#include <QApplication>
//DoubleLinkedList<Imagen_> dlist;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();
    return a.exec();
}

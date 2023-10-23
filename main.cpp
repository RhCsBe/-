#include "chessboard.h"
#include "singleplay.h"
#include "beginning.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Beginning w;
    w.show();
    return a.exec();
}

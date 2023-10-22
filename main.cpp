#include "chessboard.h"
#include "singleplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SinglePlay w;
    w.show();
    return a.exec();
}

#include "roundbutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoundButton w;
    w.setColor (QColor (80, 164, 201));
    w.setTextColor (Qt::white);
    w.setFont (QFont ("Calibri"));
//    w.setText ("Hello World.");
    w.setText ("MENU");
    w.setTextSizeRatio (0.6);
    w.setAlignment (Qt::AlignLeft);
    w.show();

    return a.exec();
}

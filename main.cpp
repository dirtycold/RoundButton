#include "roundbutton.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int id = QFontDatabase::addApplicationFont (":/fonts/icon.ttf");
    QStringList families = QFontDatabase::applicationFontFamilies (id);

    RoundButton w;
    w.setColor (QColor (80, 164, 201));
    w.setTextColor (Qt::white);

    QString family (families.front ());
    QFont font (family);
    QFont::insertSubstitution (family, "Segoe UI");
    w.setFont (font);

//    w.setText ("Hello World.");
    w.setText ("= MENU");
    w.setTextSizeRatio (0.7);
    w.setAlignment (RoundButton::AlignBoth);
    w.show();

    QObject::connect (&w, &RoundButton::clicked, &a, &QApplication::quit);

    return a.exec();
}

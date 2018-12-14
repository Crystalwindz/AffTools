#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int nIndex = QFontDatabase::addApplicationFont("./DFPShaoNvW5GB.ttf");
    if (nIndex != -1)
    {
    QStringList strList(QFontDatabase::applicationFontFamilies(nIndex));
    if (strList.count() > 0)
    {
    QFont fontThis(strList.at(0));
    //fontThis.setPointSize(9);
    app.setFont(fontThis);
    }
    }

    MainWindow window;
    window.show();

    return app.exec();
}

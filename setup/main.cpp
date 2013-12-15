#include "app/appui.h"
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppUi ui;
    ui.show();

    return a.exec();
}

void v8Test()
{

}

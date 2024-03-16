
#include <QApplication>
#include "regWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    regWindow window;
    window.show();
    return app.exec();
}
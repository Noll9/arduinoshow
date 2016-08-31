#include "arduinoshow.h"                // Main.cpp, wird automatisch von QT erstellt
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);         // Hier wird ArduinoShow geöffnet.
    ArduinoShow w;                      // Kommunikation mit dem Betriebssystem
    w.show();

    return a.exec();
}

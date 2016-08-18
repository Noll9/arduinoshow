#ifndef ARDUINOSHOW_H
#define ARDUINOSHOW_H

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <stdio.h>

using namespace std;

namespace Ui {
class ArduinoShow;
}

class ArduinoShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArduinoShow(QWidget *parent = 0);
    ~ArduinoShow();

private slots:                                          //sämtlich Funktionen die in der GUI verwendet werden
    void on_listButton_clicked();

    void on_connectButton_clicked();

    void readArduionoData();


    void on_initButton_clicked();

    void on_disconnectButton_clicked();

    void handleErrors(QSerialPort::SerialPortError);

    void on_saveScore_clicked();

private:
    Ui::ArduinoShow *ui;                //
    QSerialPort *serialPort;

    int tempString;                     // Variable zur Highscore Sortierung
    int highscore[6]={0,0,0,0,0,0};     // Array in dem die Highscores gespeichert werden
};

#endif // ARDUINOSHOW_H

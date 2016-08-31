#ifndef ARDUINOSHOW_H                   // Definieren falls noch nicht geschehen
#define ARDUINOSHOW_H

#include <QMainWindow>                  // Einbinden der benötigten Includes

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <stdio.h>

using namespace std;

namespace Ui {
class ArduinoShow;                              // Klasse ArduinoShow deklarieren
}

class ArduinoShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArduinoShow(QWidget *parent = 0); // Ableitung der Klasse
    ~ArduinoShow();

private slots:                           //sämtlich Funktionen die in der GUI verwendet werden


    void on_listButton_clicked();       // Schaltfläche zum Anzeigen der verfügbaren USB-Slots

    void on_connectButton_clicked();    // Schaltfläche zur Verbindungsherstellung

    void readArduionoData();            // Funktion zum Auslesen des Arduino


    void on_initButton_clicked();       // Schaltfläche zum Starten des Spiels

    void on_disconnectButton_clicked(); // Schaltfläche zum Trennen der Verbindung

    void handleErrors(QSerialPort::SerialPortError);    // Funktion zur Verarbeitung von Fehlern

    void on_saveScore_clicked();        // Schaltfläche zum Anzeigen der Highscores

private:
    Ui::ArduinoShow *ui;
    QSerialPort *serialPort;

    int tempString;                     // Variable zur Highscore Sortierung
    int highscore[6]={0,0,0,0,0,0};     // Array in dem die Highscores gespeichert werden
};

#endif

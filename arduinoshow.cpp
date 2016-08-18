#include "arduinoshow.h"
#include "ui_arduinoshow.h"





ArduinoShow::ArduinoShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArduinoShow)                 //Konstructor
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);

    connect(serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleErrors(QSerialPort::SerialPortError)));
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readArduionoData()));
}

ArduinoShow::~ArduinoShow()             //Destructor
{
    delete ui;
}

void ArduinoShow::on_listButton_clicked()  {             // Wenn man auf "Anschluss" klickt, werden die USB
                                                        // die verfügbar sind, angezeigt
    QList<QSerialPortInfo> portInfoList = QSerialPortInfo::availablePorts();

    for(int i = 0; i < portInfoList.size(); i++)
    {
        QSerialPortInfo &info = portInfoList[i];
        ui->outputBrowser->append(info.portName());
    }
}

void ArduinoShow::on_connectButton_clicked()        // Wenn man auf "Verbinden" klickt, wird der eingegebene USB-Port
{                                                   // zur Verbindung mit dem Arduino vorbereitet
    serialPort->setPortName(ui->portNameEdit->toPlainText());

    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(serialPort->open(QIODevice::ReadWrite))
    {
        ui->outputBrowser->append("Connection made");       // Verbindung steht
    }
    else
    {
        ui->outputBrowser->append("Connection fail");       // Verbindung fehlgeschlagen
    }
}

 void ArduinoShow::readArduionoData()           //lesen der Daten, welche vom Arduino kommen
 {
    QByteArray data = serialPort->readAll();
    QString str = data;
    tempString= str.toInt();                    // Umwandeln des Strings in einen Integerwert
    tempString*=1000;                           // für den Highscore

    if(tempString>0){

        ui->outputHistorie->append(QString::number(tempString));        // Ausgabe im Feld "Historie
    }
    if(tempString>0){

        ui->outputPunkte->append(QString::number(tempString));          // Ausgabe im Feld für die aktuelle Punktzahl
    }

     int newScore = tempString;

     //ui->punktzahl->setText(QString::number(newScore));
   // QString newScoreInText = QString::number(newScore);


    for(int i=0; i<5 ;i++){             // Highscore-Array wird durchlaufen

      if (highscore[i]<=newScore){        // vergleich mit der akutell erreichten Punktzahl

          int tempScore= highscore[i];     // Einfügen und Verschieben falls neuer Highscore erreicht wurde
          highscore[i]=newScore;
          newScore=tempScore;

       }


    }


 }

void ArduinoShow::on_initButton_clicked()  // Wenn man auf "Start" klickt
{




    ui->outputPunkte->QTextBrowser::clear();      //löschen des Feldes für die aktuelle Punktzahl
    QString str = "I";                            // Freigabe für das Spiel an den Arduino
    QByteArray data = str.toUtf8();
    serialPort->write(data);        //senden zum Arduino
}


void ArduinoShow::on_disconnectButton_clicked()  //Wenn man auf "Trennen" klickt, wird die Verbindung zum Arduino unterbrochen
{
    serialPort->close();
    ui->outputBrowser->append("Connection close");

    for(int a=0;a<5;a++){               // Löschen des Highscore Feldes

        highscore[a]=0;
    }
}

void ArduinoShow::handleErrors(QSerialPort::SerialPortError error)      // Anzeige bei Fehlern
{
    if (error == QSerialPort::ResourceError)
    {
        serialPort->close();
        ui->outputBrowser->append("There was an error");
    }
}

void ArduinoShow::on_saveScore_clicked()                    // Wenn man auf "Highscore" klickt, werden die im Array
{                                                           // gepseicherten Punktezahlen angezeigt

    QString platz_eins_t = QString::number(highscore[0]);
    ui->platz_eins->setText(platz_eins_t);

    QString platz_zwei_t = QString::number(highscore[1]);
    ui->platz_zwei->setText(platz_zwei_t);

    QString platz_drei_t = QString::number(highscore[2]);
    ui->platz_drei->setText(platz_drei_t);

    QString platz_vier_t = QString::number(highscore[3]);
    ui->platz_vier->setText(platz_vier_t);

    QString platz_funf_t = QString::number(highscore[4]);
    ui->platz_funf->setText(platz_funf_t);


}

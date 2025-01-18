#ifndef GROUND_STATION_H
#define GROUND_STATION_H

#include <iostream>
#include <memory>

#include <QObject>
#include <QSerialPort>

#include <transceiver.h>

class ground_station : public QObject
{
  Q_OBJECT

  public :
    ground_station();

    std::shared_ptr< QSerialPort > get_serial_port();
    //void set_radio_configured();
    bool is_radio_running();

  public slots :
    void start_radio();
    void stop_radio();

  private :
    bool  radio_configured;
    std::shared_ptr< QSerialPort > p_serial_port;
    std::shared_ptr< transceiver > p_radio;

    // Thread 
    // Needs to be qt version of thread to access QSerialPort
    QThread       _thread_radio;
};

#endif

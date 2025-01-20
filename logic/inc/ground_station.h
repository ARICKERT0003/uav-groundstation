#ifndef GROUND_STATION_H
#define GROUND_STATION_H

#include <iostream>
#include <memory>

#include <QObject>
#include <QSerialPort>

#include <transceiver.h>
#include <thread_radio.h>

class ground_station : public QObject
{
  Q_OBJECT

  public :
    ground_station();

    void set_radio_config( std::shared_ptr< serial_config_t > );

    bool is_radio_running();
    void radio_start();
    void radio_stop();

  public slots :
    void set_state_change( std::shared_ptr< state_radio_t > state ); 

  signals :
    void sig_radio_config( std::shared_ptr< serial_config_t > );
    void sig_radio_start();
    void sig_radio_stop();

  private :
    std::shared_ptr< transceiver >      p_radio;
    std::shared_ptr< serial_config_t >  p_radio_config;
    std::shared_ptr< state_radio_t >    p_radio_state;

    // Thread 
    std::unique_ptr< thread_radio >     p_thread_radio;
};

#endif

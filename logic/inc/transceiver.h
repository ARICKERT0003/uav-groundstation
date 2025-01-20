#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <serial_port_config.h>
#include <receiver.h>
#include <switch_timed.h>

typedef struct 
{
  bool  configured    : 1;
  bool  opened        : 1;
  bool  running       : 1;
  bool  pending_stop  : 1;
  bool  error         : 1;
  bool  not_used      : 3;
} state_radio_t;

class transceiver : public QObject
{
  Q_OBJECT

  public :

    // Pointer Type
    transceiver();

    typedef std::shared_ptr< transceiver > ptr;
    std::shared_ptr< state_radio_t > get_state();

    // Serial Connection
    std::shared_ptr< QSerialPort > p_port;

    void loop();
    // Callback
    //typedef bool (*p_rx_callback_t)( const mavlink_message_t&, void*, void*);
    //typedef void (*p_tx_callback_t)( std::shared_ptr< MavlinkQueue > );

    //bool initialize( const std::string&, int, MavlinkQueue::Ptr );
    //void set_rx_callback( p_rx_callback, void*, void* );
    //void set_tx_callback( p_tx_callback );

  public slots :
    void configure( std::shared_ptr< serial_config_t > );
    void start();
    void stop();

  signals :
    void state_changed( std::shared_ptr< state_radio_t > );

  private:

    // Vars
    // =======================
    std::mutex _mu;

    // Timers
    std::shared_ptr< switch_timed > p_timer_rx;
    std::shared_ptr< switch_timed > p_timer_tx;

    // Receiver & Transmitter
    std::unique_ptr< receiver > p_rcvr;

    // State
    std::shared_ptr< state_radio_t > p_state;
    
    bool  _stop_loop;

    // Error
    QSerialPort::SerialPortError _qerror;
    bool _error;

    // Functions
    // =======================
    /*
    void run_thread();

    Transmitter transmitter;

    MavlinkQueue::Ptr _pMsgQueue;

    // Mavlink
    int _mavDropped = 0;
    mavlink_status_t _mavStatus;
    mavlink_message_t _msg;

    // Callback
    p_rx_callback_t _rx_callback = nullptr;
    p_tx_callback_t _tx_callback = nullptr;
    void* _param1 = NULL;
    void* _param2 = NULL;

    // Thread
    bool _loopStatus = false;
    std::thread _transceiverThread;
    */
};

#endif

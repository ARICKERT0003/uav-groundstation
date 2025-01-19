#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <receiver.h>
#include <switch_timed.h>

class transceiver : public QObject
{
  Q_OBJECT

  public :

    enum state_thread : bool
    {
      NRUNNING,
      RUNNING,
    };

    // Pointer Type
    transceiver();

    typedef std::shared_ptr< transceiver > ptr;

    void set_port( std::shared_ptr< QSerialPort > port );
    
    void start();
    void stop();
    bool get_state();

    // Callback
    //typedef bool (*p_rx_callback_t)( const mavlink_message_t&, void*, void*);
    //typedef void (*p_tx_callback_t)( std::shared_ptr< MavlinkQueue > );

    //bool initialize( const std::string&, int, MavlinkQueue::Ptr );
    //void set_rx_callback( p_rx_callback, void*, void* );
    //void set_tx_callback( p_tx_callback );
    //void message_loop();
    //void start();
    //void stop();

  public slots :
    void configure( config_radio_t* );
    void loop();
    void enable();

  signals :
    void configured();
    void state_change( transceiver::state_thread );


  private:

    // Vars
    // =======================
    // Serial Connection
    std::shared_ptr< QSerialPort > p_port;

    // Timers
    std::shared_ptr< switch_timed > p_timer_rx;
    std::shared_ptr< switch_timed > p_timer_tx;

    // Receiver & Transmitter
    std::unique_ptr< receiver > p_rcvr;

    // State
    state_thread _state_thread_current;
    state_thread _state_thread_pending;

    // Thread 
    // Needs to be qt version of thread to access QSerialPort
    QThread       _thread;
    //std::thread  _thread;
    
    bool  _enable;

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

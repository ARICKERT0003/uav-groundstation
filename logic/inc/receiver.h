/**
  * @file    Receiver.h
  * @brief   Thread safe object for reading from serial and populating
  *          Mavlink Message Struct 
  * @author  Alex Rickert
  */
 
#ifndef RECEIVER_H
#define RECEIVER_H

//#include <stdio.h>
#include <iostream>
#include <memory>
//#include <errno.h>
//#include <string.h>
//#include <mutex>
//#include <thread>

#include <QSerialPort>

//#include <spdlog/spdlog.h>
//#include <mavlink/common/mavlink.h>

//#include "SerialConnection.h"
//#include "MessageHandler.h"

class receiver
{
  public:
    //receiver( std::shared_ptr< QSerialPort > pport=nullptr, std::shared_ptr< mavlink_rx_container > prx_container=nullptr )

    // Callback
    //typedef bool (*ptrCallbackFunc)(const mavlink_message_t&, void*, void*);

    void set_port( std::shared_ptr< QSerialPort > pport );
    bool get_messages();

    //void initialize(std::shared_ptr< Serial >);
    //void start();
    //void stop();
    //void setCallback(ptrCallbackFunc, void*, void*);

  private:

    // Connection
    std::shared_ptr< QSerialPort > p_port;
    
    // Callback
    //ptrCallbackFunc _messageCallback = NULL;
    //void* _callbackParam1 = NULL;
    //void* _callbackParam2 = NULL;

    //// Thread
    //bool _loopStatus = false;
    //std::mutex _mu;
    //std::thread _receiverThread;

    // Mavlink
    //int _mavDropped = 0;
    //mavlink_status_t _mavStatus;
    //mavlink_message_t _msg;
    
    //void messageLoop();
};

#endif

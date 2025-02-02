/**
  * @file    Receiver.cpp
  * @brief   Receiver implementation file
  * @author  Alex Rickert
  */

#include "receiver.h"

//receiver::receiver( std::shared_ptr< QSerialPort > pport=nullptr, std::shared_ptr< mavlink_rx_container > prx_container=nullptr )
//{
//  p_port = pport;
//  p_rx_container = prx_container;
//} 

void receiver::set_port( std::shared_ptr< QSerialPort > pport )
{ p_port = pport; }

bool receiver::get_messages()
{
  while( sizeof(mavlink_message_t) <= (size_t)(p_port->bytesAvailable()) )
  {
    //p_port->read( p_rx_buffer, sizeof(mavlink_message_t) ); 
    std::cout << "Received a msg\n";
  }
  return true;
}

//void Receiver::initialize(std::shared_ptr< Serial > ptrPort) 
//{
//  _ptrPort = ptrPort;
//  std::cout << "Receiver::prelog\n";
//  spdlog::get("Status")->trace("Receiver::initialize");
//  spdlog::get("Status")->flush();
//  std::cout << "Receiver::postlog\n";
//}
//
//void Receiver::setCallback(ptrCallbackFunc callbackFunc, void* callbackParam1, void* callbackParam2)
//{ 
//  _messageCallback = callbackFunc; 
//  _callbackParam1 = callbackParam1;
//  _callbackParam2 = callbackParam2;
//}
//
//void Receiver::start()
//{
//  _loopStatus = true;
//  _receiverThread = std::thread(&Receiver::messageLoop, this); 
//}
//
//void Receiver::stop()
//{ 
//  _loopStatus = false;
//  _receiverThread.join(); 
//  
//  if(! _receiverThread.joinable() )
//  { spdlog::get("Status")->trace("Receiver::stop"); }
//
//  _ptrPort->closePort();
//}

//void Receiver::messageLoop()
//{
//  while(_loopStatus)
//  {
//    if(! getMessage(_msg) )
//    { continue; }
//
//    if(! _messageCallback(_msg, _callbackParam1, _callbackParam2) )
//    { spdlog::get("Status")->warn("Receiver::messageLoop: Received Message from wrong Vehicle"); }
//  }
//}

//bool receiver::get_message(mavlink_message_t& msg)
//{
//  int portStatus = 0;
//  bool msgComplete = false;
//  uint8_t byte = 0;
//
//  portStatus = _ptrPort->readPort(byte); 
//  if(portStatus == -1)
//  { 
//    spdlog::get("Status")->warn("Receiver::getMessage: Port Error:\t{}", strerror(errno));
//    spdlog::get("Status")->flush();
//    return msgComplete; 
//  }
//  
//  if(portStatus == 0)
//  { 
//    spdlog::get("Status")->trace("Receiver::getMessage: Waiting for msg");
//    spdlog::get("Status")->flush();
//    return msgComplete; 
//  }
//
//  msgComplete = mavlink_parse_char(MAVLINK_COMM_1, byte, &msg, &_mavStatus);
//
//  if(_mavDropped != _mavStatus.packet_rx_drop_count)
//  {
//    _mavDropped = _mavStatus.packet_rx_drop_count;
//    spdlog::get("Status")->warn("Receiver::getMessage: Packet Dropped");
//    spdlog::get("Status")->warn("Receiver::getMessage: Total Package Loss:\t{}", _mavDropped);
//    spdlog::get("Status")->flush();
//  }
// 
//  return msgComplete;
//}


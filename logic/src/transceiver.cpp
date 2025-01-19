#include <transceiver.h>

transceiver::transceiver()
{
  p_timer_rx = std::make_shared< switch_timed >( 500U, true );
  p_timer_tx = std::make_shared< switch_timed >( 100U, true );

  p_rcvr  = std::make_unique< receiver >();
  //p_transmitter = std::make_shared< transmitter >();

  _enable = false;
  //_state_thread_current = state_thread::NRUNNING;
  //_state_thread_pending = state_thread::NRUNNING;
  _qerror = QSerialPort::NoError;
}

void transceiver::config( port_config_t* p_config )
{
  p_port->setPortName(    p_config->name ); 
  p_port->setBaudRate(    p_config->baud_rate, p_config->direction );
  p_port->setDataBits(    p_config->data_bits );
  p_port->setFlowControl( p_config->flow_control );
  p_port->setParity(      p_config->parity );
  p_port->setStopBits(    p_config->stop_bits );
  emit configured();
}

void transceiver::set_port( std::shared_ptr< QSerialPort > port )
{ 
  p_port = port;
  p_rcvr->set_port( port ); 
} 

void transceiver::enable()
{ _enable = true; }

void transceiver::stop()
{ _enable = false; }

//  if( _state_thread_current == state_thread::NRUNNING )
//  { return; }
//
//  while( !_thread.isFinished() )
//  {} // Block
//
//  //_thread.join();
//  _thread.exit();
//  _state_thread_current = NRUNNING;
//
//  std::cout << "Stopped\n";
//  p_port->close();
//}

bool transceiver::get_state()
{ return _enable; }

// Private
// =======================
void transceiver::loop()
{
  std::cout << "looping\n";
  if( !p_port )
  { 
    std::cout << "Error\n";
    return; 
  }

  if( !p_port->open( QIODeviceBase::ReadWrite ) )
  { 
    _error = true; 
    std::cout << "Error\n";
    return; 
  }

  while( !_qerror & !_enable )
  {
    if( p_timer_rx->run() ) 
    { p_rcvr->get_messages(); }

    //if( p_timer_tx->run() )
    //{ p_transmitter->run(); }

    _qerror = p_port->error();
  }
}


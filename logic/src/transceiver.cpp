#include <transceiver.h>

transceiver::transceiver()
{
  p_port      = std::make_shared< QSerialPort >();
  p_timer_rx  = std::make_shared< switch_timed >( 500U, true );
  p_timer_tx  = std::make_shared< switch_timed >( 100U, true );

  p_rcvr  = std::make_unique< receiver >();
  p_rcvr->set_port( p_port );

  //p_transmitter = std::make_shared< transmitter >();
  
  p_state = std::make_shared< state_radio_t >();
  p_state->configured   = false;
  p_state->opened       = false;
  p_state->running      = false;
  p_state->error        = false;

  _stop_loop = false;
  
  _qerror = QSerialPort::NoError;
}

std::shared_ptr< state_radio_t > transceiver::get_state()
{ return p_state; }

void transceiver::loop()
{
  while( !_stop_loop )
  {
    std::cout << "looping\n";

    // Make sure port created
    if( !p_port )
    { 
      std::cout << "Error 1\n";
      continue; 
    }

    // Make sure configured
    if( !p_state->configured ) 
    { continue; }

    // Make sure port opened
    if( !p_port->open( QIODeviceBase::ReadWrite ) )
    { 
      _error = true; 
      std::cout << p_port->error();
      std::cout << "Error 2\n";
      return; 
    }

    p_state->opened   = true;
    p_state->running  = true;
    emit state_changed( p_state );

    while( !_qerror & !_stop_loop )
    {
      //std::cout << "Loop 2\n";
      if( p_timer_rx->run() ) 
      { 
        std::cout << "Loop RX\n";
        p_rcvr->get_messages(); 
      }

      //if( p_timer_tx->run() )
      //{ p_transmitter->run(); }

      _qerror = p_port->error();
    }

    std::cout << "Stopped\n";
    p_state->running  = false;
    emit state_changed( p_state );
  }
}

// Slots
// =======================

void transceiver::configure( std::shared_ptr< serial_config_t > p_config )
{
  qDebug() << "Config\n";
  p_port->setPortName(    p_config->name ); 
  p_port->setBaudRate(    p_config->baud_rate, p_config->direction );
  p_port->setDataBits(    p_config->data_bits );
  p_port->setFlowControl( p_config->flow_control );
  p_port->setParity(      p_config->parity );
  p_port->setStopBits(    p_config->stop_bits );

  p_state->configured = true;
  emit state_changed( p_state );
}

void transceiver::start()
{ _stop_loop = false; } 

void transceiver::stop()
{ _stop_loop = true; }

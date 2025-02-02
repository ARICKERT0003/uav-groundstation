#include <transceiver.h>

transceiver::transceiver()
{
  p_port      = std::make_shared< QSerialPort >();
  p_timer_rx  = std::make_shared< switch_timed >( 500U, true );
  p_timer_tx  = std::make_shared< switch_timed >( 100U, true );

  p_rcvr  = std::make_unique< receiver >();
  p_rcvr->set_port( p_port );

  //p_transmitter = std::make_shared< transmitter >();
  
  _ready_rx = false;
  reset();
  ext_state_reset();

  //connect( p_port.get(), &QSerialPort::readyRead, this, &transceiver::ready_rx );
}

void transceiver::ready_rx()
{ _ready_rx = true; }

transceiver::ext_state_t transceiver::get_state()
{ return radio_ext_state; }

void transceiver::loop()
{
  while( true )
  {
    switch( radio_state )
    {
      case STATE_LOOP_CREATE : 
        qDebug() << "Create\n";
        if( p_port )
        { 
          radio_ext_state.created = true;
          emit state_changed( radio_ext_state );
          radio_state = STATE_LOOP_CONFIGURE; 
        }
        break;

      case STATE_LOOP_CONFIGURE : 
        qDebug() << "Configure\n";
        if( radio_ext_state.configured )
        { 
          qDebug() << "Read Buffer Size: " << p_port->readBufferSize() << "\n";
          radio_state = STATE_LOOP_OPEN; 
        }
        break;

      case STATE_LOOP_OPEN : 
        qDebug() << "Open\n";
        if( !p_port->open( QIODeviceBase::ReadWrite ) )
        { 
          radio_ext_state.opened = false;
          emit sig_error( p_port->error() );
          reset();
          return;
        }
        else
        { 
          radio_ext_state.opened = true;
          emit state_changed( radio_ext_state );
          radio_state  = STATE_LOOP_RUN; 
        }
        break;

      case STATE_LOOP_RUN :

        radio_ext_state.running = true;
        emit state_changed( radio_ext_state );

        while( !_qerror & !(radio_ext_state.stop) )
        {
          if( p_timer_rx->run() ) 
          { 
            std::cout << "Loop RX\n";
            p_port->waitForReadyRead();
            p_rcvr->get_messages(); 
          }

          //if( p_timer_tx->run() )
          //{ p_transmitter->run(); }

          _qerror = p_port->error();
        }
        
        if( _qerror )
        { emit sig_error( p_port->error() ); }
        reset();
        radio_ext_state.configured  = false;
        radio_ext_state.opened      = false;
        radio_ext_state.running     = false;
        emit state_changed( radio_ext_state );
        return;

      default :
        qDebug() << "State default" << radio_state << "\n";
        break;
    } // end switch

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
  p_port->setReadBufferSize( 20*sizeof(mavlink_message_t) );

  radio_ext_state.configured = true;
  emit state_changed( radio_ext_state );
}

void transceiver::start()
{ 
  radio_ext_state.stop  = false; 
  emit state_changed( radio_ext_state );
  radio_state           = STATE_LOOP_CREATE;
} 

void transceiver::stop()
{ 
  radio_ext_state.stop = true; 
  emit state_changed( radio_ext_state );
} 

// Private
// =======================

void transceiver::reset()
{
  p_port->close();
  radio_state = STATE_LOOP_CREATE;
  _qerror     = QSerialPort::NoError;
}

void transceiver::ext_state_reset()
{
  radio_ext_state.created     = false;
  radio_ext_state.configured  = false;
  radio_ext_state.opened      = false;
  radio_ext_state.running     = false;
  radio_ext_state.stop        = false;
} 
  


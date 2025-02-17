#include <ground_station.h>

ground_station::ground_station()
{
  // Make Components
  p_radio       = std::make_shared< transceiver >();
  radio_state   = p_radio->get_state();

  // Radio
  p_thread_radio = std::make_unique< thread_radio >( p_radio );
  p_radio->p_port->moveToThread( p_thread_radio.get() );

  connect( this, &ground_station::sig_radio_config, p_radio.get(), &transceiver::configure ); 
  connect( this, &ground_station::sig_radio_start, p_radio.get(), &transceiver::start ); 
  connect( this, &ground_station::sig_radio_stop, p_radio.get(), &transceiver::stop ); 
  connect( p_radio.get(), &transceiver::state_changed, this, &ground_station::set_state_change );
  //connect( &_thread_radio, &QThread::started, p_radio.get(), &transceiver::loop );
}

bool ground_station::is_radio_running()
{ return radio_state.running; }

void ground_station::set_state_change( transceiver::ext_state_t state )
{ 
  std::cout << "State Change\n";
  radio_state = state; 

  emit sig_radio_state_change( state );

  if( !p_thread_radio->isRunning() )
  {
    p_thread_radio->quit();
    p_thread_radio->wait();
  }
}

void ground_station::set_radio_config( std::shared_ptr< serial_config_t > p_config )
{ 
  p_radio_config = p_config;
  if( p_thread_radio->isRunning() )
  { 
    emit sig_radio_config( p_radio_config ); 
    return;
  }
}

void ground_station::radio_start()
{ 
  if( !p_thread_radio->isRunning() )
  { p_thread_radio->start(); }
  emit sig_radio_config( p_radio_config ); 
  emit sig_radio_start();
}

void ground_station::radio_stop()
{ 
  emit sig_radio_stop(); 

  //while( p_radio_state->running )
  //{ std::cout << "Stopping\n"; } // block

}

#include <ground_station.h>

ground_station::ground_station()
{
  // Make Components
  p_serial_port = std::make_shared< QSerialPort >();
  p_radio       = std::make_shared< transceiver >();

  // Share Components
  p_radio->set_port( p_serial_port );

  // Radio
  p_radio->moveToThread( &_thread_radio );
  connect( &_thread_radio, &QThread::started, p_radio.get(), &transceiver::loop );
}

std::shared_ptr< QSerialPort > ground_station::get_serial_port()
{ return p_serial_port; }

//void ground_station::set_radio_configured()
//{ radio_configured = true; }

void ground_station::start_radio()
{ 
  if( _thread_radio.isRunning() )
  { return; }
  _thread_radio.start(); 
  p_radio->start(); 
}

void ground_station::stop_radio()
{ p_radio->stop(); }

bool ground_station::is_radio_running()
{ return p_radio->get_state(); }

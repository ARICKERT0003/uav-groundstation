#ifndef MAVLINK_RADIO_H
#define MAVLINK_RADIO_H

class mavlink_radio
{
  // Make Components
  p_xcvr      = std::make_shared< transceiver >();
  xcvr_state = p_xcvr->get_state();

  // Radio
  p_thread_radio = std::make_unique< thread_radio >( p_radio );
  p_radio->p_port->moveToThread( p_thread_radio.get() );
  
};

#endif

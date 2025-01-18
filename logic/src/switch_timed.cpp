#include <switch_timed.h>

switch_timed::switch_timed( uint32_t trigger_ms, bool auto_reset )
  : active( false ),
  auto_reset( auto_reset ),
  time_trigger_ms( std::chrono::milliseconds(trigger_ms) ),
  time_duration_ms( 0 )
{}

bool switch_timed::run()
{
  if( !active ) 
  { 
    time_start = std::chrono::steady_clock::now();
    active = true;
    return false;
  }

  time_now = std::chrono::steady_clock::now();
  time_duration_ms = std::chrono::duration_cast< std::chrono::milliseconds>( time_now - time_start );

  if( time_duration_ms < time_trigger_ms ) 
  { return false; }

  if( !auto_reset )
  { 
    active = false;
    return true;
  }

  time_start = std::chrono::steady_clock::now();
  return true;
}




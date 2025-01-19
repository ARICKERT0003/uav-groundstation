#include <thread_radio.h>

thread_radio::thread_radio()
{
  p_radio = std::make_unique< transceiver >();
}

void thread_radio::run()
{ p_radio->loop(); }

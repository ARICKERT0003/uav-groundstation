#include <thread_radio.h>

thread_radio::thread_radio( std::shared_ptr< transceiver > radio )
{ p_radio = radio; }

void thread_radio::run()
{ p_radio->loop(); }

#ifndef SWITCH_TIMED_H
#define SWITCH_TIMED_H

#include <chrono>

class switch_timed
{
  public :
    switch_timed( uint32_t trigger_ms = 0, bool auto_reset = false );
    bool run();

  private:
    bool  active;
    bool  auto_reset;
    std::chrono::milliseconds time_trigger_ms;
    std::chrono::milliseconds time_duration_ms;
    std::chrono::time_point<std::chrono::steady_clock> time_start;
    std::chrono::time_point<std::chrono::steady_clock> time_now;
};

#endif

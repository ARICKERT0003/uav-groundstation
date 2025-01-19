#ifndef THREAD_RADIO_H
#define THREAD_RADIO_H

#include <memory>

#include <transceiver.h>

class thread_radio : public QThread
{
  Q_OBJECT

  public :

    thread_radio();

  private :

    std::unique_ptr< transceiver > p_radio; 

    void run() override;

  signals :
};

#endif

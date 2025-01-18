#ifndef XCVR_THREAD_H
#define XCVR_THREAD_H

#include <QThread>

class xcvr_thread : public QThread
{
  Q_OBJECT

  void run() override;
};

#endif

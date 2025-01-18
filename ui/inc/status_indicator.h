#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

#include <QtWidgets>
#include <QLabel>

class status_indicator : public QLabel
{
  Q_OBJECT

  public :
    explicit status_indicator( QLabel* parent = nullptr );

  private :
};

#endif

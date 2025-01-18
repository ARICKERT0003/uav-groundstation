#ifndef TAB1_H
#define TAB1_H

#include <memory>

#include <QtWidgets>
#include <QLabel>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QGridLayout>

#include <serial_config_box.h>

#include "ground_station.h"

class tab_1 : public QWidget
{
  Q_OBJECT

  public :
    explicit tab_1( QWidget* parent = nullptr );
    //void set_radio( std::shared_ptr< transceiver > radio );

  private : 
    //serial_config_box* p_serial_config_box  = nullptr;
};

#endif

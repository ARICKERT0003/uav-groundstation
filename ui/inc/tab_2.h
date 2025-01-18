#ifndef TAB2_H
#define TAB2_H

#include <QtWidgets>

#include <sql_config_box.h>

class tab_2 : public QWidget
{
  Q_OBJECT

  public :
    explicit tab_2( QWidget* parent = nullptr );

  private :
    QGroupBox* p_sql_config_box = nullptr;
    QGroupBox* p_box = nullptr;
};

#endif

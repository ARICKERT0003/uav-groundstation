#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>

#include <QtWidgets>
#include <QDialog>
#include <QDebug>

#include <tab_1.h>
#include <sql_config_box.h>

#include <tab_2.h>
#include <telem_tbl.h>

//#include <tab_3.h>

#include "ground_station.h"

class main_window : public QDialog
{
  Q_OBJECT

  public :
    explicit main_window( QWidget* parent = nullptr );
    //void init();
    //void set_radio( std::shared_ptr< transceiver > radio );

  private : 

    std::shared_ptr< ground_station >     p_gs;
    
    std::unique_ptr< QTabWidget >         p_main_widget;

    std::shared_ptr< tab_1 >              p_tab1;
    std::shared_ptr< serial_config_box >  p_serial_config_box;
    std::shared_ptr< sql_config_box >     p_sql_config_box;
    
    std::shared_ptr< tab_2 >              p_tab2;
    std::unique_ptr< telem_tbl >          p_telem_tbl;
};


#endif

#ifndef TELEM_TBL_H
#define TELEM_TBL_H

#include <iostream>
#include <memory>

#include <QtWidgets>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableView>
#include <QGridLayout>

#include <ground_station.h>

class telem_tbl : public QWidget
{
  Q_OBJECT
  
  public :
  explicit telem_tbl( QWidget* parent = nullptr );

  private :
  std::shared_ptr< QSqlTableModel > p_model;
  std::shared_ptr< QTableView >     p_view;
};

#endif

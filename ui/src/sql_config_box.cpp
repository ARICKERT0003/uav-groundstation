#include <sql_config_box.h>

sql_config_box::sql_config_box( QGroupBox* parent )
  : QGroupBox(parent),
  p_driver_label(     new QLabel( tr("Driver:") ) ),
  p_driver_combo_box( new QComboBox ),
  p_file_label(       new QLabel( tr("File:") ) ),
  p_file_line_edit(   new QLineEdit )
{
  setTitle( "SQL Configuration" );

  // SQL Driver
  QStringList driver_list = QSqlDatabase::drivers();
  p_driver_combo_box->addItems( driver_list );

  // SQL Database File


  QGridLayout* layout = new QGridLayout;
  layout->addWidget( p_driver_label,      0, 0 );
  layout->addWidget( p_driver_combo_box,  0, 1 );
  layout->addWidget( p_file_label,        1, 0 );
  layout->addWidget( p_file_line_edit,    1, 1 );
  setLayout( layout );
}

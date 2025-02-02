#ifndef SQL_CONFIG_BOX_H
#define SQL_CONFIG_BOX_H

#include <QtWidgets>
#include <QGroupBox>
#include <QSqlDatabase>

class sql_config_box : public QGroupBox
{
  Q_OBJECT

  public :
    explicit sql_config_box( QGroupBox* parent = nullptr );

  private :
    QFileDialog*  p_exist_db_diag     = nullptr;
    QLabel*       p_driver_label      = nullptr;
    QComboBox*    p_driver_combo_box  = nullptr;
    QLabel*       p_file_label        = nullptr;
    QLineEdit*    p_file_line_edit    = nullptr;
};

#endif


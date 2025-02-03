#include "telemetry_status.h"

telemetry_status::telemetry_status()
{
  p_model = std::make_shared< QSqlTableModel >();
  p_view  = std::make_shared< QTableView >();

  p_model->setTable("Received Messages");
  p_model->setHeaderData( 0, Qt::Horizontal, tr("Time Stamp") );
  p_model->setHeaderData( 1, Qt::Horizontal, tr("Message Type") );

  p_view->setModel( p_model.get() );
  p_view->resizeColumnsToContents();
}

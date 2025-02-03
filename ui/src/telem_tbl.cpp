#include "telem_tbl.h"

telem_tbl::telem_tbl( QWidget* parent )
{
  p_model = std::make_shared< QSqlTableModel >();
  p_view  = std::make_shared< QTableView >();

  p_model->setTable("Received Messages");
  p_model->setHeaderData( 0, Qt::Horizontal, tr("Time Stamp") );
  p_model->setHeaderData( 1, Qt::Horizontal, tr("Message Type") );

  p_view->setModel( p_model.get() );
  p_view->resizeColumnsToContents();

  QHBoxLayout*  layout = new QHBoxLayout;
  layout->addWidget( p_view.get() );
  setLayout( layout );
}

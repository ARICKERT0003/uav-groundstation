#include <main_window.h>

main_window::main_window( QWidget* parent )
  : QDialog( parent )
{
  // Logic Component
  p_gs =  std::make_shared< ground_station >();

  // UI Components
  p_main_widget = std::make_unique< QTabWidget >();
  p_main_widget->setObjectName( "mainWidget" );
  p_main_widget->setDocumentMode( true );

  // Main Widget->Tab 1
  p_tab1 = std::make_shared< tab_1 >();
  //QGridLayout* tab1_layout = new QGridLayout;
  p_main_widget->addTab( p_tab1.get(), tr("Tab 1") );

  // [Main Widget]->[Tab 1]->[Serial Config Box]
  p_serial_config_box = std::make_shared< serial_config_box >( p_gs );
  QGridLayout* layout_t1 = new QGridLayout;
  layout_t1->addWidget( p_serial_config_box.get(), 0, 0 );
  p_tab1->setLayout( layout_t1 );

  p_main_widget->addTab( new tab_2(), tr("Tab 2") );
  p_main_widget->addTab( new tab_3(), tr("Tab 3") );

  QVBoxLayout* main_layout = new QVBoxLayout;
  main_layout->addWidget( p_main_widget.get() );
  setLayout( main_layout );
   
  p_main_widget->setTabShape( QTabWidget::TabShape::Rounded );
  setWindowTitle( tr("QT App") );
} 

//void main_window::init()
//{ 
//  p_main_widget->setTabShape( QTabWidget::TabShape::Triangular ); 
//  std::cout << "Tab Shape: " << p_main_widget->tabShape() << "\n";
//}

//void main_window::set_radio( std::shared_ptr< transceiver > radio )
//{ p_tab1->set_radio( radio ); } 

//std::shared_ptr< QSerialPort > main_window::get_port()
//{ return p_port; }

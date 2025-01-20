#include <serial_config_box.h>

serial_config_box::serial_config_box( std::shared_ptr< ground_station > pgs, QGroupBox* parent )
  : QGroupBox(parent),
  p_port_label(             new QLabel( tr("Serial Port:") ) ),
  p_port_combo_box(         new QComboBox ),
  p_baud_label(             new QLabel( tr("Baud Rate:") ) ),
  p_baud_combo_box(         new QComboBox ),
  p_direction_label(        new QLabel( tr("Direction:") ) ),
  p_direction_combo_box(    new QComboBox ),
  p_data_bits_label(        new QLabel( tr("Data Bits:") ) ),
  p_data_bits_combo_box(    new QComboBox ),
  p_flow_control_label(     new QLabel( tr("Flow Control:") ) ),
  p_flow_control_combo_box( new QComboBox ),
  p_parity_label(           new QLabel( tr("Parity:") ) ),
  p_parity_combo_box(       new QComboBox ),
  p_stop_bits_label(        new QLabel( tr("Stop Bits:") ) ),
  p_stop_bits_combo_box(    new QComboBox ),
  p_apply_btn(              new QPushButton( tr("Apply") ) ),
  p_start_stop_btn(         new QPushButton( tr("Start") ) )
{
  // Components
  // =========================
  p_gs      = pgs;
  p_config  = std::make_shared< serial_config_t >();

  // UI
  // =========================

  // Title
  setTitle( "Serial Configuration" );

  // Get Avaiable Ports
  const auto ports = QSerialPortInfo::availablePorts();
  for( QSerialPortInfo port : ports )
  { p_port_combo_box->addItem( port.portName() ); }

  // Get Supported Baud Rates
  QList<qint32> baud_rate_list = QSerialPortInfo::standardBaudRates();
  for( qint32 baud_rate : baud_rate_list )
  { p_baud_combo_box->addItem( QString::number(baud_rate) ); }

  // Get Direction
  QList<QString> directions = {"Read", "Write", "R/W" };
  for( QString direction : directions )
  { p_direction_combo_box->addItem( direction ); }

  // Get Data Bits
  QList<QString> data_bits_list = {"5", "6", "7", "8" };
  for( QString data_bits : data_bits_list )
  { p_data_bits_combo_box->addItem( data_bits ); }

  // Get Flow Control
  QList<QString> flow_controls = {"No Flow Control", "Hardware (RTS/CTS)", "Software (XON/XOFF)" };
  for( QString flow_control : flow_controls )
  { p_flow_control_combo_box->addItem( flow_control ); }

  // Parity
  QList<QString> parities = {"No Parity", "Even Parity", "Odd Parity", "Space Parity", "Mark Parity" };
  for( QString parity : parities )
  { p_parity_combo_box->addItem( parity ); }

  // Stop Bits
  QList<QString> stop_bits_list = {"1", "1.5", "2" };
  for( QString stop_bits : stop_bits_list )
  { p_stop_bits_combo_box->addItem( stop_bits ); }

  QGridLayout* layout = new QGridLayout;
  layout->addWidget( p_port_label, 0, 0 );
  layout->addWidget( p_port_combo_box, 0, 1 );
  layout->addWidget( p_baud_label, 1, 0 );
  layout->addWidget( p_baud_combo_box, 1, 1 );
  layout->addWidget( p_direction_label, 2, 0 );
  layout->addWidget( p_direction_combo_box, 2, 1 );
  layout->addWidget( p_data_bits_label, 3, 0 );
  layout->addWidget( p_data_bits_combo_box, 3, 1 );
  layout->addWidget( p_flow_control_label, 4, 0 );
  layout->addWidget( p_flow_control_combo_box, 4, 1 );
  layout->addWidget( p_parity_label, 5, 0 );
  layout->addWidget( p_parity_combo_box, 5, 1 );
  layout->addWidget( p_stop_bits_label, 6, 0 );
  layout->addWidget( p_stop_bits_combo_box, 6, 1 );
  layout->addWidget( p_apply_btn, 7, 1 );
  layout->addWidget( p_start_stop_btn, 8, 1 );
  setLayout( layout );

  p_port_combo_box->setFocus();

  // Connect
  // =========================

  // User makes selection in combobox
  connect( p_port_combo_box,          &QComboBox::activated, this, &serial_config_box::set_name );
  connect( p_baud_combo_box,          &QComboBox::activated, this, &serial_config_box::set_baud_rate );
  connect( p_direction_combo_box,     &QComboBox::activated, this, &serial_config_box::set_direction );
  connect( p_data_bits_combo_box,     &QComboBox::activated, this, &serial_config_box::set_data_bits );
  connect( p_flow_control_combo_box,  &QComboBox::activated, this, &serial_config_box::set_flow_control );
  connect( p_parity_combo_box,        &QComboBox::activated, this, &serial_config_box::set_parity );
  connect( p_stop_bits_combo_box,     &QComboBox::activated, this, &serial_config_box::set_stop_bits );

  // User click button
  connect( p_apply_btn, &QPushButton::clicked, this, &serial_config_box::sanitize ); 
  connect( p_start_stop_btn, &QPushButton::clicked, this, &serial_config_box::on_start_stop_btn ); 
  //connect( p_start_stop_btn, &QPushButton::clicked, (this->p_radio).get(), &transceiver::temp ); 
  //connect( p_start_stop_btn, &QPushButton::clicked, this, &serial_config_box::config_port ); 
  
  // Set Default Values
  set_defaults();
}

//void serial_config_box::set_radio( std::shared_ptr< transceiver > radio )
//{ p_radio = radio; }

void serial_config_box::set_defaults()
{
  p_baud_combo_box->setCurrentText( "9600" );       
  set_baud_rate();
  p_direction_combo_box->setCurrentText( "R/W" );  
  set_direction();
  p_data_bits_combo_box->setCurrentText( "8" ); 
  set_data_bits();
  p_flow_control_combo_box->setCurrentText( "No Flow Control" );
  set_flow_control();
  p_parity_combo_box->setCurrentText( "No Parity" );     
  set_parity();
  p_stop_bits_combo_box->setCurrentText( "1" );
  set_stop_bits();
}

// Slots
void serial_config_box::set_name()
{ p_config->name = p_port_combo_box->currentText(); }

void serial_config_box::set_baud_rate()
{ p_config->baud_rate = (p_baud_combo_box->currentText()).toUInt(); }

void serial_config_box::set_data_bits()
{
  uint8_t db = (p_data_bits_combo_box->currentText()).toUInt(); 
  switch( db ) {
    case 5 : p_config->data_bits  = QSerialPort::Data5; break;
    case 6 : p_config->data_bits  = QSerialPort::Data6; break;
    case 7 : p_config->data_bits  = QSerialPort::Data7; break;
    case 8 : p_config->data_bits  = QSerialPort::Data8; break;
    default : p_config->data_bits = QSerialPort::Data8; break;
  }
}

void serial_config_box::set_direction()
{ 
  QString dir = p_direction_combo_box->currentText(); 
  if( dir == "Read" )
  { p_config->direction = QSerialPort::Input; }
  else if( dir == "Write" )
  { p_config->direction = QSerialPort::Output; }
  else
  { p_config->direction = QSerialPort::AllDirections; }
}

void serial_config_box::set_flow_control()
{ 
  QString fc = p_flow_control_combo_box->currentText(); 
  if( fc == "No Flow Control" )
  { p_config->flow_control = QSerialPort::NoFlowControl; }
  else if( fc == "Hardware (RTS/CTS)" )
  { p_config->flow_control = QSerialPort::HardwareControl; }
  else if( fc == "Software (XON/XOFF)" )
  { p_config->flow_control = QSerialPort::NoFlowControl; }
  else
  { p_config->flow_control = QSerialPort::NoFlowControl; }
}

void serial_config_box::set_parity()
{ 
  QString par = p_parity_combo_box->currentText(); 
  if( par == "No Parity" )
  { p_config->parity = QSerialPort::NoParity; }
  else if( par == "Even Parity" )
  { p_config->parity = QSerialPort::EvenParity; }
  else if( par == "Odd Parity" )
  { p_config->parity = QSerialPort::OddParity; }
  else if( par == "Space Parity" )
  { p_config->parity = QSerialPort::SpaceParity; }
  else if( par == "Mark Parity" )
  { p_config->parity = QSerialPort::MarkParity; }
  else
  { p_config->parity = QSerialPort::NoParity; }
}

void serial_config_box::set_stop_bits()
{
  QString sb = p_stop_bits_combo_box->currentText(); 
  if( sb == "1" )
  { p_config->stop_bits = QSerialPort::OneStop; }
  else if( sb == "1.5" )
  { p_config->stop_bits = QSerialPort::OneAndHalfStop; }
  else if( sb == "2" )
  { p_config->stop_bits = QSerialPort::TwoStop; }
  else 
  { p_config->stop_bits = QSerialPort::OneStop; }
}

void serial_config_box::sanitize()
{
  set_name();
  if( p_config->name.isEmpty() )
  { return; } // TODO: red text to show error
    
  //qDebug() << "Port Name: " << p_port->portName()     << "\n";
  //qDebug() << "Baud Rate: " << p_port->baudRate()     << "\n";
  //qDebug() << "Data Bits: " << p_port->dataBits()     << "\n";
  //qDebug() << "Flow Ctrl: " << p_port->flowControl()  << "\n";
  //qDebug() << "Parity: "    << p_port->parity()       << "\n";
  //qDebug() << "Stop Bits: " << p_port->stopBits()     << "\n";

  p_gs->set_radio_config( p_config );
}

void serial_config_box::on_start_stop_btn()
{
  qDebug() << "Click\n";
  if( p_gs->is_radio_running() )
  {
    qDebug() << "Running, stopping\n";
    p_gs->radio_stop();
    p_start_stop_btn->setText( tr("Start") );
  }
  else
  {
    qDebug() << "Not running, starting\n";
    p_gs->radio_start();
    p_start_stop_btn->setText( tr("Stop") );
  }
}

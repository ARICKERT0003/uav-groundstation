#ifndef SERIAL_PORT_CONFIG_H
#define SERIAL_PORT_CONFIG_H

// Serial Configuration Struct
struct 
{
  QString                     name;
  quint32                     baud_rate;
  QSerialPort::DataBits       data_bits;
  QSerialPort::Direction      direction;
  QSerialPort::FlowControl    flow_control;
  QSerialPort::Parity         parity;
  QSerialPort::StopBits       stop_bits;
} typedef serial_config_t;

#endif

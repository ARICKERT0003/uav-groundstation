#ifndef SERIAL_CONFIG_BOX_H
#define SERIAL_CONFIG_BOX_H

#include <iostream>
#include <memory>

#include <QtWidgets>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QGridLayout>
#include <QDebug>

#include <ground_station.h>

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


class serial_config_box : public QGroupBox
{
  Q_OBJECT

  public :
    explicit serial_config_box( std::shared_ptr< ground_station >, QGroupBox* parent = nullptr );
    void set_radio( std::shared_ptr< transceiver > radio );
    void set_defaults();

  public slots :
    void set_name();
    void set_baud_rate();
    void set_data_bits();
    void set_direction();
    void set_flow_control();
    void set_parity();
    void set_stop_bits();

    void config_port();
    void on_start_stop_btn();

  private :

    //struct serial_config_t;

    // Components
    serial_config_t*                  p_config;
    std::shared_ptr< QSerialPort >    p_port;
    std::shared_ptr< ground_station > p_gs;

    // UI 
    QLabel*       p_port_label              = nullptr;
    QComboBox*    p_port_combo_box          = nullptr;
    QLabel*       p_baud_label              = nullptr;
    QComboBox*    p_baud_combo_box          = nullptr;
    QLabel*       p_direction_label         = nullptr;
    QComboBox*    p_direction_combo_box     = nullptr;
    QLabel*       p_data_bits_label         = nullptr;
    QComboBox*    p_data_bits_combo_box     = nullptr;
    QLabel*       p_flow_control_label      = nullptr;
    QComboBox*    p_flow_control_combo_box  = nullptr;
    QLabel*       p_parity_label            = nullptr;
    QComboBox*    p_parity_combo_box        = nullptr;
    QLabel*       p_stop_bits_label         = nullptr;
    QComboBox*    p_stop_bits_combo_box     = nullptr;
    QLabel*       p_status_indicator        = nullptr;
    QPushButton*  p_apply_btn               = nullptr;
    QPushButton*  p_start_stop_btn          = nullptr;
};

#endif

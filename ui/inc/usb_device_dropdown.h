#ifndef USB_DEV_DROPDOWN
#define USB_DEV_DROPDOWN

#include <QObject>
#include <QString>
#include <qqml.h>

class usb_dev_dd : public QComboBox
{
  QML_ELEMENT

  explicit usb_dev_dd()

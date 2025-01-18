#include <tab_3.h>

tab_3::tab_3( QWidget* parent )
  : QWidget(parent)
{
  QLabel* p_label = new QLabel(tr("Tab 3:"));

  QVBoxLayout* tab_layout = new QVBoxLayout;
  tab_layout->addWidget( p_label );
  setLayout( tab_layout );
}


#include <iostream>
#include <memory>

#include "QApplication"
#include  <QFontDatabase>

#include "main_window.h"

int main( int argc, char* argv[] )
{
  QApplication app( argc, argv );

  app.setStyle( QStyleFactory::create( "Fusion" ) );

  // Style
  QFile file_qss( "../ui/style.qss");
  file_qss.open( QFile::ReadOnly );
  QString styleSheet = QLatin1String( file_qss.readAll() );
  app.setStyleSheet( styleSheet );

  // Font
  //int font_id = QFontDatabase::addApplicationFont("../ui/font/JetBrainsMonoNerdFont-Regular.ttf");
  //if (font_id != -1) 
  //{
  //  QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
  //  QFont font(family);
  //  app.setFont(font);
  //}

  // Instantiate Ground Station
  // ::ground_station gs;
  //std::shared_ptr< transceiver > radio = std::make_shared< transceiver >();
  
  // UI
  main_window win;

  // Exchange Layer 
  //exchange_comps( &win, radio );

  win.show();

  return app.exec();
}

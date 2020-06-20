#include <iostream>
#include <memory>

#include <gtk/gtk.h>
#include <gtkmm.h>
#include <gtkmm/application.h>

extern "C" {
# include <lib/sqlite3.h>
}

#include <DB.hh>
#include <MainWindow.hh>



int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "com.nulmail.trh");
  auto builder = Gtk::Builder::create();
  builder->add_from_file("ui_main.xml");

  MainWindow* wnd = nullptr;
  builder->get_widget_derived("window", wnd);
  auto r = app->run(*wnd);
  delete wnd;

  return 0;
}

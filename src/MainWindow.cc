#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>
#include <db_tables.hh>
#include <Vocabulary.hh>
#include <Grammar.hh>



MainWindow::MainWindow()
{
  initializeBuilder();
  initializeWidgets();
  show_all_children();
}


MainWindow::~MainWindow()
{
}



void MainWindow::initializeBuilder()
{
  _builder = Gtk::Builder::create();

  try
  {
    _builder->add_from_file("ui_main.xml");
  }
  catch (const Glib::FileError& e)
  {
    std::cerr << "GtkBuilder FileError: " << e.what() << '\n';
    throw;
  }
  catch (const Glib::MarkupError& e)
  {
    std::cerr << "GtkBuilder MarkupError: " << e.what() << '\n';
    throw;
  }
  catch (const Gtk::BuilderError& e)
  {
    std::cerr << "GtkBuilder BuilderError: " << e.what() << '\n';
    throw;
  }
}



void MainWindow::initializeWidgets()
{
  Gtk::Box *box = nullptr;
  _builder->get_widget("box", box);
  add(*box);

  _vocabulary = std::make_unique<Vocabulary> (_builder);
  _grammar = std::make_unique<Grammar> (_builder);
}

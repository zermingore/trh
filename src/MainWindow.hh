#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow() = default;


private:
  void cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection);
  void cbOnSearch();

  void initializeBuilder();
  void initializeWidgets();


  Glib::RefPtr<Gtk::Builder> _builder;
};


#endif /* !MAINWINDOW_HH_ */

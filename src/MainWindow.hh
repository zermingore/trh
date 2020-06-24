#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow() = default;


private:
  void on_selection_changed(Glib::RefPtr<Gtk::TreeSelection> selection);

  void initializeBuilder();
  void initializeWidgets();


  Glib::RefPtr<Gtk::Builder> _builder;
};


#endif /* !MAINWINDOW_HH_ */

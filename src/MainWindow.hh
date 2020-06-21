#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow() = default;

  void on_selection_changed(Glib::RefPtr<Gtk::TreeSelection> selection);
};


#endif /* !MAINWINDOW_HH_ */

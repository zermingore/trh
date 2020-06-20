#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



class MainWindow: public Gtk::ApplicationWindow
{
public:
  /**
   * @brief Constructor. Build the UI
   * @brief db_file_name Database file name
   * @note Throws
   */
  //MainWindow(const char* db_file_name);
  MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder)
    : Gtk::ApplicationWindow(obj)
  {
  }

  /**
   * @brief Default destructor
   */
  virtual ~MainWindow() = default;



private:
  Glib::RefPtr<Gtk::Builder> _builder;
};

#endif /* !MAINWINDOW_HH_ */

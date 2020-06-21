#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



class DbTableWords: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableWords() {
    add(id);
    add(language);
    add(category);
    add(name);
  }

  Gtk::TreeModelColumn<unsigned int> id;
  Gtk::TreeModelColumn<short> language;
  Gtk::TreeModelColumn<short> category;
  Gtk::TreeModelColumn<Glib::ustring> name;
};



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow() = default;
};


#endif /* !MAINWINDOW_HH_ */

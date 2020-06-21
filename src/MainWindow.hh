#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

#include <gtkmm.h>



  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); add(m_col_number); add(m_col_percentage);}

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<short> m_col_number;
    Gtk::TreeModelColumn<int> m_col_percentage;
  };




class DbTableWords: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableWords() {
    add(_id);
    add(_language);
    add(_category);
    add(_name);
  }

  Gtk::TreeModelColumn<unsigned int> _id;
  Gtk::TreeModelColumn<short> _language;
  Gtk::TreeModelColumn<short> _category;
  Gtk::TreeModelColumn<Glib::ustring> _name;
};



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow() = default;


protected:
  //Signal handlers:
  void on_button_quit();


  DbTableWords m_Columns;

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView vocabularyList;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
};


#endif /* !MAINWINDOW_HH_ */

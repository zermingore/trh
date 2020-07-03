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
  void cbOnAdd();
  void cbOnConfirmAddWord();


  void initializeBuilder();
  void initializeWidgets();
  void initializeAddWord();


  Glib::RefPtr<Gtk::Builder> _builder;

  bool _addWordDisplayed = false;
  Gtk::Box *_boxAddWord;
};


#endif /* !MAINWINDOW_HH_ */

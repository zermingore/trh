#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

# include <memory>
# include <gtkmm.h>

class Vocabulary;



class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();


private:
  void initializeBuilder();
  void initializeWidgets();
  void initializeAddWord();


  Glib::RefPtr<Gtk::Builder> _builder;
  std::unique_ptr<Vocabulary> _vocabulary;
};


#endif /* !MAINWINDOW_HH_ */

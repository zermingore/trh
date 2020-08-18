#ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

# include <memory>
# include <gtkmm.h>

class Vocabulary;
class Grammar;



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
  std::unique_ptr<Grammar> _grammar;
};


#endif /* !MAINWINDOW_HH_ */

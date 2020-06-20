#ifndef UI_HH_
# define UI_HH_

# include <gtkmm/application.h>


class MainWindow;


class UI
{
public:
  UI(int argc, char *argv[]);

  int run();

private:
  MainWindow* _window;
  Glib::RefPtr<Gtk::Application> _app;
};


#endif /* !UI_HH_ */

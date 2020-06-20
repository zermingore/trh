#ifndef UI_HH_
# define UI_HH_

# include <gtkmm/application.h>


class MainWindow;


class UI
{
public:
  /**
   * @brief GTK User Interface Constructor
   * @param argc Arguments count forwarded from the main
   * @param argc Arguments vector forwarded from the main
   */
  UI(int argc, char *argv[]);

  /**
   * @brief Main loop
   */
  int run();


private:
  MainWindow* _window;
  Glib::RefPtr<Gtk::Application> _app;
};


#endif /* !UI_HH_ */

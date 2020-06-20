#include <MainWindow.hh>



int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "com.nulmail.trh");
  MainWindow window;

  return app->run(window);
}

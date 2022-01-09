#include <DB.hh>
#include <MainWindow.hh>



int main(int argc, char* argv[])
{
  DB::initialize("db.sql");

  auto app = Gtk::Application::create(argc, argv, "com.nulmail.trh");
  MainWindow window;
  int ret {app->run(window)};

  DB::close();

  return ret;
}

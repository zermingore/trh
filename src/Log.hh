# include <gtkmm.h>



class Log
{
public:
  static void init(Glib::RefPtr<Gtk::Builder> builder);

  static void print(const char* str);


private:
  static Gtk::TextView* _view;
  static Glib::RefPtr<Gtk::TextBuffer> _buffer;
};

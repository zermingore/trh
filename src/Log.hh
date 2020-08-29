#ifndef LOG_HH_
# define LOG_HH_

# include <iterator>
# include <gtkmm.h>



class Log
{
public:
  static void init(Glib::RefPtr<Gtk::Builder> builder);

  static void print(const char* str);
  static void notice(const char* str);
  static void warning(const char* str);
  static void error(const char* str);


private:
  static Gtk::TextView* _view;
  static Glib::RefPtr<Gtk::TextBuffer> _buffer;

  static Gtk::TextIter _bufIter;
  static Glib::RefPtr<Gtk::TextTagTable> _reftagtable;
  static Glib::RefPtr<Gtk::TextTag> _noticeTag;
  static Glib::RefPtr<Gtk::TextTag> _warningTag;
  static Glib::RefPtr<Gtk::TextTag> _errorTag;
};

#endif // LOG_HH_

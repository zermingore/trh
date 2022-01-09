#ifndef LOG_HH_
# define LOG_HH_

# include <gtkmm.h>



# ifdef __unix__
#   define COLOR_NORMAL  "\x1B[0m"
#   define COLOR_RED     "\x1B[31m"
#   define COLOR_GREEN   "\x1B[32m"
#   define COLOR_YELLOW  "\x1B[33m"
#   define COLOR_BLUE    "\x1B[34m"
#   define COLOR_MAGENTA "\x1B[35m"
#   define COLOR_CYAN    "\x1B[36m"
#   define COLOR_WHITE   "\x1B[37m"
# else
#   define COLOR_NORMAL  ""
#   define COLOR_RED     ""
#   define COLOR_GREEN   ""
#   define COLOR_YELLOW  ""
#   define COLOR_BLUE    ""
#   define COLOR_MAGENTA ""
#   define COLOR_CYAN    ""
#   define COLOR_WHITE   ""
# endif

/// \def Messages specific colors
# define COLOR_ERROR   COLOR_RED
# define COLOR_WARNING COLOR_YELLOW
# define COLOR_SUCCESS COLOR_GREEN
# define COLOR_VERBOSE COLOR_BLUE
# define COLOR_NOTICE  COLOR_CYAN



class Log
{
public:
  static void init(Glib::RefPtr<Gtk::Builder> builder);



  static void print();

  template<typename T, typename... Tail>
  static void print(T head, Tail... tail);



  static void notice();

  template<typename T, typename... Tail>
  static void notice(T head, Tail... tail);



  static void warning();

  template<typename T, typename... Tail>
  static void warning(T head, Tail... tail);



  static void error();

  template<typename T, typename... Tail>
  static void error(T head, Tail... tail);



private:
  static Gtk::TextView* _view;
  static Glib::RefPtr<Gtk::TextBuffer> _buffer;

  static Gtk::TextIter _bufIter;
  static Glib::RefPtr<Gtk::TextTagTable> _reftagtable;
  static Glib::RefPtr<Gtk::TextTag> _noticeTag;
  static Glib::RefPtr<Gtk::TextTag> _warningTag;
  static Glib::RefPtr<Gtk::TextTag> _errorTag;

  static std::stringstream _printerAccu;
};


#include "Log.hxx"


#endif // LOG_HH_

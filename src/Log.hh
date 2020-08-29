#ifndef LOG_HH_
# define LOG_HH_

# include <gtkmm.h>



class Log
{
public:
  static void init(Glib::RefPtr<Gtk::Builder> builder);



  // For every severity, override its print for:
  // empty parameters, const char*, char, std::string, otherwise use std::to_string

  template<typename T>
  using EnableIfStr = std::enable_if_t<std::is_constructible_v<const char*, T>>;



  static void print();

  template<typename... Tail>
  static void print(const char head, const Tail... tail);

  template<typename... Tail>
  static void print(const char* head, const Tail... tail);

  template<typename... Tail>
  static void print(const std::string& head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void print(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void print(const T head, const Tail... tail);



  static void notice();

  template<typename... Tail>
  static void notice(const char head, const Tail... tail);

  template<typename... Tail>
  static void notice(const char* head, const Tail... tail);

  template<typename... Tail>
  static void notice(const std::string& head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void notice(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void notice(const T head, const Tail... tail);



  static void warning();

  template<typename... Tail>
  static void warning(const char head, const Tail... tail);

  template<typename... Tail>
  static void warning(const char* head, const Tail... tail);

  template<typename... Tail>
  static void warning(const std::string& head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void warning(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void warning(const T head, const Tail... tail);



  static void error();

  template<typename... Tail>
  static void error(const char head, const Tail... tail);

  template<typename... Tail>
  static void error(const char* head, const Tail... tail);

  template<typename... Tail>
  static void error(const std::string& head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void error(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void error(const T head, const Tail... tail);



private:
  static Gtk::TextView* _view;
  static Glib::RefPtr<Gtk::TextBuffer> _buffer;

  static Gtk::TextIter _bufIter;
  static Glib::RefPtr<Gtk::TextTagTable> _reftagtable;
  static Glib::RefPtr<Gtk::TextTag> _noticeTag;
  static Glib::RefPtr<Gtk::TextTag> _warningTag;
  static Glib::RefPtr<Gtk::TextTag> _errorTag;
};


#include "Log.hxx"


#endif // LOG_HH_

#ifndef LOG_HH_
# define LOG_HH_

# include <iterator>
# include <gtkmm.h>


#include <iostream>
class Log
{
public:
  static void init(Glib::RefPtr<Gtk::Builder> builder);



  // For every severity, override its print for:
  // empty parameters, const char*, char, otherwise use std::to_string

  template<typename T>
  using EnableIfStr = std::enable_if_t<std::is_convertible_v<T, const char*, T>>;



  static void print()
  {
  }

  template<typename... Tail>
  static void constexpr print(const char head, const Tail... tail);

  template<typename... Tail>
  static void constexpr print(const char* head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void constexpr print(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void constexpr print(const T head, const Tail... tail);



  static void notice()
  {
  }

  template<typename... Tail>
  static void constexpr notice(const char head, const Tail... tail);

  template<typename... Tail>
  static void constexpr notice(const char* head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void constexpr notice(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void constexpr notice(const T head, const Tail... tail);



  static void warning()
  {
  }

  template<typename... Tail>
  static void constexpr warning(const char head, const Tail... tail);

  template<typename... Tail>
  static void constexpr warning(const char* head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void constexpr warning(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void constexpr warning(const T head, const Tail... tail);



  static void error()
  {
  }

  template<typename... Tail>
  static void constexpr error(const char head, const Tail... tail);

  template<typename... Tail>
  static void constexpr error(const char* head, const Tail... tail);

  template<typename T, typename... Tail, typename = EnableIfStr<T>>
  static void constexpr error(const T head, const Tail... tail);

  template<typename T, typename... Tail>
  static void constexpr error(const T head, const Tail... tail);




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

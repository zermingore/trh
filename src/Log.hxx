#ifndef LOG_HXX_
# define LOG_HXX_

# include <iostream>

# include "Log.hh"



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



template<typename T>
using EnableIfStr = std::enable_if_t<std::is_constructible_v<const char*, T>>;



template<typename... Tail>
void Log::print(const char head, const Tail... tail)
{
  std::cout << head;

  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert(_bufIter, str);
  print(tail...);
}

template<typename... Tail>
void Log::print(const char* head, const Tail... tail)
{
  std::cout << head;

  _bufIter = _buffer->insert(_bufIter, head);
  print(tail...);
}

template<typename... Tail>
void Log::print(const std::string& head, const Tail... tail)
{
  std::cout << head;

  _bufIter = _buffer->insert(_bufIter, head);
  print(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void Log::print(const T head, const Tail... tail)
{
  std::cout << head;

  _bufIter = _buffer->insert(_bufIter, head);
  print(tail...);
}

template<typename T, typename... Tail>
void Log::print(const T head, const Tail... tail)
{
  std::cout << head;

  _bufIter = _buffer->insert(_bufIter, std::to_string(head));
  print(tail...);
}



template<typename... Tail>
void Log::notice(const char head, const Tail... tail)
{
  std::cout << COLOR_NOTICE << head;

  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _noticeTag);
  notice(tail...);
}

template<typename... Tail>
void Log::notice(const char* head, const Tail... tail)
{
  std::cout << COLOR_NOTICE << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _noticeTag);
  notice(tail...);
}

template<typename... Tail>
void Log::notice(const std::string& head, const Tail... tail)
{
  std::cout << COLOR_NOTICE << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _noticeTag);
  notice(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void Log::notice(const T head, const Tail... tail)
{
  std::cout << COLOR_NOTICE << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _noticeTag);
  notice(tail...);
}

template<typename T, typename... Tail>
void Log::notice(const T head, const Tail... tail)
{
  std::cout << COLOR_NOTICE << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _noticeTag);
  notice(tail...);
}



template<typename... Tail>
void Log::warning(const char head, const Tail... tail)
{
  std::cerr << COLOR_WARNING << head;

  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _warningTag);
  warning(tail...);
}

template<typename... Tail>
void Log::warning(const char* head, const Tail... tail)
{
  std::cerr << COLOR_WARNING << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _warningTag);
  warning(tail...);
}

template<typename... Tail>
void Log::warning(const std::string& head, const Tail... tail)
{
  std::cerr << COLOR_WARNING << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _warningTag);
  warning(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void Log::warning(const T head, const Tail... tail)
{
  std::cerr << COLOR_WARNING << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _warningTag);
  warning(tail...);
}

template<typename T, typename... Tail>
void Log::warning(const T head, const Tail... tail)
{
  std::cerr << COLOR_WARNING << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _warningTag);
  warning(tail...);
}



template<typename... Tail>
void Log::error(const char head, const Tail... tail)
{
  std::cerr << COLOR_ERROR << head;

  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _errorTag);
  error(tail...);
}

template<typename... Tail>
void Log::error(const char* head, const Tail... tail)
{
  std::cerr << COLOR_ERROR << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _errorTag);
  error(tail...);
}

template<typename... Tail>
void Log::error(const std::string& head, const Tail... tail)
{
  std::cerr << COLOR_ERROR << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _errorTag);
  error(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void Log::error(const T head, const Tail... tail)
{
  std::cerr << COLOR_ERROR << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, head, _errorTag);
  error(tail...);
}

template<typename T, typename... Tail>
void Log::error(const T head, const Tail... tail)
{
  std::cerr << COLOR_ERROR << head;

  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _errorTag);
  error(tail...);
}



#endif // LOG_HXX_

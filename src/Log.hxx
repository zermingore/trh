#ifndef LOG_HXX_
# define LOG_HXX_

# include "Log.hh"


template<typename T>
using EnableIfStr = std::enable_if_t<std::is_convertible_v<T, const char*, T>>;



template<typename... Tail>
void constexpr Log::print(const char head, const Tail... tail)
{
  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert(_bufIter, str);
  print(tail...);
}

template<typename... Tail>
void constexpr Log::print(const char* head, const Tail... tail)
{
  _bufIter = _buffer->insert(_bufIter, head);
  print(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void constexpr Log::print(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert(_bufIter, head);
  print(tail...);
}

template<typename T, typename... Tail>
void constexpr Log::print(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert(_bufIter, std::to_string(head));
  print(tail...);
}



template<typename... Tail>
void constexpr Log::notice(const char head, const Tail... tail)
{
  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _noticeTag);
  notice(tail...);
}

template<typename... Tail>
void constexpr Log::notice(const char* head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _noticeTag);
  notice(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void constexpr Log::notice(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _noticeTag);
  notice(tail...);
}

template<typename T, typename... Tail>
void constexpr Log::notice(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _noticeTag);
  notice(tail...);
}



template<typename... Tail>
void constexpr Log::warning(const char head, const Tail... tail)
{
  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _warningTag);
  warning(tail...);
}

template<typename... Tail>
void constexpr Log::warning(const char* head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _warningTag);
  warning(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void constexpr Log::warning(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _warningTag);
  warning(tail...);
}

template<typename T, typename... Tail>
void constexpr Log::warning(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _warningTag);
  warning(tail...);
}



template<typename... Tail>
void constexpr Log::error(const char head, const Tail... tail)
{
  std::string str;
  str.assign(1, head);
  _bufIter = _buffer->insert_with_tag(_bufIter, str, _errorTag);
  error(tail...);
}

template<typename... Tail>
void constexpr Log::error(const char* head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _errorTag);
  error(tail...);
}

template<typename T, typename... Tail, typename = EnableIfStr<T>>
void constexpr Log::error(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, head, _errorTag);
  error(tail...);
}

template<typename T, typename... Tail>
void constexpr Log::error(const T head, const Tail... tail)
{
  _bufIter = _buffer->insert_with_tag(_bufIter, std::to_string(head), _errorTag);
  error(tail...);
}



#endif // LOG_HXX_

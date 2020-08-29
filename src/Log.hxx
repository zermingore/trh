#ifndef LOG_HXX_
# define LOG_HXX_

# include <iostream>

# include "Log.hh"




template<typename T, typename... Tail>
void Log::print(T head, Tail... tail)
{
  _printerAccu << head;
  print(tail...);
}



template<typename T, typename... Tail>
void Log::notice(T head, Tail... tail)
{
  _printerAccu << head;
  notice(tail...);
}



template<typename T, typename... Tail>
void Log::warning(T head, Tail... tail)
{
  _printerAccu << head;
  warning(tail...);
}



template<typename T, typename... Tail>
void Log::error(T head, Tail... tail)
{
  _printerAccu << head;
  error(tail...);
}



#endif // LOG_HXX_

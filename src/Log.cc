#include "Log.hh"



Gtk::TextView* Log::_view;
Glib::RefPtr<Gtk::TextBuffer> Log::_buffer;



void Log::init(Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("console", _view);
  _buffer = Gtk::TextBuffer::create();
  _view->set_buffer(_buffer);
}



void Log::print(const char* str)
{
  _buffer->insert_at_cursor(str);
}

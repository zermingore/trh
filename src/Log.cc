#include "Log.hh"



Gtk::TextView* Log::_view;
Glib::RefPtr<Gtk::TextBuffer> Log::_buffer;

Gtk::TextIter Log::_bufIter;
Glib::RefPtr<Gtk::TextTagTable> Log::_reftagtable;
Glib::RefPtr<Gtk::TextTag> Log::_noticeTag;
Glib::RefPtr<Gtk::TextTag> Log::_warningTag;
Glib::RefPtr<Gtk::TextTag> Log::_errorTag;

std::stringstream Log::_printerAccu;



void Log::init(Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("console", _view);

  _reftagtable = Gtk::TextBuffer::TagTable::create();

  _noticeTag = Gtk::TextBuffer::Tag::create();
  _noticeTag->property_foreground() = "blue";
  _reftagtable->add(_noticeTag);

  _warningTag = Gtk::TextBuffer::Tag::create();
  _warningTag->property_foreground() = "orange";
  _reftagtable->add(_warningTag);

  _errorTag = Gtk::TextBuffer::Tag::create();
  _errorTag->property_foreground() = "red";
  _reftagtable->add(_errorTag);

  _buffer = Gtk::TextBuffer::create(_reftagtable);
  _view->set_monospace(true);

  _view->set_buffer(_buffer);

  _bufIter = _buffer->get_iter_at_offset(0);
}




void Log::print()
{
  std::cout << _printerAccu.str() << COLOR_NORMAL;
  _bufIter = _buffer->insert(_bufIter, _printerAccu.str().c_str());

  _printerAccu.str(std::string());
  _printerAccu.clear();
}


void Log::notice()
{
  std::cout << COLOR_NOTICE << _printerAccu.str() << COLOR_NORMAL;
  _bufIter = _buffer->insert_with_tag(_bufIter, _printerAccu.str().c_str(), _noticeTag);

  _printerAccu.str(std::string());
  _printerAccu.clear();
}


void Log::warning()
{
  std::cerr << COLOR_WARNING << _printerAccu.str() << COLOR_NORMAL;
  _bufIter = _buffer->insert_with_tag(_bufIter, _printerAccu.str().c_str(), _warningTag);

  _printerAccu.str(std::string());
  _printerAccu.clear();
}


void Log::error()
{
  std::cerr << COLOR_ERROR << _printerAccu.str()  << COLOR_NORMAL;
  _bufIter = _buffer->insert_with_tag(_bufIter, _printerAccu.str().c_str(), _errorTag);

  _printerAccu.str(std::string());
  _printerAccu.clear();
}

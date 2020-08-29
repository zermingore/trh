#include "Log.hh"



Gtk::TextView* Log::_view;
Glib::RefPtr<Gtk::TextBuffer> Log::_buffer;

Gtk::TextIter Log::_bufIter;
Glib::RefPtr<Gtk::TextTagTable> Log::_reftagtable;
Glib::RefPtr<Gtk::TextTag> Log::_noticeTag;
Glib::RefPtr<Gtk::TextTag> Log::_warningTag;
Glib::RefPtr<Gtk::TextTag> Log::_errorTag;



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

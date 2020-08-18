#ifndef GRAMMAR_HH_
# define GRAMMAR_HH_

# include <gtkmm.h>



class Grammar
{
public:
  explicit Grammar(Glib::RefPtr<Gtk::Builder> builder);
  ~Grammar() = default;

private:
  const Glib::RefPtr<Gtk::Builder> _builder;
};


# endif /* GRAMMAR_HH_ */

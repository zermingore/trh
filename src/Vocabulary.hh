#ifndef VOCABULARY_HH_
# define VOCABULARY_HH_

# include <vector>
# include <string>

# include <gtkmm.h>



namespace Gtk
{
  class RadioButton;
}


class Vocabulary
{
public:
    explicit Vocabulary(Glib::RefPtr<Gtk::Builder> builder);


private:
  void cbOnSearch();
  void cbEditWord();
  void cbOnAdd();
  void cbOnConfirmAddWord();
  void cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection);


  Glib::RefPtr<Gtk::Builder> _builder;

  std::vector<Gtk::RadioButton*> _buttonsCategories; ///< Radio buttons list

  const std::vector<std::string> _categories;
  const std::vector<std::string> _languages;


  bool _addWordDisplayed = false;
  Gtk::Box *_boxAddWord;
  int _addWordSelectedCategory = 0;
  int _addWordSelectedLanguage = 0;
};


#endif /* VOCABULARY_HH_ */

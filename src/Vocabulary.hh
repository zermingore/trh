#ifndef VOCABULARY_HH_
# define VOCABULARY_HH_

# include <vector>
# include <string>

# include <gtkmm.h>



namespace Gtk
{
  class RadioButton;
}


struct Word
{
  unsigned int id;
  short language;
  short category;
  Glib::ustring name;
};


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


  const Glib::RefPtr<Gtk::Builder> _builder;

  std::vector<Gtk::RadioButton*> _buttonsCategories; ///< Radio buttons list
  std::vector<Gtk::RadioButton*> _buttonsLanguages; ///< Radio buttons list

  const std::vector<std::string> _categories;
  const std::vector<std::string> _languages;


  bool _editMode = false;
  bool _addWordDisplayed = false;
  Gtk::Box *_boxAddWord;
  Word _selectedWord;
};


#endif /* VOCABULARY_HH_ */

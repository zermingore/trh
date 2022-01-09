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


enum e_sort_method: uint8_t
{
  ALPHA = 0,
  NEWEST,

  NB_SORT_METHODS
};



class Vocabulary
{
public:
    explicit Vocabulary(Glib::RefPtr<Gtk::Builder> builder);


private:
  void cbOnSearch(const Glib::ustring string);
  void cbEditWord();
  void cbOnAdd();
  void cbOnConfirmAddWord();
  void cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection);
  void cbOnSortWords();
  void cbOnUserWords();
  void cbSwitchLanguage();


  const Glib::RefPtr<Gtk::Builder> _builder;

  std::vector<Gtk::RadioButton*> _buttonsCategories; ///< Radio buttons list
  std::vector<Gtk::RadioButton*> _buttonsLanguages; ///< Radio buttons list

  const std::vector<std::string> _categories;
  const std::vector<std::string> _languages;

  Gtk::SearchEntry* _search; ///< Keeping in the class to access the string

  bool _editMode = false;
  bool _addWordDisplayed = false;
  bool _userShownOnly = false;
  size_t _currentLanguage = 0;
  Gtk::Box *_boxAddWord;
  Word _selectedWord;

  uint8_t _sortMethod = e_sort_method::ALPHA;


  Gtk::TextView* _view;
  Glib::RefPtr<Gtk::TextBuffer> _buffer;
  Gtk::TextIter _bufIter;
};


#endif /* VOCABULARY_HH_ */

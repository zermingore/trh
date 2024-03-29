#include "Vocabulary.hh"

#include <iostream>

#include <gtkmm.h>

#include <DB.hh>
#include <db_tables.hh>
#include <Log.hh>



Vocabulary::Vocabulary(Glib::RefPtr<Gtk::Builder> builder)
  : _builder(builder)
  , _categories(DB::getTableEntries("categories"))
  , _languages(DB::getTableEntries("languages"))
{
  _builder->get_widget("boxAddWord", _boxAddWord);

  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);
  vocabularyList->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = vocabularyList->get_selection();
  refTreeSelection->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &Vocabulary::cbOnSelectionChanged), refTreeSelection));

  DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get());

  vocabularyList->append_column("Name", tableColumnsWords.name);

  _builder->get_widget("search", _search);
  _search->signal_search_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &Vocabulary::cbOnSearch), _search->get_text()));

  Gtk::Button* addButton;
  _builder->get_widget("add", addButton);
  addButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnAdd));

  Gtk::Button* sortButton;
  _builder->get_widget("sort", sortButton);
  sortButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnSortWords));

  Gtk::Button* userButton;
  _builder->get_widget("user", userButton);
  userButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnUserWords));

  Gtk::Button* editButton;
  _builder->get_widget("edit", editButton);
  editButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbEditWord));

  Gtk::TreeView* list;
  _builder->get_widget("vocabularyList", list);
  auto row = Gtk::make_managed<Gtk::Button>("word");


  _buffer = Gtk::TextBuffer::create();
  builder->get_widget("translations", _view);
  _view->set_monospace(true);
  _view->set_buffer(_buffer);
  _bufIter = _buffer->get_iter_at_offset(0);


  row->show();
  list->add(*row);


  Gtk::Button* confirmAddWord;
  _builder->get_widget("confirmAddWordButton", confirmAddWord);
  confirmAddWord->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnConfirmAddWord));

  Gtk::ButtonBox *boxCategories = nullptr;
  _builder->get_widget("addWordButtonBoxCategory", boxCategories);

  Gtk::RadioButton::Group groupCategories;

  int i = 1; // DB index starts at 1
  for (const auto &category: _categories)
  {
    auto button = Gtk::make_managed<Gtk::RadioButton> (groupCategories, category);
    boxCategories->pack_start(*button);
    button->signal_clicked().connect([=] () {
      _selectedWord.category = i;
    });
    _buttonsCategories.emplace_back(button);

    ++i;
  }

  Gtk::ButtonBox *boxLanguages = nullptr;
  _builder->get_widget("addWordButtonBoxLanguages", boxLanguages);

  Gtk::RadioButton::Group groupLanguages;
  i = 1; // DB index starts at 1
  for (const auto &language: _languages)
  {
    auto button = Gtk::make_managed<Gtk::RadioButton> (groupLanguages, language);
    boxLanguages->pack_end(*button);
    button->signal_clicked().connect([=] () { _selectedWord.language = i; });
    _buttonsLanguages.emplace_back(button);
    ++i;
  }

  Gtk::Button* languageButton;
  _builder->get_widget("language", languageButton);
  languageButton->set_label(_languages[0]);
  languageButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbSwitchLanguage));

  _addWordDisplayed = false;
  _editMode = false;
  _boxAddWord->hide();
}



void Vocabulary::cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection)
{
  _addWordDisplayed = false;
  _editMode = false;
  _boxAddWord->hide();

  Log::print("selectionChanged\n");

  Gtk::TreeModel::iterator iter = selection->get_selected();
  if (iter)
  {
    Gtk::TreeModel::Row row = *iter;
    DbTableColumnsWords tableCol;

    DbTableColumnsTranslations tableTranslation;
    Glib::RefPtr<Gtk::ListStore> store = Gtk::ListStore::create(tableTranslation);
    DB::getTranslations(row[tableCol.id], DB::fetchTranslations, (void *) store.get());
    _selectedWord.id = row[tableCol.id];

    for (auto& child: store->children())
    {
      Gtk::TreeModel::Row row_translations = child;
      DbTableColumnsWords word;
      Glib::RefPtr<Gtk::ListStore> list_words = Gtk::ListStore::create(word);
      DB::getWord(row_translations[tableTranslation.id_word_dst], (void*) list_words.get());

      for (auto c: list_words->children())
      {
        row[tableCol.name] = static_cast<Glib::ustring> (c[word.name]);
        std::stringstream sstr;
        sstr << _languages[c[word.language] - 1] << ": " << c[word.name] << "\n";
        _bufIter = _buffer->insert(_bufIter, sstr.str().c_str());
      }
    }
  }
}



void Vocabulary::cbOnConfirmAddWord()
{
  Gtk::Entry *entryName = nullptr;
  _builder->get_widget("addWordName", entryName);

  if (_editMode)
  {
    Log::print("id: ", _selectedWord.id, '\n',
               "name: ", _selectedWord.name, '\n',
               "language: ", _selectedWord.language, '\n',
               "category: ", _selectedWord.category, '\n');

    DB::editWord(_selectedWord.id, entryName->get_text(), _selectedWord.language, _selectedWord.category);
  }
  else
  {
    DB::addWord(entryName->get_text(), _selectedWord.language, _selectedWord.category);
  }

  // Refresh the vocabulary list
  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get());
}



void Vocabulary::cbOnSearch(const Glib::ustring string)
{
  auto content{_search->get_text()};
  Log::print("search clicked ");
  Log::print(string + _search->get_text());

  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get(), _search->get_text());
}



void Vocabulary::cbEditWord()
{
  Log::print("\n--- cbEditWord... ");

  // Reset selected word (with error values)
  _selectedWord.category = 0;
  _selectedWord.language = 0;
  _selectedWord.name = "";

  _addWordDisplayed = !_addWordDisplayed;
  if (!_addWordDisplayed)
  {
    Log::print("OFF\n");
    _boxAddWord->hide();
    return;
  }
  _boxAddWord->show();
  Log::print("ON\n");

  DbTableColumnsWords dbWord;
  Glib::RefPtr<Gtk::ListStore> list_words = Gtk::ListStore::create(dbWord);
  DB::getWord(_selectedWord.id, (void*) list_words.get());


  for (auto c: list_words->children())
  {
    _selectedWord.name = static_cast<Glib::ustring> (c[dbWord.name]);
    _selectedWord.category = static_cast<int> (c[dbWord.category]);
    _selectedWord.language = static_cast<int> (c[dbWord.language]);
  }

  if (   _selectedWord.name == ""
      || _selectedWord.category <= 0
      || _selectedWord.language <= 0)
  {
    Log::warning(  "Unable to locate word\n"
                 , "id:       ", _selectedWord.id, "\n"
                 , "category: ", _selectedWord.category, "\n"
                 , "language: ", _selectedWord.language, "\n"
                 , "name:     ", _selectedWord.name, "\n\n");
    return;
  }

  Log::print(  "activating...\n"
             , "id:       ", _selectedWord.id, "\n"
             , "category: ", _selectedWord.category, "\n"
             , "language: ", _selectedWord.language, "\n"
             , "name:     ", _selectedWord.name, "\n\n");

  Gtk::Entry *entryName = nullptr;
  _builder->get_widget("addWordName", entryName);
  entryName->set_text(_selectedWord.name);

  Gtk::ButtonBox *boxCategories = nullptr;
  _builder->get_widget("addWordButtonBoxCategory", boxCategories);

  // -1: db index Vs vector index
  _buttonsCategories[_selectedWord.category - 1]->set_active(true);
  _buttonsLanguages[_selectedWord.language - 1]->set_active(true);

  _editMode = true;
  _boxAddWord->show();
}



void Vocabulary::cbOnAdd()
{
  _addWordDisplayed = !_addWordDisplayed;

  // Reset selection
  _buttonsCategories[0]->set_active(true);
  _buttonsLanguages[0]->set_active(true);
  Gtk::Entry *entryName = nullptr;
  _builder->get_widget("addWordName", entryName);
  entryName->set_text("");

  if (_addWordDisplayed)
  {
    _boxAddWord->show();
    return;
  }
  _boxAddWord->hide();
}



void Vocabulary::cbOnSortWords()
{
  _sortMethod = (_sortMethod + 1) % static_cast<uint8_t> (e_sort_method::NB_SORT_METHODS);

  Gtk::Entry *entryName = nullptr;
  _builder->get_widget("addWordName", entryName);

  // Refresh the vocabulary list
  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  switch (_sortMethod)
  {
    case e_sort_method::ALPHA:
      DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get());
      break;

    case e_sort_method::NEWEST:
      DB::getWordsLanguageSortedInsertionDate(_currentLanguage + 1, (void*) treeModel.get());
      break;

    default:
      Log::error("Invalid sorting method", static_cast<uint8_t> (_sortMethod));
      break;
  }
}



void Vocabulary::cbOnUserWords()
{
  _userShownOnly = !_userShownOnly;

  // Refresh the vocabulary list
  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  if (_userShownOnly)
  {
    DB::getWordsUser((void*) treeModel.get());
  }
  else
  {
    DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get());
  }
}



void Vocabulary::cbSwitchLanguage()
{
  _currentLanguage = (_currentLanguage + 1) % _languages.size();

  // Refresh the vocabulary list
  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  Gtk::Button* languageButton;
  _builder->get_widget("language", languageButton);
  languageButton->set_label(_languages[_currentLanguage]);

  DB::getWordsLanguageSortedName(_currentLanguage + 1, (void*) treeModel.get());
}

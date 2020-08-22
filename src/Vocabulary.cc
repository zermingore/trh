#include "Vocabulary.hh"

#include <iostream>

#include <gtkmm.h>

#include <DB.hh>
#include <db_tables.hh>



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

  DB::getWordsLanguageSorted(2, (void*) treeModel.get());

  vocabularyList->append_column("Name", tableColumnsWords.name);


  Gtk::Button* searchButton;
  _builder->get_widget("search", searchButton);
  searchButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnSearch));

  Gtk::Button* addButton;
  _builder->get_widget("add", addButton);
  addButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbOnAdd));

  Gtk::Button* editButton;
  _builder->get_widget("edit", editButton);
  editButton->signal_clicked().connect(sigc::mem_fun(*this, &Vocabulary::cbEditWord));


  Gtk::TreeView* list;
  _builder->get_widget("vocabularyList", list);
  auto row = Gtk::make_managed<Gtk::Button>("word");


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
    button->signal_clicked().connect([=] () { _addWordSelectedCategory = i; });
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
    button->signal_clicked().connect([=] () { _addWordSelectedLanguage = i; });
    ++i;
  }

  _boxAddWord->hide();
}



void Vocabulary::cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection)
{
  _addWordDisplayed = false;
  _editMode = false;
  _boxAddWord->hide();

  Gtk::TreeModel::iterator iter = selection->get_selected();
  if (iter)
  {
    Gtk::TreeModel::Row row = *iter;
    DbTableColumnsWords tableCol;

    DbTableColumnsTranslations tableTranslation;
    Glib::RefPtr<Gtk::ListStore> store = Gtk::ListStore::create(tableTranslation);
    DB::getTranslations(row[tableCol.id], DB::fetchTranslations, (void *) store.get());
    _selectedWordIndex = row[tableCol.id];

    for (auto& child: store->children())
    {
      Gtk::TreeModel::Row row_translations = child;
      DbTableColumnsWords word;
      Glib::RefPtr<Gtk::ListStore> list_words = Gtk::ListStore::create(word);
      DB::getWord(row_translations[tableTranslation.id_word_dst], (void*) list_words.get());

      for (auto c: list_words->children())
      {
        row[tableCol.name] = static_cast<Glib::ustring> (c[word.name]);
      }
    }
  }
}



void Vocabulary::cbOnConfirmAddWord()
{
  if (_editMode)
  {
    return;
  }

  Gtk::Entry *entryName = nullptr;
  _builder->get_widget("addWordName", entryName);
  DB::addWord(entryName->get_text(), _addWordSelectedLanguage, _addWordSelectedCategory);

  DbTableColumnsWords tableColumnsWords;

  // Refresh the vocabulary list
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = vocabularyList->get_selection();
  refTreeSelection->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &Vocabulary::cbOnSelectionChanged), refTreeSelection));

  DB::getWordsLanguageSorted(2, (void*) treeModel.get());
}



void Vocabulary::cbOnSearch()
{
  std::cout << "search clicked" << std::endl;
}



void Vocabulary::cbEditWord()
{
  std::cout << "--- cbEditWord ---\n";

  _addWordDisplayed = !_addWordDisplayed;
  if (!_addWordDisplayed)
  {
    _boxAddWord->hide();
    return;
  }

  DbTableColumnsWords word;
  Glib::RefPtr<Gtk::ListStore> list_words = Gtk::ListStore::create(word);
  DB::getWord(_selectedWordIndex, (void*) list_words.get());

  std::cout << "Checking children of " << _selectedWordIndex << '\n';
  for (auto c: list_words->children())
  {
    // auto name = static_cast<Glib::ustring> (c[word.name]);
    std::cout << "id: " << c[word.id] << '\n';
    std::cout << "name: " << c[word.name] << '\n';
    std::cout << "language: " << c[word.language] << '\n';
    std::cout << "category: " << c[word.category] << '\n';
  }

  Gtk::RadioButton::Group groupCategories;

  auto button = Gtk::make_managed<Gtk::RadioButton> (groupCategories, "adverb");
  button->set_active(true);

  _boxAddWord->show();
}



void Vocabulary::cbOnAdd()
{
  _addWordDisplayed = !_addWordDisplayed;
  if (_addWordDisplayed)
  {
    _boxAddWord->show();
    return;
  }
  _boxAddWord->hide();
}

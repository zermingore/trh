#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>
#include <db_tables.hh>



MainWindow::MainWindow()
{
  initializeBuilder();
  initializeWidgets();
  show_all_children();
}



void MainWindow::cbOnSelectionChanged(Glib::RefPtr<Gtk::TreeSelection> selection)
{
  Gtk::TreeModel::iterator iter = selection->get_selected();
  if (iter)
  {
    Gtk::TreeModel::Row row = *iter;
    DbTableColumnsWords tableCol;

    DbTableColumnsTranslations tableTranslation;
    Glib::RefPtr<Gtk::ListStore> store = Gtk::ListStore::create(tableTranslation);
    DB::getTranslations(row[tableCol.id], DB::fetchTranslations, (void *) store.get());

    for (auto& child: store->children())
    {
      Gtk::TreeModel::Row row_translations = child;
      DbTableColumnsWords word;
      Glib::RefPtr<Gtk::ListStore> list_words = Gtk::ListStore::create(word);
      DB::getWord(row_translations[tableTranslation.id_word_dst], (void*) list_words.get());

      Gtk::TreeModel::Row row_word = child;
      for (auto c: list_words->children())
      {
        Gtk::TreeModel::Row row_word = c;
        Glib::ustring tmp = row_word[word.name];
        row[tableCol.name] = tmp;
      }
    }
  }
}



void MainWindow::cbOnSearch()
{
  std::cout << "search clicked" << std::endl;
}



void MainWindow::cbOnAdd()
{
  std::cout << "add clicked" << std::endl;
}



void MainWindow::initializeBuilder()
{
  _builder = Gtk::Builder::create();

  try
  {
    _builder->add_from_file("ui_main.xml");
  }
  catch (const Glib::FileError& e)
  {
    std::cerr << "GtkBuilder FileError: " << e.what() << '\n';
    throw e;
  }
  catch (const Glib::MarkupError& e)
  {
    std::cerr << "GtkBuilder MarkupError: " << e.what() << '\n';
    throw e;
  }
  catch (const Gtk::BuilderError& e)
  {
    std::cerr << "GtkBuilder BuilderError: " << e.what() << '\n';
    throw e;
  }
}



void MainWindow::initializeWidgets()
{
  Gtk::Box *box = nullptr;
  _builder->get_widget("box", box);
  add(*box);

  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  _builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);
  vocabularyList->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = vocabularyList->get_selection();
  refTreeSelection->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::cbOnSelectionChanged), refTreeSelection));

  DB::getWordsLanguageSorted(2, (void*) treeModel.get());

  vocabularyList->append_column("Name", tableColumnsWords.name);


  DbTableGrammarRules tableGrammarRules;
  Gtk::TreeView* grammarRulesTitles = nullptr;
  _builder->get_widget("grammarRulesTitles", grammarRulesTitles);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammar = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesTitles->set_model(treeModelGrammar);
  grammarRulesTitles->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammar = grammarRulesTitles->get_selection();
  refTreeSelectionGrammar->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::cbOnSelectionChanged), refTreeSelectionGrammar));

  DB::getGrammarRulesTitles((void*) treeModelGrammar.get());
  grammarRulesTitles->append_column("title", tableGrammarRules.title);



  Gtk::TreeView* grammarRulesContent = nullptr;
  _builder->get_widget("grammarRulesContent", grammarRulesContent);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammarContent = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesContent->set_model(treeModelGrammarContent);
  grammarRulesContent->set_headers_visible(false);
  grammarRulesContent->get_selection()->set_mode(Gtk::SELECTION_NONE);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammarContent = grammarRulesContent->get_selection();
  refTreeSelectionGrammarContent->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::cbOnSelectionChanged), refTreeSelectionGrammarContent));

  DB::getGrammarRulesTitles((void*) treeModelGrammarContent.get());
  grammarRulesContent->append_column("content", tableGrammarRules.content);



  DbViewGrammarExampleNames dbViewNames;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel = Gtk::ListStore::create(dbViewNames);

  Gtk::TreeView* grammarExamplesView;
  _builder->get_widget("grammarExamples", grammarExamplesView);

  grammarExamplesView->set_model(m_refTreeModel);
  grammarExamplesView->set_headers_visible(false);
  grammarExamplesView->get_selection()->set_mode(Gtk::SELECTION_NONE);

  DB::getGrammarExamples(1, (void*) m_refTreeModel.get());
  grammarExamplesView->append_column("name", dbViewNames.name);


  Gtk::Button* searchButton;
  _builder->get_widget("search", searchButton);
  searchButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::cbOnSearch));

  Gtk::Button* addButton;
  _builder->get_widget("add", addButton);
  addButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::cbOnAdd));


  Gtk::TreeView* list;
  _builder->get_widget("vocabularyList", list);
  auto row = Gtk::make_managed<Gtk::Button>("word");


  row->show();
  list->add(*row);
}

#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>
#include <db_tables.hh>



void MainWindow::on_selection_changed(Glib::RefPtr<Gtk::TreeSelection> selection)
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



MainWindow::MainWindow()
{
  auto builder = Gtk::Builder::create();
  try
  {
    builder->add_from_file("ui_main.xml");
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

  Gtk::Box *box = nullptr;
  builder->get_widget("box", box);
  add(*box);

  DbTableColumnsWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);
  vocabularyList->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = vocabularyList->get_selection();
  refTreeSelection->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::on_selection_changed), refTreeSelection));

  DB::getWordsLanguageSorted(2, (void*) treeModel.get());

  vocabularyList->append_column("Name", tableColumnsWords.name);



  DbTableGrammarRules tableGrammarRules;
  Gtk::TreeView* grammarRulesTitle = nullptr;
  builder->get_widget("grammarRulesTitle", grammarRulesTitle);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammar = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesTitle->set_model(treeModelGrammar);
  grammarRulesTitle->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammar = grammarRulesTitle->get_selection();
  refTreeSelectionGrammar->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::on_selection_changed), refTreeSelectionGrammar));

  DB::getGrammarRulesTitles((void*) treeModelGrammar.get());
  grammarRulesTitle->append_column("title", tableGrammarRules.title);



  Gtk::TreeView* grammarRulesContent = nullptr;
  builder->get_widget("grammarRulesContent", grammarRulesContent);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammar2 = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesContent->set_model(treeModelGrammar2);
  grammarRulesContent->set_headers_visible(false);

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammar2 = grammarRulesContent->get_selection();
  refTreeSelectionGrammar2->signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &MainWindow::on_selection_changed), refTreeSelectionGrammar2));

  DB::getGrammarRulesTitles((void*) treeModelGrammar2.get());
  grammarRulesContent->append_column("content", tableGrammarRules.content);

  show_all_children();
}

#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>
#include <db_tables.hh>
#include <Vocabulary.hh>



MainWindow::MainWindow()
{
  initializeBuilder();
  initializeWidgets();
  show_all_children();
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
    throw;
  }
  catch (const Glib::MarkupError& e)
  {
    std::cerr << "GtkBuilder MarkupError: " << e.what() << '\n';
    throw;
  }
  catch (const Gtk::BuilderError& e)
  {
    std::cerr << "GtkBuilder BuilderError: " << e.what() << '\n';
    throw;
  }
}



void MainWindow::initializeWidgets()
{
  Gtk::Box *box = nullptr;
  _builder->get_widget("box", box);
  add(*box);


  DbTableGrammarRules tableGrammarRules;
  Gtk::TreeView* grammarRulesTitles = nullptr;
  _builder->get_widget("grammarRulesTitles", grammarRulesTitles);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammar = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesTitles->set_model(treeModelGrammar);
  grammarRulesTitles->set_headers_visible(false);

  // Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammar = grammarRulesTitles->get_selection();
  // refTreeSelectionGrammar->signal_changed().connect(
  //   sigc::bind(sigc::mem_fun(*this, &MainWindow::cbOnSelectionChanged), refTreeSelectionGrammar));

  DB::getGrammarRulesTitles((void*) treeModelGrammar.get());
  grammarRulesTitles->append_column("title", tableGrammarRules.title);



  Gtk::TreeView* grammarRulesContent = nullptr;
  _builder->get_widget("grammarRulesContent", grammarRulesContent);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammarContent = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesContent->set_model(treeModelGrammarContent);
  grammarRulesContent->set_headers_visible(false);
  grammarRulesContent->get_selection()->set_mode(Gtk::SELECTION_NONE);

  // Glib::RefPtr<Gtk::TreeSelection> refTreeSelectionGrammarContent = grammarRulesContent->get_selection();
  // refTreeSelectionGrammarContent->signal_changed().connect(
  //   sigc::bind(sigc::mem_fun(*this, &MainWindow::cbOnSelectionChanged), refTreeSelectionGrammarContent));

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



  _vocabulary = std::make_unique<Vocabulary> (_builder);
}

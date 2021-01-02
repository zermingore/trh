#include <Grammar.hh>

#include <gtkmm.h>

#include <DB.hh>
#include <db_tables.hh>



Grammar::Grammar(Glib::RefPtr<Gtk::Builder> builder)
  : _builder(builder)
{
  DbTableGrammarRules tableGrammarRules;
  Gtk::TreeView* grammarRulesTitles = nullptr;
  _builder->get_widget("grammarRulesTitles", grammarRulesTitles);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammar = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesTitles->set_model(treeModelGrammar);
  grammarRulesTitles->set_headers_visible(false);

  DB::getGrammarRulesTitles((void*) treeModelGrammar.get());
  grammarRulesTitles->append_column("title", tableGrammarRules.title);



  Gtk::TreeView* grammarRulesContent = nullptr;
  _builder->get_widget("grammarRulesContent", grammarRulesContent);
  Glib::RefPtr<Gtk::ListStore> treeModelGrammarContent = Gtk::ListStore::create(tableGrammarRules);
  grammarRulesContent->set_model(treeModelGrammarContent);
  grammarRulesContent->set_headers_visible(false);
  grammarRulesContent->get_selection()->set_mode(Gtk::SELECTION_NONE);

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
}
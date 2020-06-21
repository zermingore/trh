#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>



int dbFetchWords(void *model, int argc, char **argv, char **azColName)
{
  Gtk::ListStore *refTreeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(refTreeModel->append());
  DbTableWords table_col;
  row[table_col._id] = std::stoi(argv[0]);
  row[table_col._language] = std::stoi(argv[1]);
  row[table_col._category] = std::stoi(argv[2]);
  row[table_col._name] = argv[3];

  return 0;
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

  Gtk::TreeView* vocabularyList = nullptr;
  builder->get_widget("vocabularyList", vocabularyList);

  // Create the Tree model
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel = Gtk::ListStore::create(m_Columns);
  vocabularyList->set_model(m_refTreeModel);
  vocabularyList->set_headers_visible(false);

  DB::initialize("db.sql");
  DB::getWordsSorted(dbFetchWords, (void*) (m_refTreeModel.get()));
  DB::close();

  vocabularyList->append_column("Name", m_Columns._name);

  show_all_children();
}

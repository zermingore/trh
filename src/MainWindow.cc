#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

#include <MainWindow.hh>
#include <DB.hh>



int dbFetchWords(void *model, int argc, char **argv, char **azColName)
{
  Gtk::ListStore *treeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(treeModel->append());
  DbTableWords tableCol;
  row[tableCol.id] = std::stoi(argv[0]);
  row[tableCol.language] = std::stoi(argv[1]);
  row[tableCol.category] = std::stoi(argv[2]);
  row[tableCol.name] = argv[3];

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

  DbTableWords tableColumnsWords;
  Gtk::TreeView* vocabularyList = nullptr;
  builder->get_widget("vocabularyList", vocabularyList);
  Glib::RefPtr<Gtk::ListStore> treeModel = Gtk::ListStore::create(tableColumnsWords);
  vocabularyList->set_model(treeModel);
  vocabularyList->set_headers_visible(false);

  DB::initialize("db.sql");
  DB::getWordsSorted(dbFetchWords, (void*) treeModel.get());
  DB::close();

  vocabularyList->append_column("Name", tableColumnsWords.name);

  show_all_children();
}

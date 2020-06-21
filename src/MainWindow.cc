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
    std::cout << "selected: " << row[tableCol.name] << std::endl;
    row[tableCol.name] = "lol";

    DbTableColumnsTranslations tableTranslation;
    Glib::RefPtr<Gtk::ListStore> store = Gtk::ListStore::create(tableTranslation);
    DB::getTranslations(row[tableCol.id], DB::fetchTranslations, (void *) store.get());
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

  DB::getWordsSorted(DB::dbFetchWords, (void*) treeModel.get());

  vocabularyList->append_column("Name", tableColumnsWords.name);

  show_all_children();
}

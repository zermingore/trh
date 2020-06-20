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
  : m_VBox(Gtk::ORIENTATION_VERTICAL)
{
  set_title("Gtk::TreeView (ListStore) example");
  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);
  m_TreeView.set_headers_visible(false);



  // GtkListStore *store = gtk_list_store_new(
  //   (int) e_db_words_col::NB_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  DB::initialize("db.sql");
  DB::getWordsSorted(dbFetchWords, (void*) (m_refTreeModel.get()));
  DB::close();

  // auto builder = Gtk::Builder::create();
  // try
  // {
  //   builder->add_from_file("ui_main.xml");
  // }
  // catch (const Glib::FileError& e)
  // {
  //   std::cerr << "GtkBuilder FileError: " << e.what() << '\n';
  //   throw e;
  // }
  // catch (const Glib::MarkupError& e)
  // {
  //   std::cerr << "GtkBuilder MarkupError: " << e.what() << '\n';
  //   throw e;
  // }
  // catch (const Gtk::BuilderError& e)
  // {
  //   std::cerr << "GtkBuilder BuilderError: " << e.what() << '\n';
  //   throw e;
  // }

  // Gtk::Stack* stack;
  // builder->get_widget("stack", stack);
  // if (!stack)
  //   throw std::runtime_error("No [stack] object in window.ui\n");

  // Gtk::TreeView *vocabularyList;
  // builder->get_widget("vocabularyList", vocabularyList);

  // GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  // GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
  //   "language", renderer, "text", 1, NULL);
  // //gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);
  // vocabularyList->append_column(column);

  // renderer = gtk_cell_renderer_text_new();
  // column = gtk_tree_view_column_new_with_attributes("category", renderer, "text", 2, NULL);
  // gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

  // renderer = gtk_cell_renderer_text_new();
  // column = gtk_tree_view_column_new_with_attributes("name", renderer, "text", 3, NULL);
  // gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

  // gtk_tree_view_set_model(GTK_TREE_VIEW(vocabularyList), GTK_TREE_MODEL(store));
  // g_object_unref(store);
  // gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vocabularyList), TRUE);


  //Add the TreeView's view columns:
  //This number will be shown with the default numeric formatting.
  m_TreeView.append_column("Name", m_Columns._name);

  show_all_children();
}

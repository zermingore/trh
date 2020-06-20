#include <iostream>
#include <stdexcept>

#include <gtkmm.h>
#include <gtkmm.h>

#include <iostream>
#include <memory>

#include <gtk/gtk.h>
#include <gtkmm.h>
#include <gtkmm/application.h>

extern "C" {
# include <lib/sqlite3.h>
}


#include <UI.hh>
#include <MainWindow.hh>




enum class e_db_words_col {
  ID,
  LANGUAGE,
  CATEGORY,
  NAME,
  NB_COLUMNS
};


int callback(void *, int, char **, char **);



static void vocabulary_cb(GtkWidget */* unused */, gpointer /* unused */)
{
  GtkBuilder *builder = gtk_builder_new();
  GError *error = NULL;
  if (!gtk_builder_add_from_file(builder, "ui_vocabulary.xml", &error)) // 0 on error
  {
    g_printerr("Error loading UI file: %s\n", error->message);
    g_clear_error(&error);
  }
}



int callback(void *model, int argc, char **argv, char **azColName)
{
  GtkTreeIter iter;
  gtk_list_store_append(GTK_LIST_STORE(model), &iter);
  gtk_list_store_set(GTK_LIST_STORE(model), &iter,
                     e_db_words_col::ID, argv[0],
                     e_db_words_col::LANGUAGE, argv[1],
                     e_db_words_col::CATEGORY, argv[2],
                     e_db_words_col::NAME, argv[3],
                     -1);

   return 0;
}




UI::UI(int argc, char *argv[])
{
  _app = Gtk::Application::create(argc, argv, "com.nulmail.trh");

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

  builder->get_widget_derived("window", _window);



  g_signal_connect(G_OBJECT(_window), "destroy", gtk_main_quit, NULL);

  Gtk::Stack *stack;
  builder->get_widget("stack", stack);

  Gtk::StackSwitcher *switcher;
  builder->get_widget("switcher", switcher);

  Gtk::Widget *vocabularyView;
  builder->get_widget("vocabularyView", vocabularyView);
  // gtk_stack_set_visible_child(stack, vocabularyView);


  GtkListStore *store = gtk_list_store_new(
    (int) e_db_words_col::NB_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  sqlite3 *db;
  if (sqlite3_open("db.sql", &db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(db) << '\n';
    return;
  }
  std::cout << "DB OPENED\n";

  const char *request = "SELECT * FROM words ORDER BY name ASC";
  char *err_msg = 0;
  int rc = sqlite3_exec(db, request, callback, store, &err_msg);
  if (rc != SQLITE_OK )
  {
    std::cerr << "Error selecting DB data:\n\t" << err_msg << '\n';
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return;
  }
  sqlite3_close(db);

  Gtk::Widget *vocabularyList;
  builder->get_widget("vocabularyList", vocabularyList);

  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
    "language", renderer, "text", 1, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("category", renderer, "text", 2, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("name", renderer, "text", 3, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

  gtk_tree_view_set_model(GTK_TREE_VIEW(vocabularyList), GTK_TREE_MODEL(store));
  g_object_unref(store);
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vocabularyList), TRUE);
}



int UI::run()
{
  auto r = _app->run(*_window);
  delete _window;

  return r;
}

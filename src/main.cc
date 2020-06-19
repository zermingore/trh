#include <iostream>

#include <gtk/gtk.h>

extern "C" {
#include <lib/sqlite3.h>
}


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



int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkBuilder *builder = gtk_builder_new();
  GError *error = NULL;
  if (!gtk_builder_add_from_file(builder, "ui_main.xml", &error)) // 0 on error
  {
    g_printerr("Error loading UI file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  GtkWidget *window = (GtkWidget*) gtk_builder_get_object(builder, "window");
  g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);

  GtkStack *stack = (GtkStack*) gtk_builder_get_object(builder, "stack");
  GtkStackSwitcher *switcher = (GtkStackSwitcher*) gtk_builder_get_object(builder, "switcher");

  gtk_widget_set_halign(GTK_WIDGET(switcher), GTK_ALIGN_CENTER);

  GtkWidget *vocabularyView = (GtkWidget*) gtk_builder_get_object(builder, "vocabularyView");
  gtk_stack_set_visible_child(stack, vocabularyView);


  GtkListStore *store = gtk_list_store_new(
    (int) e_db_words_col::NB_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  sqlite3 *db;
  if (sqlite3_open("db.sql", &db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(db) << '\n';
    return 1;
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
    return 1;
  }
  sqlite3_close(db);

  GtkWidget *list = (GtkWidget*) gtk_builder_get_object(builder, "list");
  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
    "language", renderer, "text", 1, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("category", renderer, "text", 2, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("name", renderer, "text", 3, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
  g_object_unref(store);
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);


  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

#include <iostream>

#include <gtk/gtk.h>

extern "C" {
#include <lib/sqlite3.h>
}



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

  GObject *vocabulary = gtk_builder_get_object(builder, "vocabulary");
  g_signal_connect(vocabulary, "clicked", G_CALLBACK(vocabulary_cb), NULL);

  gtk_main();


  sqlite3 *db;
  if (sqlite3_open("/", &db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  std::cout << "DB OPENED\n";
  sqlite3_close(db);
}

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

  GObject *window = gtk_builder_get_object(builder, "window");
  g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);

  GtkBox *box = (GtkBox*) gtk_builder_get_object(builder, "box");
  GtkStack *stack = (GtkStack*) gtk_builder_get_object(builder, "stack");
  GtkStackSwitcher *switcher = (GtkStackSwitcher*) gtk_builder_get_object(builder, "switcher");

  GtkLabel *labelGrammar = GTK_LABEL(gtk_label_new("Grammar"));
  GtkLabel *labelVocabulary = GTK_LABEL(gtk_label_new("Vocabulary"));

  gtk_stack_add_titled(stack, GTK_WIDGET(labelGrammar), "Grammar", "Grammar");
  gtk_stack_add_titled(stack, GTK_WIDGET(labelVocabulary), "Vocabulary", "Vocabulary");

  gtk_widget_set_halign(GTK_WIDGET(switcher), GTK_ALIGN_CENTER);

  gtk_box_pack_start(box, GTK_WIDGET(switcher), FALSE, FALSE, 6);
  gtk_box_pack_start(box, GTK_WIDGET(stack), TRUE, TRUE, 6);

  // GObject *vocabulary = gtk_builder_get_object(builder, "vocabulary");
  // g_signal_connect(vocabulary, "clicked", G_CALLBACK(vocabulary_cb), NULL);

  gtk_widget_show_all(GTK_WIDGET(window));

  gtk_main();


  sqlite3 *db;
  if (sqlite3_open("/", &db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  std::cout << "DB OPENED\n";
  sqlite3_close(db);

  return 0;
}

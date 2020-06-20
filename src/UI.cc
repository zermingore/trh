#include <iostream>
#include <stdexcept>

#include <gtkmm.h>
#include <gtkmm.h>

// #include <iostream>
// #include <memory>

// #include <gtk/gtk.h>
// #include <gtkmm.h>
// #include <gtkmm/application.h>

// extern "C" {
// # include <lib/sqlite3.h>
// }


#include <UI.hh>
#include <MainWindow.hh>


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
}


// MainWindow::MainWindow(const char* db_file_name)
// {
//   return;
//   auto builder = Gtk::Builder::create();
//   try
//   {
//     builder->add_from_file("ui_main.xml");
//   }
//   catch (const Glib::FileError& e)
//   {
//     std::cerr << "GtkBuilder FileError: " << e.what() << '\n';
//     throw e;
//   }
//   catch (const Glib::MarkupError& e)
//   {
//     std::cerr << "GtkBuilder MarkupError: " << e.what() << '\n';
//     throw e;
//   }
//   catch (const Gtk::BuilderError& e)
//   {
//     std::cerr << "GtkBuilder BuilderError: " << e.what() << '\n';
//     throw e;
//   }

//   Gtk::Stack* stack;
//   builder->get_widget("stack", stack);
//   if (!stack)
//     throw std::runtime_error("No [stack] object in window.ui\n");

//   // auto tab = dynamic_cast<Gtk::ScrolledWindow*> (stack->get_focus_child());
//   // if (!tab)
//   // {
//   //   std::cerr << "DBG: No child\n";
//   //   // throw std::runtime_error("No visible child\n");
//   // }

//   // auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
//   // scrolled->set_hexpand(true);
//   // scrolled->set_vexpand(true);
//   // scrolled->show();

//   // GtkScrolledWindow* scrolled;
//   // builder->get_widget("vocabularyView", scrolled);

//   // auto view = Gtk::make_managed<Gtk::TextView>();
//   // view->set_editable(false);
//   // view->set_cursor_visible(false);
//   // view->show();
//   // scrolled->add(*view);
//   // stack->add(*scrolled, "basename", "basename");


//   // GtkStackSwitcher *switcher = (GtkStackSwitcher*) gtk_builder_get_object(builder, "switcher");

//   // gtk_widget_set_halign(GTK_WIDGET(switcher), GTK_ALIGN_CENTER);

//   // GtkWidget *vocabularyView = (GtkWidget*) gtk_builder_get_object(builder, "vocabularyView");
//   // gtk_stack_set_visible_child(stack, vocabularyView);


//   // GtkListStore *store = gtk_list_store_new(
//   //   (int) e_db_words_col::NB_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

//   // // DB::initialize("db.sql");
//   // // DB::getWordsSorted(callback, store);
//   // // DB::close();

//   // GtkWidget *vocabularyList = (GtkWidget*) gtk_builder_get_object(builder, "vocabularyList");
//   // GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
//   // GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
//   //   "language", renderer, "text", 1, NULL);
//   // gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

//   // renderer = gtk_cell_renderer_text_new();
//   // column = gtk_tree_view_column_new_with_attributes("category", renderer, "text", 2, NULL);
//   // gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

//   // renderer = gtk_cell_renderer_text_new();
//   // column = gtk_tree_view_column_new_with_attributes("name", renderer, "text", 3, NULL);
//   // gtk_tree_view_append_column(GTK_TREE_VIEW(vocabularyList), column);

//   // gtk_tree_view_set_model(GTK_TREE_VIEW(vocabularyList), GTK_TREE_MODEL(store));
//   // g_object_unref(store);
//   // gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vocabularyList), FALSE);


//   // builder->get_widget_derived("window", wnd);
//   // auto r = app->run(*wnd);
// }



int UI::run()
{
  auto r = _app->run(*_window);
  delete _window;

  return r;
}

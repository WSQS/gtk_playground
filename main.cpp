#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
  auto window = gtk_application_window_new(app);
  auto gtk_window = GTK_WINDOW(window);
  gtk_window_set_title(gtk_window, "Hello");
  gtk_window_set_default_size(gtk_window, 200, 200);

  auto button = gtk_button_new_with_label("Hello World");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_window_set_child(gtk_window, button);
  
  gtk_window_present(gtk_window);
}

int main(int argc, char **argv) {
  auto app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  const auto status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

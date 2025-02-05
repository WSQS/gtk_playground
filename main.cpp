#include <gtk/gtk.h>
#include <string> // to_string

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}
inline auto add_number(GtkGrid *grid, int number) {
  auto button = gtk_button_new_with_label(std::to_string(number).data());
  gtk_grid_attach(grid, button, (number - 1) % 3, (number - 1) / 3, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
}
static void activate(GtkApplication *app, gpointer user_data) {
  auto window = gtk_application_window_new(app);
  auto gtk_window = GTK_WINDOW(window);
  gtk_window_set_title(gtk_window, "Hello");
  gtk_window_set_default_size(gtk_window, 200, 200);
  auto grid = gtk_grid_new();
  auto box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  for (int i = 1; i < 10; ++i)
    add_number(GTK_GRID(grid), i);
  gtk_window_set_child(GTK_WINDOW(window), box);

  auto button = gtk_button_new_with_label("Hello World");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_close),
                           gtk_window);
  gtk_box_append(GTK_BOX(box), grid);

  gtk_window_present(gtk_window);
}

int main(int argc, char **argv) {
  auto app =
      gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);
  const auto status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

#include <gtk/gtk.h>
#include <memory>
#include <string> // to_string

class label_wrapper {
  GtkWidget *label{nullptr};
  std::string string{};

public:
  void init(std::string input_string = {}) {
    string = input_string;
    label = gtk_label_new(string.data());
  }
  void set_label(const std::string &input_string) {
    string = input_string;
    gtk_label_set_label(GTK_LABEL(label), string.data());
  }
  void append(const std::string &input_string) {
    string += input_string;
    gtk_label_set_label(GTK_LABEL(label), string.data());
  }
  auto get() { return label; }
};

label_wrapper screen{};

class button_wrapper {
  GtkWidget *button{nullptr};
  std::string string{};
  static void print_label(std::string *label) {
    g_print("Button %s clicked\n", (*label).data());
  }

public:
  void init(std::string input_string = {}) {
    string = input_string;
    button = gtk_button_new_with_label(string.data());
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(print_label),
                             &string);
  }
  void set_label(const std::string &input_string) {
    string = input_string;
    gtk_button_set_label(GTK_BUTTON(button), string.data());
  }
  auto get() { return button; }
};

static void print_hello(GtkWidget *, gpointer) { g_print("Hello World\n"); }

inline auto add_number(int *number) {
  screen.append(std::to_string(*number));
}
inline auto add_button(GtkGrid *grid, int number) {
  auto button = new button_wrapper();
  button->init(std::to_string(number));
  gtk_grid_attach(grid, button->get(), (number - 1) % 3, (number - 1) / 3, 1,
                  1);
  g_signal_connect(button->get(), "clicked", G_CALLBACK(print_hello), nullptr);
  auto i = new int(number);
  g_signal_connect_swapped(button->get(), "clicked", G_CALLBACK(add_number), i);
}
static void activate(GtkApplication *app, gpointer) {
  auto window = gtk_application_window_new(app);
  auto gtk_window = GTK_WINDOW(window);
  gtk_window_set_title(gtk_window, "Hello");
  gtk_window_set_default_size(gtk_window, 200, 200);
  auto grid = gtk_grid_new();
  auto box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  for (int i = 1; i < 10; ++i)
    add_button(GTK_GRID(grid), i);
  gtk_window_set_child(GTK_WINDOW(window), box);

  auto button = gtk_button_new_with_label("Hello World");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_close),
                           gtk_window);
  screen.init();
  gtk_box_append(GTK_BOX(box), screen.get());
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

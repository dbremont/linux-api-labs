#include <gtk/gtk.h>
#include <iostream>
#include <string>

// Callback when text is changed
static void on_text_changed(GtkEntry *entry, GtkLabel *label) {
    const gchar *text = gtk_entry_get_text(entry);
    std::string char_count = "Characters: " + std::to_string(strlen(text));
    gtk_label_set_text(label, char_count.c_str());
}

// Callback when "Send" is clicked
static void on_send_clicked(GtkEntry *entry) {
    std::cout << "Sent: " << gtk_entry_get_text(entry) << std::endl;
}

// Callback when "Reset" is clicked
static void on_reset_clicked(GtkEntry *entry, GtkLabel *label) {
    gtk_entry_set_text(entry, "");  // Clear text
    gtk_label_set_text(label, "Characters: 0");  // Reset count
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Character Counter");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create vertical box layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Input field
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Type here...");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Character count label
    GtkWidget *char_count_label = gtk_label_new("Characters: 0");
    gtk_box_pack_start(GTK_BOX(vbox), char_count_label, FALSE, FALSE, 0);

    // Buttons box
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // "Send" button
    GtkWidget *send_button = gtk_button_new_with_label("Send");
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_clicked), entry);
    gtk_box_pack_start(GTK_BOX(hbox), send_button, TRUE, TRUE, 0);

    // "Reset" button
    GtkWidget *reset_button = gtk_button_new_with_label("Reset");
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_clicked), entry);
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_clicked), char_count_label);
    gtk_box_pack_start(GTK_BOX(hbox), reset_button, TRUE, TRUE, 0);

    // Connect text changed event
    g_signal_connect(entry, "changed", G_CALLBACK(on_text_changed), char_count_label);

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

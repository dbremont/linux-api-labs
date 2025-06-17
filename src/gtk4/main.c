#include <gtk/gtk.h>

// Sample data points
static double data_x[] = {0, 1, 2, 3, 4, 5};
static double data_y[] = {0, 1, 4, 9, 16, 25};
static int n_points = sizeof(data_x) / sizeof(data_x[0]);

// Draw callback for GtkDrawingArea
static void
on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{
    // Clear background (white)
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Draw axes (black)
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);

    // X axis
    cairo_move_to(cr, 40, height - 40);
    cairo_line_to(cr, width - 10, height - 40);

    // Y axis
    cairo_move_to(cr, 40, height - 40);
    cairo_line_to(cr, 40, 10);

    cairo_stroke(cr);

    // Find max values for scaling
    double max_x = data_x[n_points - 1];
    double max_y = 0;
    for (int i = 0; i < n_points; i++) {
        if (data_y[i] > max_y)
            max_y = data_y[i];
    }

    // Plot points as circles
    double margin_left = 40;
    double margin_bottom = 40;
    double plot_width = width - margin_left - 10;
    double plot_height = height - margin_bottom - 10;

    cairo_set_source_rgb(cr, 1, 0, 0); // red points

    for (int i = 0; i < n_points; i++) {
        double x = margin_left + (data_x[i] / max_x) * plot_width;
        double y = height - margin_bottom - (data_y[i] / max_y) * plot_height;

        cairo_arc(cr, x, y, 5, 0, 2 * G_PI);
        cairo_fill(cr);
    }
}

// Handler to quit main loop on window close
static gboolean
on_close_request(GtkWindow *window, gpointer user_data)
{
    GMainLoop *loop = user_data;
    g_main_loop_quit(loop);
    return TRUE; // Stop other handlers and close manually
}

int main(int argc, char **argv)
{
    gtk_init();

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "GTK4 Simple Scatter Plot");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Connect close request signal to quit loop
    g_signal_connect(window, "close-request", G_CALLBACK(on_close_request), loop);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), on_draw, NULL, NULL);

    gtk_window_set_child(GTK_WINDOW(window), drawing_area);

    // Use the recommended way to show the window
    gtk_widget_set_visible(window, TRUE);

    g_main_loop_run(loop);

    g_main_loop_unref(loop);

    return 0;
}
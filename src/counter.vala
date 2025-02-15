// MinimalApp.vala

int main (string[] args) {
    Gtk.init ();

    var window = new Gtk.Window () {
        title = "Minimal GTK4 App"
    };

    int counter  = 1;

    var button = new Gtk.Button.with_label ("Click me!");
    button.clicked.connect (() => {
        button.label =  @"$counter";
        ++counter;
    });

    window.child = button;
    window.present ();

    while (Gtk.Window.get_toplevels ().get_n_items () > 0) {
        GLib.MainContext.@default ().iteration (true);
    }

    return 0;
}

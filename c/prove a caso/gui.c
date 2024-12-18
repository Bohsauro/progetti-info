#include <gtk/gtk.h>
int main(){
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new_with_label
   		("Click Me!");
}


#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>

void move_button( GtkWidget *widget, GtkWidget *fixed)
{
	gint x = 50;
	gint y = 50;

	x =(x + random()) % 300;
	y =(y + random()) % 200;
	gtk_fixed_move(GTK_FIXED(fixed), widget, x, y);
}

int main( int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *button;
	gint i;

	srandom((int)time(0));

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Fixed Container");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_widget_show(fixed);

	for (i = 1 ; i <= 3 ; i++) {
		button = gtk_button_new_with_label("Agree");
		g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(move_button), fixed);
		gtk_fixed_put(GTK_FIXED(fixed), button, i * 10, i * 10);
		gtk_widget_show(button);
	}

	gtk_widget_show(window);
	gtk_main();
	return 0;
}

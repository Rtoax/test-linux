#include <gtk/gtk.h>

#define pixmap GdkPixmap
#define pixbuf GdkPixmap

void hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");//temp(data);
}

gint delete_event(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	g_print("delete event occurred\n");
	return FALSE;
}

void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *draw;
	GtkWidget *frame;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	frame = gtk_aspect_frame_new("image:",0.5, 0.1,1, FALSE);
	gtk_container_add(GTK_CONTAINER(window), frame);

	draw = gtk_drawing_area_new();
	gtk_widget_set_size_request(draw, 800, 600);
	draw = gtk_image_new_from_file("bpf.png");

	// g_signal_connect(G_OBJECT(draw), "clicked", G_CALLBACK(expose_event), NULL);

	gtk_container_add(GTK_CONTAINER(frame), draw);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

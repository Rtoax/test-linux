#include <gtk/gtk.h>

int main(int argc,char* argv[])
{
	GtkWidget* window;
	GtkWidget* box;
	GtkWidget* image;
	GtkWidget* button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_title(GTK_WINDOW(window), "Splash Window");
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	box = gtk_box_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), box);
	image = gtk_image_new_from_file("bpf.png");
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
	button = gtk_button_new_with_label("Splash Window");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_widget_show_all(window);

	gtk_main();

	return FALSE;
}

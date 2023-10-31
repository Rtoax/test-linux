#include <gtk/gtk.h>

void on_button_clicked(GtkWidget* button, gpointer data)
{
	g_print("Button %s is pressed.\n", (gchar*)data);
}

GtkWidget* create_button1(void)
{
	GtkWidget* box;
	GtkWidget* image;
	GtkWidget* label;
	GtkWidget* button;
	char* title = "x";
	image = gtk_image_new_from_file("x.png");
	label = gtk_label_new(title);
	box = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);
	gtk_widget_show(image);
	gtk_widget_show(label);
	button = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button), box);
	gtk_widget_show(box);
	return button ;
}
GtkWidget* create_button2(void)
{
	GtkWidget* box;
	GtkWidget* image;
	GtkWidget* label;
	GtkWidget* button;
	char* title = "w";
	image = gtk_image_new_from_file("w.png");
	label = gtk_label_new(title);
	box = gtk_hbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);
	gtk_widget_show(image);
	gtk_widget_show(label);
	button = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button), box);
	gtk_widget_show(box);
	return button ;
}

int main(int argc,  char *argv[])
{
	GtkWidget* window;
	GtkWidget* box;
	GtkWidget* button1;
	GtkWidget* button2;
	GtkWidget* button3;
	GtkWidget* button4;

	gchar* b1 = "Red apple";
	gchar* b2 = "Small mushroom";
	gchar* b3 = "Short key";
	gchar* b4 = "OK";

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),  "Image Button");
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	box = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	button1 = create_button1();
	g_signal_connect(G_OBJECT(button1), "clicked",
	G_CALLBACK(on_button_clicked), (gpointer)b1);
	gtk_box_pack_start(GTK_BOX(box), button1, FALSE, FALSE, 5);

	button2 = create_button2();
	g_signal_connect(G_OBJECT(button2), "clicked",
	G_CALLBACK(on_button_clicked), (gpointer)b2);
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, FALSE, 5);

	button3 = gtk_button_new_with_mnemonic("Short key");
	g_signal_connect(G_OBJECT(button3), "clicked",
	G_CALLBACK(on_button_clicked), (gpointer)b3);
	gtk_box_pack_start(GTK_BOX(box), button3, FALSE, FALSE, 5);

	button4 = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button4), "clicked",
	G_CALLBACK(on_button_clicked), (gpointer)b4);
	gtk_box_pack_start(GTK_BOX(box), button4, FALSE, FALSE, 5);

	gtk_widget_show_all(window);

	gtk_main();

	return FALSE ;
}
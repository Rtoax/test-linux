#include <gtk/gtk.h>

static gchar* red = " Red " ;
static gchar* green = " Green " ;
static gchar* yellow = " Yellow " ;
static gchar* blue = " Blue " ;

void on_radio_clicked(GtkWidget* radio, gint data)
{
	g_print("The color you select is ");
	switch ((int)data) {
	case 1:
		g_print("%s", red); break;
	case 2:
		g_print("%s", green); break;
	case 3:
		g_print("%s", yellow); break;
	case 4:
		g_print("%s", blue); break;
	}
	g_print("\n");
}

int main(int argc,  char *argv[])
{
	GtkWidget* window;
	GtkWidget* frame;
	GtkWidget* box;
	GtkWidget* box1;
	GtkWidget* button1;
	GtkWidget* radio1;
	GtkWidget* radio2;
	GtkWidget* radio3;
	GtkWidget* radio4;
	GSList* group;


	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Radio Select Window");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	frame = gtk_frame_new("Please choise color:");
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_OUT);
	gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 5);

	box1 = gtk_hbox_new(FALSE, 10);
	gtk_container_set_border_width(GTK_CONTAINER(box1), 10);
	gtk_container_add(GTK_CONTAINER(frame), box1);

	radio1 = gtk_radio_button_new_with_label(NULL, red);
	g_signal_connect(G_OBJECT(radio1), "released",
			G_CALLBACK(on_radio_clicked), (gpointer)1);
	gtk_box_pack_start(GTK_BOX(box1), radio1, FALSE, FALSE, 5);
	group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1));

	radio2 = gtk_radio_button_new_with_label(group, green);
	g_signal_connect(G_OBJECT(radio2), "released",
			G_CALLBACK(on_radio_clicked), (gpointer)2);
	gtk_box_pack_start(GTK_BOX(box1), radio2, FALSE, FALSE, 5);
	group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio2));

	radio3 = gtk_radio_button_new_with_label(group, yellow);
	g_signal_connect(G_OBJECT(radio3), "released",
			G_CALLBACK(on_radio_clicked), (gpointer)3);
	gtk_box_pack_start(GTK_BOX(box1), radio3, FALSE, FALSE, 5);
	group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio3));

	radio4 = gtk_radio_button_new_with_label(group, blue);
	g_signal_connect(G_OBJECT(radio4), "released",
			G_CALLBACK(on_radio_clicked), (gpointer)4);
	gtk_box_pack_start(GTK_BOX(box1), radio4, FALSE, FALSE, 5);

	button1 = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button1), "clicked",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_box_pack_start(GTK_BOX(box), button1, FALSE, FALSE, 5);

	gtk_widget_show_all(window);

	gtk_main();

	return FALSE ;
}

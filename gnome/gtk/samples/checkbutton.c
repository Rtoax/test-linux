#include <gtk/gtk.h>

gboolean isbold = FALSE ;
gboolean isitli = FALSE ;
gboolean isuline = FALSE ;
gboolean iscolor = FALSE ;

void on_check_clicked(GtkWidget* check, gint data)
{
	switch ((int)data) {
	case 1:
		isbold = !isbold;
		break;
	case 2:
		isitli = !isitli;
		break;
	case 3:
		isuline = !isuline;
		break;
	case 4:
		iscolor = !iscolor;
		break;
	}
}

void on_button_clicked(GtkWidget *button, gpointer data)
{
	g_print("字体配置为：");
	if(isbold)
		g_print("粗体 ");
	if(isitli)
		g_print("斜体 ");
	if(isuline)
		g_print("下划线 ");
	if(iscolor)
		g_print("彩色 ");
	if( !isbold && !iscolor && !isuline && !isitli )
		g_print("正常，无任何选项");
	g_print("\n");
}

int main(int argc,  char *argv[])
{
	GtkWidget* window;
	GtkWidget* frame;
	GtkWidget* box;
	GtkWidget* button;
	GtkWidget* box1;
	GtkWidget* check1;
	GtkWidget* check2;
	GtkWidget* check3;
	GtkWidget* check4;

	char* title = "多项选择窗口";

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	frame = gtk_frame_new("字体选项：");
	gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 5);

	box1 = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), box1);
	gtk_container_set_border_width(GTK_CONTAINER(box1), 10);

	gtk_widget_show(box);

	check1 = gtk_check_button_new_with_label(" 粗体 ");
	g_signal_connect(G_OBJECT(check1), "released",
			G_CALLBACK(on_check_clicked), (gpointer)1);
	gtk_box_pack_start(GTK_BOX(box1), check1, FALSE, FALSE, 3);

	check2 = gtk_check_button_new_with_label(" 斜体 ");
	g_signal_connect(G_OBJECT(check2), "released",
			G_CALLBACK(on_check_clicked), (gpointer)2);
	gtk_box_pack_start(GTK_BOX(box1), check2, FALSE, FALSE, 3);

	check3 = gtk_check_button_new_with_label(" 下划线 ");
	g_signal_connect(G_OBJECT(check3), "released",
			G_CALLBACK(on_check_clicked), (gpointer)3);
	gtk_box_pack_start(GTK_BOX(box1), check3, FALSE, FALSE, 3);

	check4 = gtk_check_button_new_with_label(" 彩色 ");
	g_signal_connect(G_OBJECT(check4), "released",
			G_CALLBACK(on_check_clicked), (gpointer)4);
	gtk_box_pack_start(GTK_BOX(box1), check4, FALSE, FALSE, 3);

	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(on_button_clicked), NULL);
	g_signal_connect_swapped(G_OBJECT(button), "clicked",
			G_CALLBACK(gtk_widget_destroy), window);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 5);

	gtk_widget_show_all(window);

	gtk_main();

	return FALSE ;
}
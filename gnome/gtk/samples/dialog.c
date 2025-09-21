#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget* button,gint data)
{
	GtkWidget* dialog ;
	GtkMessageType type ;
	gchar *message;
	switch ((int)data) {
	case 1 :
		message = "这是一个信息提示对话框．";
		type = GTK_MESSAGE_INFO ; break;
	case 2 :
		message = "这是一个错误提示对话框．";
		type = GTK_MESSAGE_ERROR ; break;
	case 3 :
		message = "这是一个问题提示对话框．";
		type = GTK_MESSAGE_QUESTION ; break;
	case 4 :
		message = "这是一个警告提示对话框．";
		type = GTK_MESSAGE_WARNING ; break;
	}

	dialog = gtk_message_dialog_new(NULL,
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			type ,
			GTK_BUTTONS_OK,
			"%s", message);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int main(int argc, char* argv[])
{
	GtkWidget* window;
	GtkWidget* frame;
	GtkWidget* box;
	GtkWidget* button1;
	GtkWidget* button2;
	GtkWidget* button3;
	GtkWidget* button4;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "创建消息框");
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	frame = gtk_frame_new("四种消息对话框：");
	gtk_container_add(GTK_CONTAINER(window), frame);

	box = gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(frame), box);
	gtk_container_set_border_width(GTK_CONTAINER(box), 20);

	button1= gtk_button_new_from_stock(GTK_STOCK_DIALOG_INFO);
	gtk_box_pack_start(GTK_BOX(box), button1, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button1), "clicked",
			G_CALLBACK(on_button_clicked), (gpointer)1);

	button2 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_ERROR);
	gtk_box_pack_start(GTK_BOX(box), button2, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button2), "clicked",
			G_CALLBACK(on_button_clicked),(gpointer)2);

	button3 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_QUESTION);
	gtk_box_pack_start(GTK_BOX(box), button3, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button3), "clicked",
			G_CALLBACK(on_button_clicked),(gpointer)3);

	button4 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_WARNING);
	gtk_box_pack_start(GTK_BOX(box), button4, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(button4), "clicked",
			G_CALLBACK(on_button_clicked), (gpointer)4);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}

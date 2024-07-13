#include <gtk/gtk.h>

static GtkWidget *entry;

void on_button_clicked(GtkButton* button,gpointer data)
{
	const gchar* command;
	command = gtk_entry_get_text(GTK_ENTRY(entry));
	system(command);
}

int main(int argc , char* argv[])
{
	GtkWidget *window;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *button;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",
			G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"命令窗口");
	//gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),hbox);

	label = gtk_label_new("输入命令：");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);

	entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox),entry,TRUE,TRUE,5);

	button = gtk_button_new_with_label("执行");
	g_signal_connect(G_OBJECT(button),"clicked",
			G_CALLBACK(on_button_clicked),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}

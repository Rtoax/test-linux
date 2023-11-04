#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
   GtkWidget* window;
   GtkWidget* vbox;
   GtkWidget* frame;
   GtkWidget* spin;
   GtkWidget* label;
   GtkWidget* vvbox;
   GtkWidget *hbox,*vbox1,*vbox2,*vbox3;
   GtkAdjustment* adj1;

   gtk_init(&argc,&argv);

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "滚动按钮");
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   gtk_container_set_border_width(GTK_CONTAINER(window), 10);

   vbox = gtk_vbox_new(FALSE, 0);
   gtk_container_add(GTK_CONTAINER(window), vbox);

   frame = gtk_frame_new("日历");
   gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);

   hbox = gtk_hbox_new(FALSE, 0);
   gtk_container_add(GTK_CONTAINER(frame), hbox);
   gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);

   vbox1 = gtk_vbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), vbox1, TRUE, TRUE, 5);
   label = gtk_label_new("年：");
   gtk_box_pack_start(GTK_BOX(vbox1), label, FALSE, FALSE, 2);
   spin = gtk_spin_button_new_with_range(2019,2100,1);
   gtk_box_pack_start(GTK_BOX(vbox1), spin, FALSE, FALSE, 2);

   vbox2 = gtk_vbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), vbox2, TRUE, TRUE, 5);
   label = gtk_label_new("月：");
   gtk_box_pack_start(GTK_BOX(vbox2), label, FALSE, FALSE, 2);
   spin = gtk_spin_button_new_with_range(1,12,1);
   gtk_box_pack_start(GTK_BOX(vbox2), spin, FALSE, FALSE, 2);

   vbox3 = gtk_vbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), vbox3, TRUE, TRUE, 5);
   label = gtk_label_new("日：");
   gtk_box_pack_start(GTK_BOX(vbox3), label, FALSE, FALSE, 2);
   spin = gtk_spin_button_new_with_range(1,31,1);
   gtk_box_pack_start(GTK_BOX(vbox3), spin, FALSE, FALSE, 2);

   frame = gtk_frame_new(NULL);
   gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);

   vvbox = gtk_vbox_new(FALSE, 0);
   gtk_container_add(GTK_CONTAINER(frame), vvbox);
   gtk_container_set_border_width(GTK_CONTAINER(vvbox), 10);

   label = gtk_label_new("第一个滚动按钮,\n显示整数,范围: 0 - 100");

   adj1 =(GtkAdjustment *)gtk_adjustment_new(50.0, 0.0, 100.0, 1.0, 5.0, 5.0);

   spin = gtk_spin_button_new(adj1, 5, 1);
   gtk_box_pack_start(GTK_BOX(vvbox),label,FALSE,FALSE,3);
   gtk_box_pack_start(GTK_BOX(vvbox),spin,FALSE,FALSE,3);

   label = gtk_label_new("第二个滚动按钮,\n显示浮点数,范围: 0.1 - 1.50");

   spin = gtk_spin_button_new_with_range(0, 9.9, 0.1);
   gtk_box_pack_start(GTK_BOX(vvbox), label, FALSE, FALSE, 3);
   gtk_box_pack_start(GTK_BOX(vvbox), spin, FALSE, FALSE, 3);

   gtk_widget_show_all(window);
   gtk_main();

   return FALSE;
}

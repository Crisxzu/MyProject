#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "mainMenuView.h"

void intMainMenu(GtkWidget *main_menu_label, GtkWidget *main_menu_box, GtkWidget *main_menu_button_box, GtkWidget *main_menu_run_button, GtkWidget *main_menu_settings_button, GtkWidget *main_menu_quit_button)
{	
	const char *format="<span foreground=\"black\" size=\"xx-large\" weight=\"ultrabold\">%s</span>";
	gchar *main_menu_label_str=NULL;
	
	
	main_menu_label=gtk_label_new(NULL);
	main_menu_label_str=g_markup_printf_escaped(format, "Menu Principal");
	gtk_label_set_markup(GTK_LABEL(main_menu_label), main_menu_label_str);
	
	main_menu_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	__struct_global.main_menu_box=GTK_BOX(main_menu_box);
	
	main_menu_button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_set_spacing(GTK_BOX(main_menu_button_box), 10);
	
	main_menu_run_button=gtk_button_new_with_mnemonic("_Lancer");
	main_menu_settings_button=gtk_button_new_with_mnemonic("_Paramètres");
	main_menu_quit_button=gtk_button_new_with_mnemonic("_Quitter");
	
	gtk_box_pack_start(__struct_global.main_box, main_menu_box, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(main_menu_box), main_menu_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_box), main_menu_button_box, TRUE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_run_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_settings_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_quit_button, FALSE, FALSE, 0);
	
	g_signal_connect(G_OBJECT(main_menu_run_button), "clicked", G_CALLBACK(cb_run), NULL);
	g_signal_connect(G_OBJECT(main_menu_settings_button), "clicked", G_CALLBACK(cb_settings), NULL);
	g_signal_connect(G_OBJECT(main_menu_quit_button), "clicked", G_CALLBACK(cb_quit), NULL);
	
	g_free(main_menu_label_str), main_menu_label_str=NULL;
}

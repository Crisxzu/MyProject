#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "testControler.h"
#include "struct.h"
#include "callback.h"


/*struct_global __struct_global={NULL, NULL, NULL, NULL, 5, 0, NULL, NULL, FALSE, NULL, NULL};*/

int main (int argc, char** argv)
{
	GtkWidget *main_window=NULL, *main_box=NULL;
	GtkWidget *main_menu_label=NULL, *main_menu_box=NULL, *main_menu_button_box=NULL, *main_menu_run_button=NULL, *main_menu_settings_button=NULL, *main_menu_quit_button=NULL;
	GtkWidget *settings_menu_label=NULL, *settings_menu_box=NULL, *settings_menu_button_box=NULL, *settings_menu_text_speed_box=NULL, *settings_menu_text_color_box=NULL, *text_speed_label=NULL, *text_color_label=NULL, *text_speed_inc_button=NULL, *text_speed_dec_button=NULL, *text_color_dec_button=NULL, *text_color_inc_button=NULL,*settings_menu_return_button=NULL;
	GtkWidget *run_menu_label=NULL, *run_menu_box=NULL, *run_menu_button_box=NULL, *run_menu_return_button=NULL;
	GtkWidget *combo_box_text_vn_chooser=NULL, *run_menu_play_button=NULL, *run_menu_create_vn_button=NULL;
	GtkWidget *menu_ingame_label=NULL, *menu_ingame_box=NULL, *menu_ingame_button_box=NULL, *menu_ingame_new_game_button=NULL, *menu_ingame_load_game_button=NULL, *menu_ingame_return_button=NULL;
	const char *main_menu_title="Menu principal", *run_menu_title="Lancement", *settings_menu_title="Paramètres", *menu_ingame_title="Jeu";
	const char *format="<span foreground=\"black\" size=\"xx-large\" weight=\"ultrabold\">%s</span>";
	gchar *markup_text=NULL;
	char text_speed_str[10];
	
	gtk_init(&argc, &argv);
	
	main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "Test interface graphique");
	gtk_window_set_default_size(GTK_WINDOW(main_window), 250, 100);
	__struct_global.main_window=GTK_WINDOW(main_window);
	
	main_menu_label=gtk_label_new(NULL);
	markup_text=g_markup_printf_escaped(format, main_menu_title);
	gtk_label_set_markup(GTK_LABEL(main_menu_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	
	settings_menu_label=gtk_label_new(NULL);
	markup_text=g_markup_printf_escaped(format, settings_menu_title);
	gtk_label_set_markup(GTK_LABEL(settings_menu_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	
	sprintf(text_speed_str, "%d", __struct_global.text_speed);
	text_speed_label=gtk_label_new(text_speed_str);
	
	text_color_label=gtk_label_new(NULL);
	__struct_global.format_text_color=g_strdup("<span foreground=\"%s\">%s</span>");
	markup_text=g_markup_printf_escaped(__struct_global.format_text_color, "white", "white");
	gtk_label_set_markup(GTK_LABEL(text_color_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	
	run_menu_label=gtk_label_new(NULL);
	markup_text=g_markup_printf_escaped(format, run_menu_title);
	gtk_label_set_markup(GTK_LABEL(run_menu_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	
	menu_ingame_label=gtk_label_new(NULL);
	markup_text=g_markup_printf_escaped(format, menu_ingame_title);
	gtk_label_set_markup(GTK_LABEL(menu_ingame_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	
	main_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	main_menu_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	__struct_global.main_menu_box=GTK_BOX(main_menu_box);
	
	settings_menu_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	settings_menu_text_speed_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	settings_menu_text_color_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	__struct_global.settings_menu_box=GTK_BOX(settings_menu_box);
	
	run_menu_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	__struct_global.run_menu_box=GTK_BOX(run_menu_box);
	
	menu_ingame_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	__struct_global.menu_ingame_box=GTK_BOX(menu_ingame_box);
	
	main_menu_button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_set_spacing(GTK_BOX(main_menu_button_box), 10);
	main_menu_run_button=gtk_button_new_with_mnemonic("_Lancer");
	main_menu_settings_button=gtk_button_new_with_mnemonic("_Paramètres");
	main_menu_quit_button=gtk_button_new_with_mnemonic("_Quitter");
	
	settings_menu_button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	text_speed_inc_button=gtk_button_new_with_label("+");
	text_color_inc_button=gtk_button_new_with_label("+");
	text_speed_dec_button=gtk_button_new_with_label("-");
	text_color_dec_button=gtk_button_new_with_label("-");
	settings_menu_return_button=gtk_button_new_with_mnemonic("_Return");
	
	run_menu_button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	run_menu_play_button=gtk_button_new_with_mnemonic("_Jouer ce Visual Novel");
	run_menu_create_vn_button=gtk_button_new_with_mnemonic("_Créer un Visual Novel");
	run_menu_return_button=gtk_button_new_with_mnemonic("_Return");
	
	combo_box_text_vn_chooser=gtk_combo_box_text_new();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text_vn_chooser), "Je suis là");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text_vn_chooser), "Je suis pas là");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text_vn_chooser), "Je suis");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo_box_text_vn_chooser), "Je ne suis pas");
	
	menu_ingame_button_box=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	menu_ingame_new_game_button=gtk_button_new_with_mnemonic("_Nouvelle partie");
	menu_ingame_load_game_button=gtk_button_new_with_mnemonic("_Charger une partie");
	menu_ingame_return_button=gtk_button_new_with_mnemonic("_Return");
	
	gtk_container_add(GTK_CONTAINER(main_window), main_box);
	
	gtk_box_pack_start(GTK_BOX(main_box), main_menu_box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), settings_menu_box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), run_menu_box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), menu_ingame_box, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(main_menu_box), main_menu_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_box), main_menu_button_box, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_run_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_settings_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_menu_button_box), main_menu_quit_button, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(settings_menu_box), settings_menu_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_box), settings_menu_button_box, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_button_box), settings_menu_text_speed_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_speed_box), text_speed_dec_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_speed_box), text_speed_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_speed_box), text_speed_inc_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_button_box), settings_menu_text_color_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_color_box), text_color_dec_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_color_box), text_color_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_text_color_box), text_color_inc_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings_menu_button_box), settings_menu_return_button, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(run_menu_box), run_menu_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(run_menu_box), run_menu_button_box, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(run_menu_button_box), combo_box_text_vn_chooser, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(run_menu_button_box), run_menu_play_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(run_menu_button_box), run_menu_create_vn_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(run_menu_button_box), run_menu_return_button, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(menu_ingame_box), menu_ingame_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(menu_ingame_box), menu_ingame_button_box, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(menu_ingame_button_box), menu_ingame_new_game_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(menu_ingame_button_box), menu_ingame_load_game_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(menu_ingame_button_box), menu_ingame_return_button, FALSE, FALSE, 0);
	
	gtk_box_set_homogeneous(GTK_BOX(main_menu_box), FALSE);
	gtk_box_set_homogeneous(GTK_BOX(settings_menu_box), FALSE);
	gtk_box_set_homogeneous(GTK_BOX(settings_menu_text_speed_box), TRUE);
	gtk_box_set_homogeneous(GTK_BOX(settings_menu_text_color_box), TRUE);
	gtk_box_set_homogeneous(GTK_BOX(run_menu_box), FALSE);
	
	g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(cb_quit), NULL);
	
	g_signal_connect(G_OBJECT(main_menu_run_button), "clicked", G_CALLBACK(cb_run), NULL);
	g_signal_connect(G_OBJECT(main_menu_settings_button), "clicked", G_CALLBACK(cb_settings), NULL);
	g_signal_connect(G_OBJECT(main_menu_quit_button), "clicked", G_CALLBACK(cb_quit), NULL);
	
	g_signal_connect(G_OBJECT(text_speed_inc_button), "clicked", G_CALLBACK(cb_text_speed_inc), text_speed_label);
	g_signal_connect(G_OBJECT(text_speed_dec_button), "clicked", G_CALLBACK(cb_text_speed_dec), text_speed_label);
	g_signal_connect(G_OBJECT(text_color_inc_button), "clicked", G_CALLBACK(cb_text_color_inc), text_color_label);
	g_signal_connect(G_OBJECT(text_color_dec_button), "clicked", G_CALLBACK(cb_text_color_dec), text_color_label);
	g_signal_connect(G_OBJECT(settings_menu_return_button), "clicked", G_CALLBACK(cb_return), settings_menu_box);
	
	g_signal_connect(G_OBJECT(combo_box_text_vn_chooser), "changed", G_CALLBACK(cb_changed), NULL);
	g_signal_connect(G_OBJECT(run_menu_play_button), "clicked", G_CALLBACK(cb_play), combo_box_text_vn_chooser);
	g_signal_connect(G_OBJECT(run_menu_create_vn_button), "clicked", G_CALLBACK(cb_create_vn), combo_box_text_vn_chooser);
	g_signal_connect(G_OBJECT(run_menu_return_button), "clicked", G_CALLBACK(cb_return), run_menu_box);
	
	g_signal_connect(G_OBJECT(menu_ingame_new_game_button), "clicked", G_CALLBACK(cb_create_vn), NULL);
	g_signal_connect(G_OBJECT(menu_ingame_load_game_button), "clicked", G_CALLBACK(cb_create_vn), NULL);
	g_signal_connect(G_OBJECT(menu_ingame_return_button), "clicked", G_CALLBACK(cb_return), menu_ingame_box);
	
	gtk_widget_show_all(main_window);
	gtk_widget_hide(run_menu_box);
	gtk_widget_hide(settings_menu_box);
	gtk_widget_hide(menu_ingame_box);
	
	gtk_main();
	return 0;
}

#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "struct.h"
#include "error.h"


void cb_quit(GtkWidget *p_widget, gpointer user_data)
{
	g_free(__struct_global.format_text_color), __struct_global.format_text_color=NULL;
	g_free(__struct_global.vn_folder_name), __struct_global.vn_folder_name=NULL;
	gtk_main_quit();
	
	(void)p_widget;
	(void)user_data;
}

void cb_run(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(__struct_global.main_menu_box));
	gtk_widget_show(GTK_WIDGET(__struct_global.run_menu_box));
	
	(void)p_widget;
	(void)user_data;
}

void cb_settings(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(__struct_global.main_menu_box));
	gtk_widget_show(GTK_WIDGET(__struct_global.settings_menu_box));
	
	(void)p_widget;
	(void)user_data;
}

void cb_return(GtkWidget *p_widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
	gtk_widget_show(GTK_WIDGET(__struct_global.main_menu_box));
	
	(void)p_widget;
}

void cb_text_speed_inc(GtkWidget *p_widget, gpointer user_data)
{
	gchar text_speed_str[5];
	
	__struct_global.text_speed++;
	if (__struct_global.text_speed>TEXT_SPEED_MAX)
	{
		__struct_global.text_speed=TEXT_SPEED_MAX;
	}
	sprintf(text_speed_str, "%d", __struct_global.text_speed);
	gtk_label_set_text(GTK_LABEL(user_data), text_speed_str);	
}

void cb_text_speed_dec(GtkWidget *p_widget, gpointer user_data)
{
	gchar text_speed_str[5];
	
	__struct_global.text_speed--;
	if (__struct_global.text_speed<TEXT_SPEED_MIN)
	{
		__struct_global.text_speed=TEXT_SPEED_MIN;
	}
	sprintf(text_speed_str, "%d", __struct_global.text_speed);
	gtk_label_set_text(GTK_LABEL(user_data), text_speed_str);
}

void cb_text_color_inc(GtkWidget *p_widget, gpointer user_data)
{
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	gchar *markup_text=NULL;
	
	__struct_global.text_color++;
	if (__struct_global.text_color>TEXT_COLOR_MAX)
	{
		__struct_global.text_color=TEXT_COLOR_MAX;
	}
	markup_text=g_markup_printf_escaped(__struct_global.format_text_color, color_name[__struct_global.text_color]);
	gtk_label_set_markup(GTK_LABEL(user_data), markup_text);
	
	g_free(markup_text), markup_text=NULL;
}

void cb_text_color_dec(GtkWidget *p_widget, gpointer user_data)
{
	char* color_name[6]={"white", "blue", "cyan", "red", "magenta", "yellow"};
	gchar *markup_text=NULL;
	
	__struct_global.text_color--;
	if (__struct_global.text_color<TEXT_COLOR_MIN)
	{
		__struct_global.text_color=TEXT_COLOR_MIN;
	}
	markup_text=g_markup_printf_escaped(__struct_global.format_text_color, color_name[__struct_global.text_color], color_name[__struct_global.text_color]);
	gtk_label_set_markup(GTK_LABEL(user_data), markup_text);
	
	g_free(markup_text), markup_text=NULL;
}

void cb_play(GtkWidget *p_widget, gpointer user_data)
{
	if (__struct_global.vn_isSelected)
	{
		__struct_global.vn_folder_name=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(user_data));
		gtk_widget_hide(GTK_WIDGET(__struct_global.run_menu_box));
		gtk_widget_show(GTK_WIDGET(__struct_global.menu_ingame_box));
	}
	else
	{
		print_warning("Aucun Visual Novel choisi");
	}
	(void)p_widget;
}

void cb_changed(GtkWidget *p_widget, gpointer user_data)
{
	__struct_global.vn_isSelected=TRUE;
}

void cb_create_vn(GtkWidget *p_widget, gpointer user_data)
{
	GtkWidget *create_vn_dialog=NULL, *content_area_dialog=NULL, *entry_widget=NULL;
	const char * vn_name=NULL;
	create_vn_dialog=gtk_dialog_new_with_buttons("Entrez le nom du Visual Novel", __struct_global.main_window, GTK_DIALOG_MODAL, "Retour", GTK_RESPONSE_CANCEL, "Créer", GTK_RESPONSE_ACCEPT, NULL);
	entry_widget=gtk_entry_new();
	content_area_dialog=gtk_dialog_get_content_area(GTK_DIALOG(create_vn_dialog));
	gtk_container_add(GTK_CONTAINER(content_area_dialog), entry_widget);
	gtk_widget_show_all(create_vn_dialog);
	if (gtk_dialog_run(GTK_DIALOG(create_vn_dialog))==GTK_RESPONSE_ACCEPT)
	{
		vn_name=gtk_entry_get_text(GTK_ENTRY(entry_widget));
		if(g_strcmp0(vn_name, "")!=0)
		{
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(user_data), vn_name);
			__struct_global.vn_folder_name=g_strdup(vn_name);
		}
	}
	gtk_widget_destroy(create_vn_dialog);
	
	(void)p_widget;
}

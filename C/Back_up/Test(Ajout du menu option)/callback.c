#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "struct.h"


void cb_quit(GtkWidget *p_widget, gpointer user_data)
{
	g_free(__struct_global.format_text_color), __struct_global.format_text_color=NULL;
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

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "test.h"
#include "callback.h"


int main (int argc, char** argv)
{
	gtk_init(&argc, &argv);
	
	GtkWidget *main_window=NULL, *paned=NULL, *scrolled_window=NULL, *s_window=NULL;
	GtkWidget *overlay_container=NULL, *background=NULL, *text_view=NULL, *profile_picture_and_name_box=NULL,*profile_picture=NULL, *name=NULL, *name_label=NULL, *button_box=NULL, *edit_button=NULL, *save_button=NULL, *new_button=NULL;
	GtkWidget *box=NULL;
	GtkTextBuffer *text_buffer=NULL;
	GtkTextIter iter;
	const char *format="<span foreground=\"White\">%s</span>";
	float result=0.8*533;
	float result2=0.2*533;
	GdkPixbuf *pixbuf=NULL;
	gchar *markup_text=NULL;
	
	main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW(main_window), 786, 533);
	gtk_window_set_resizable (GTK_WINDOW(main_window), FALSE);
	
	overlay_container=gtk_overlay_new();
	gtk_container_add(GTK_CONTAINER(main_window), overlay_container);
	
	/*pixbuf=gdk_pixbuf_new_from_file_at_scale(NULL, 786, 533, FALSE, NULL);*/
	background=gtk_image_new_from_pixbuf(pixbuf);
	/*g_object_unref(pixbuf), pixbuf=NULL;*/
	gtk_container_add(GTK_CONTAINER(overlay_container), background);
	/*gtk_container_set_border_width (GTK_CONTAINER(overlay_container), 10);*/
	
	profile_picture_and_name_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	
	/*pixbuf=gdk_pixbuf_new_from_file_at_scale(NULL, 70, 70, FALSE, NULL);*/
	profile_picture=gtk_image_new_from_pixbuf(pixbuf);
	/*g_object_unref(pixbuf), pixbuf=NULL;*/
	
	name=gtk_button_new();
	gtk_widget_set_sensitive(name, FALSE);
	name_label=gtk_label_new(NULL);
	markup_text=g_markup_printf_escaped(format, "Cirno");
	gtk_label_set_markup(GTK_LABEL(name_label), markup_text);
	g_free(markup_text), markup_text=NULL;
	gtk_container_add(GTK_CONTAINER(name), name_label);
	
	text_view=gtk_text_view_new();
	text_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	markup_text=g_markup_printf_escaped(format, "Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo,Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo,Je suis la fée la plus forte de tout Gensokyo Je suis la fée la plus forte de tout Gensokyo");
	gtk_text_buffer_get_iter_at_line(text_buffer, &iter, 0);
	gtk_text_buffer_insert_markup(text_buffer, &iter, markup_text, -1);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view),GTK_WRAP_WORD);
	g_free(markup_text), markup_text=NULL;
	
	scrolled_window=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	s_window=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(s_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(s_window, -1, result);
	gtk_widget_set_size_request(scrolled_window, -1, result2);
	gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
	gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 50);
	
	
	box=gtk_overlay_new();
	gtk_container_add(GTK_CONTAINER(s_window), box);
	button_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	profile_picture_and_name_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_overlay_add_overlay(GTK_OVERLAY(box), profile_picture_and_name_box);
	gtk_widget_set_halign(profile_picture_and_name_box, GTK_ALIGN_START);
	gtk_widget_set_valign(profile_picture_and_name_box, GTK_ALIGN_END);
	
	paned=gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_paned_set_position(GTK_PANED(paned), result);
	gtk_paned_pack1(GTK_PANED(paned), s_window, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED(paned), scrolled_window, FALSE, FALSE);
	
	new_button=gtk_button_new_from_icon_name("document-new", GTK_ICON_SIZE_BUTTON);
	edit_button=gtk_button_new_from_icon_name("edit-find-replace", GTK_ICON_SIZE_BUTTON);
	save_button=gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_BUTTON);
	
	gtk_overlay_add_overlay(GTK_OVERLAY(overlay_container), paned);
	gtk_overlay_add_overlay(GTK_OVERLAY(overlay_container), button_box);
	gtk_widget_set_halign(button_box, GTK_ALIGN_END);
	gtk_widget_set_valign(button_box, GTK_ALIGN_END);
	
	gtk_box_pack_start(GTK_BOX(button_box), new_button, FALSE, FALSE , 0);
	gtk_box_pack_start(GTK_BOX(button_box), edit_button, FALSE, FALSE , 0);
	gtk_box_pack_start(GTK_BOX(button_box), save_button, FALSE, FALSE , 0);
	
	gtk_box_pack_start(GTK_BOX(profile_picture_and_name_box), profile_picture, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(profile_picture_and_name_box), name, FALSE, FALSE, 0);
	
	g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(cb_quit), NULL);
	
	gtk_widget_show_all(main_window);
	/*gtk_widget_hide(paned);*/
	gtk_main();
	return 0;
}

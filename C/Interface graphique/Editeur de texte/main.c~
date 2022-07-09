#include <stdlib.h>
#include <gtk/gtk.h>
#include "main.h"
#include "callback.h"
#include "document.h"
#include "menu.h"
#include "toolbar.h"
#include "hotkey.h"

docs_t docs={NULL, NULL};

int main (int argc, char **argv)
{
	GtkWidget *p_window=NULL, *p_menu_and_toolbar_box=NULL, *p_main_box=NULL, *p_notebook=NULL, *p_paned=NULL, *p_tree_view=NULL, *p_scrolled_window=NULL;
	GtkListStore  *p_list_store=NULL;
	GtkCellRenderer *p_renderer=NULL;
	GtkTreeViewColumn *p_column=NULL;
	
	gtk_init(&argc, &argv);

	p_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
	docs.p_main_window=GTK_WINDOW(p_window);
	
	p_scrolled_window=gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(p_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	p_notebook=gtk_notebook_new();
	docs.p_notebook=GTK_NOTEBOOK(p_notebook);
	
	p_paned=gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_position(GTK_PANED(p_paned), 300);
	
	p_list_store=gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
	docs.p_list_store=p_list_store;
	docs.dir_name=g_strdup(g_get_home_dir());
	dir_list();
	
	p_tree_view=gtk_tree_view_new_with_model(GTK_TREE_MODEL(p_list_store));
	
	p_renderer=gtk_cell_renderer_pixbuf_new();
	p_column=gtk_tree_view_column_new_with_attributes(NULL, p_renderer, "pixbuf", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(p_tree_view), p_column);
	
	p_renderer=gtk_cell_renderer_text_new();
	p_column=gtk_tree_view_column_new_with_attributes(NULL, p_renderer, "text", 1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(p_tree_view), p_column);
	
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(p_tree_view), FALSE);
	
	p_main_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	p_menu_and_toolbar_box=gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(p_window), p_main_box);
	gtk_container_add(GTK_CONTAINER(p_scrolled_window), p_tree_view);
	
	gtk_box_pack_start(GTK_BOX(p_menu_and_toolbar_box), GTK_WIDGET(menu_new(NULL)), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(p_menu_and_toolbar_box), GTK_WIDGET(toolbar_new(NULL)), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(p_main_box), p_menu_and_toolbar_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(p_main_box), p_paned, TRUE, TRUE, 0);
	
	gtk_paned_add1(GTK_PANED(p_paned), p_scrolled_window);
	gtk_paned_add2(GTK_PANED(p_paned), p_notebook);
	
	gtk_box_set_homogeneous(GTK_BOX(p_main_box), FALSE);
	
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);
	g_signal_connect(G_OBJECT(p_notebook), "switch-page",  G_CALLBACK(cb_page_change), NULL);
	g_signal_connect(G_OBJECT(p_tree_view), "row-activated", G_CALLBACK(cb_select), NULL);
	
	gtk_window_maximize (GTK_WINDOW (p_window));
	gtk_widget_show_all(p_window);
	gtk_window_add_accel_group(GTK_WINDOW(p_window), accel_group_new(NULL));
	
	gtk_main();
	return 0;
}


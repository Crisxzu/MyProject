#ifndef DEF_CALLBACK
#define DEF_CALLBACK

void dir_list();

void set_title();

gboolean close_all(void);

void cb_about(GtkWidget *p_widget, gpointer user_data);

void cb_select(GtkTreeView *p_tree_view, GtkTreePath *arg1, GtkTreeViewColumn *arg2, gpointer user_data);

void cb_page_change(GtkNotebook *notebook, GtkNotebookTab *page, guint page_num, gpointer user_data);

void cb_close(GtkWidget *p_widget, gpointer user_data);	

void open_file(gchar *filename);

void cb_new(GtkWidget *p_widget, gpointer user_data);

void cb_saveas(GtkWidget *p_widget, gpointer user_data);

void cb_save(GtkWidget *p_widget, gpointer user_data);

void cb_modified(GtkWidget *p_widget, gpointer user_data);

void cb_open(GtkWidget *, gpointer);

void cb_quit(GtkWidget *, gpointer);

#endif


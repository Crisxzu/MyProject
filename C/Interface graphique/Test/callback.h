#ifndef DEF_CALLBACK
#define DEF_CALLBACK

void cb_quit(GtkWidget *p_widget, gpointer user_data);

void cb_run(GtkWidget *p_widget, gpointer user_data);

void cb_settings(GtkWidget *p_widget, gpointer user_data);

void cb_return(GtkWidget *p_widget, gpointer user_data);

void cb_text_speed_inc(GtkWidget *p_widget, gpointer user_data);

void cb_text_speed_dec(GtkWidget *p_widget, gpointer user_data);

void cb_text_color_inc(GtkWidget *p_widget, gpointer user_data);

void cb_text_color_dec(GtkWidget *p_widget, gpointer user_data);

void cb_play(GtkWidget *p_widget, gpointer user_data);

void cb_changed(GtkWidget *p_widget, gpointer user_data);

void cb_create_vn(GtkWidget *p_widget, gpointer user_data);

#endif


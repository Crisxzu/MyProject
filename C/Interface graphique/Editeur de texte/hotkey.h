#ifndef DEF_HOTKEY
#define DEF_HOTKEY

#define ACCEL_PATH_NEW "<EditorGTK>/File/New"
#define ACCEL_PATH_OPEN "<EditorGTK>/File/Open"
#define ACCEL_PATH_SAVE "<EditorGTK>/File/Save"
#define ACCEL_PATH_SAVEAS "<EditorGTK>/File/Save as"
#define ACCEL_PATH_CLOSE "<EditorGTK>/File/Close"
#define ACCEL_PATH_QUIT "<EditorGTK>/File/Quit"
#define ACCEL_PATH_ABOUT "<EditorGTK>/About"

GtkAccelGroup *accel_group_new(gpointer user_data);

void accelerator_new(GtkAccelGroup *p_accel_group, const gchar *accelerator, const gchar *accel_path,  GCallback callback, gpointer user_data);

gboolean accel_new(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_open(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_save(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_saveas(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_close(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_quit(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);

gboolean accel_about(GtkAccelGroup *p_accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data);


#endif


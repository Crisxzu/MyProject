#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gtk/gtk.h>
#include "error.h"
#include "struct.h"


void print_info(char *format, ...)
{
	va_list va;

	va_start (va, format);
	print_message(GTK_MESSAGE_INFO, format, va);
	printf ("Information : ");
	vprintf (format, va);
	printf ("\n");
}

void print_warning(char *format, ...)
{
	va_list va;

	va_start (va, format);
	print_message(GTK_MESSAGE_WARNING, format, va);
	fprintf (stderr, "Erreur : ");
	vfprintf (stderr, format, va);
	fprintf (stderr, "\n");
}

void print_error(char *format, ...)
{
	va_list va;

	va_start (va, format);
	print_message(GTK_MESSAGE_ERROR, format, va);
	fprintf (stderr, "Erreur fatale : ");
	vfprintf (stderr, format, va);
	fprintf (stderr, "\n");
	exit (EXIT_FAILURE);
}

void print_message(GtkMessageType type, const gchar *format, va_list va)
{
	gchar *message=NULL;
	GtkWidget *p_dialog=NULL;
	
	message=g_strdup_vprintf(format, va);
	p_dialog=gtk_message_dialog_new(__struct_global.main_window, GTK_DIALOG_MODAL, type, GTK_BUTTONS_OK, "%s", message);
	g_free(message), message=NULL;
	gtk_dialog_run(GTK_DIALOG(p_dialog));
	gtk_widget_destroy(p_dialog);
}

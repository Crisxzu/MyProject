#ifndef DEF_ERROR
#define DEF_ERROR

void print_info(char *, ...);

void print_warning(char *, ...);

void print_error(char *, ...);

void print_message(GtkMessageType type, const gchar *format, va_list va);
#endif


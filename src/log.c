#include "flibc/log.h"

#include <stdlib.h>
#include <stdarg.h>

void log_open(const char *ident)
{
	openlog(ident, LOG_PID, LOG_DAEMON);

	return;
}

void log_close(void)
{
	closelog();

	return;
}

void log_write(int level, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vsyslog(level, fmt, args);
	va_end(args);

	return;
}

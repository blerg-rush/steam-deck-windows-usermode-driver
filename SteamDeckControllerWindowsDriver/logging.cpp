
#include "logging.h"
#include <iostream>
#include <windows.h>   // WinApi header


HANDLE _console_handle;

void set_console_color(uint8_t color)
{
	if(_console_handle == NULL)
		_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(_console_handle, color);
}

void log_prefix(const char* tag, int lvl) {
	snprintf(tag_padded, LOG_TAG_LEN + 1, "%s", tag);
	printf("[%c] %-" xstr(LOG_TAG_LEN) "s ", levels[lvl], tag_padded);
}

void _log(const char* tag, LogLevel lvl, const char* fmt, ...) {
	if (lvl < LOG_LEVEL)
		return;

	uint8_t color = 11;

	if (lvl > LLVL_WARN)
	{
		color = 12;
	}
	else if (lvl > LLVL_INFO) {
		color = 14;
	}
	else if (lvl > LLVL_DEBUG) {
		color = 15;
	}

	set_console_color(color);
	log_prefix(tag, lvl);
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

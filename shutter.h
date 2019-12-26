#ifndef SHUTTER_H
#define SHUTTER_H

enum screenshot_type {
	FILE_T,
	CLIPBOARD_T
};

struct screenshot_args {
	enum screenshot_type type;
	char *path;
	char *format;
};

#endif

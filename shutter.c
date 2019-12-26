#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "shutter.h"
#include "screenshot-area-selection.h"

void area_screenshot_callback(GdkRectangle *rect, struct screenshot_args *args) {
	GdkPixbuf *screenshot;
	GdkWindow *root;
	
	if (rect != NULL) {
		root = gdk_get_default_root_window ();
		screenshot = gdk_pixbuf_get_from_window (root, rect->x, rect->y, rect->width, rect->height);
		
		if (args->type == FILE_T) {
			gdk_pixbuf_save(screenshot, args->path, args->format, NULL, NULL);
		}

	}
}

void whole_screen_screenshot(struct screenshot_args *args) {
	GdkWindow *root;
	GdkPixbuf *screenshot;
	gint x, y, width, height;

	root = gdk_get_default_root_window ();
	gdk_window_get_geometry (root, &x, &y, &width, &height);
	screenshot = gdk_pixbuf_get_from_window (root, x, y, width, height);

	if (args->type == FILE_T) {
		gdk_pixbuf_save(screenshot, args->path, args->format, NULL, NULL);
	}
}

void print_usage(char *name) {
	printf("usage: %s [-a | -s] [-p <folder>] [-t <type>] [-h]\n", name);
}

int main(int argc, char *argv[]) {
	char opt, mode = -1;
	time_t now;
	time(&now);
	
	char format[5];
	char format_set = 0;

	char name[21];

	char folder[PATH_MAX];
	char folder_set = 0;

	char *path;

	struct screenshot_args args;
	char type_set = 0;

	if (argc == 1) {
		print_usage(argv[0]);
		return 0;
	}

	gtk_init(&argc, &argv);

	while ((opt = getopt(argc, argv, "chasp:t:")) != -1) {
		switch (opt) {
			case 'c':
				args.type = CLIPBOARD_T;
				type_set = 1;
				break;
			case 'p':
				strcpy(folder, optarg);
				folder_set = 1;
				break;
			case 't':
				strcpy(format, optarg);
				format_set = 1;
				break;
			case 'a':
				mode = 1;
				break;
			case 's':
				mode = 0;
				break;
			default:
				print_usage(argv[0]);
		}
	}

	if (!folder_set) {
		getcwd(folder, sizeof(folder));
	}

	if (!format_set) {
		strcpy(format, "png");
	}

	if (!type_set) {
		args.type = FILE_T;
	}

	path = malloc(strlen(folder)+25);

	strftime(name, sizeof(name), "%F-%T", localtime(&now));
	sprintf(path, "%s/%s.%s", folder, name, format);

	args.path = path;
	args.format = format;

	if (mode == 0) {
		whole_screen_screenshot(&args);
	}

	else if (mode == 1) {
		screenshot_select_area_x11(&area_screenshot_callback, &args);
	}

	free(path);

	return 0;
}

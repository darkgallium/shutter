#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "screenshot-area-selection.h"

void area_screenshot_callback(GdkRectangle *rect, char *path, char *type) {
	GdkPixbuf *screenshot;
	GdkWindow *root;
	
	if (rect != NULL) {
		root = gdk_get_default_root_window ();
		screenshot = gdk_pixbuf_get_from_window (root, rect->x, rect->y, rect->width, rect->height);
		gdk_pixbuf_save(screenshot, path, type, NULL, NULL);
	}
}

void whole_screen_screenshot(char *path, char *type) {
	GdkWindow *root;
	GdkPixbuf *screenshot;
	gint x, y, width, height;

	root = gdk_get_default_root_window ();
	gdk_window_get_geometry (root, &x, &y, &width, &height);
	screenshot = gdk_pixbuf_get_from_window (root, x, y, width, height);
	gdk_pixbuf_save(screenshot, path, type, NULL, NULL);
}

void print_usage(char *name) {
	printf("usage: %s [-a | -s] [-p <folder>] [-t <type>] [-h]\n", name);
}

int main(int argc, char *argv[]) {
	char opt, mode = -1;
	time_t now;
	time(&now);
	
	char type[5];
	char type_set = 0;

	char name[21];

	char folder[PATH_MAX];
	char folder_set = 0;

	char *path;

	if (argc == 1) {
		print_usage(argv[0]);
		return 0;
	}

	gtk_init(&argc, &argv);

	while ((opt = getopt(argc, argv, "hasp:t:")) != -1) {
		switch (opt) {
			case 'p':
				strcpy(folder, optarg);
				folder_set = 1;
				break;
			case 't':
				strcpy(type, optarg);
				type_set = 1;
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

	if (!type_set) {
		strcpy(type, "png");
	}

	path = malloc(strlen(folder)+25);

	strftime(name, sizeof(name), "%F-%T", localtime(&now));
	sprintf(path, "%s/%s.%s", folder, name, type);

	if (mode == 0) {
		whole_screen_screenshot(path, type);
	}

	else if (mode == 1) {
		screenshot_select_area_x11(&area_screenshot_callback, path, type);
	}

	free(path);

	return 0;
}

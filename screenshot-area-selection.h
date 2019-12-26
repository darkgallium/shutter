#ifndef SCREENSHOT_AREA_SELECT_H
#include <gdk/gdk.h>

typedef void (* SelectAreaCallback) (GdkRectangle *rectangle, char *filename, char *type);

typedef struct {
  GdkRectangle rectangle;
  SelectAreaCallback callback;
  gboolean aborted;
} CallbackData;

void screenshot_select_area_x11 (SelectAreaCallback callback, char *filename, char *type);

#endif

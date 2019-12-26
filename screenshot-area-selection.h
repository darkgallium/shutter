#ifndef SCREENSHOT_AREA_SELECT_H
#define SCREENSHOT_AREA_SELECT_H

#include <gdk/gdk.h>
#include "shutter.h"

typedef void (* SelectAreaCallback) (GdkRectangle *rectangle, struct screenshot_args *args);

typedef struct {
  GdkRectangle rectangle;
  SelectAreaCallback callback;
  gboolean aborted;
} CallbackData;

void screenshot_select_area_x11 (SelectAreaCallback callback, struct screenshot_args *args);

#endif

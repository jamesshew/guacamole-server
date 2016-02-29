/*
 * Copyright (C) 2016 Glyptodon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "config.h"
#include "display.h"
#include "log.h"

#include <guacamole/client.h>
#include <guacamole/timestamp.h>

#include <stdlib.h>

int guacenc_display_sync(guacenc_display* display, guac_timestamp timestamp) {

    /* Verify timestamp is not decreasing */
    if (timestamp < display->last_sync) {
        guacenc_log(GUAC_LOG_DEBUG, "Decreasing sync timestamp");
        return 1;
    }

    /* Update timestamp of display */
    display->last_sync = timestamp;

    /* STUB */

    return 0;

}

guacenc_layer* guacenc_display_get_layer(guacenc_display* display,
        int index) {

    /* Do not lookup / allocate if index is invalid */
    if (index < 0 || index > GUACENC_DISPLAY_MAX_LAYERS) {
        guacenc_log(GUAC_LOG_DEBUG, "Layer index out of bounds: %i", index);
        return NULL;
    }

    /* Lookup layer, allocating a new layer if necessary */
    guacenc_layer* layer = display->layers[index];
    if (layer == NULL) {

        /* Attempt to allocate layer */
        layer = guacenc_layer_alloc();
        if (layer == NULL) {
            guacenc_log(GUAC_LOG_DEBUG, "Layer allocation failed");
            return NULL;
        }

        /* Store layer within display for future retrieval / management */
        display->layers[index] = layer;

    }

    return layer;

}

int guacenc_display_free_layer(guacenc_display* display,
        int index) {

    /* Do not lookup / allocate if index is invalid */
    if (index < 0 || index > GUACENC_DISPLAY_MAX_LAYERS) {
        guacenc_log(GUAC_LOG_DEBUG, "Layer index out of bounds: %i", index);
        return 1;
    }

    /* Free layer (if allocated) */
    guacenc_layer_free(display->layers[index]);

    /* Mark layer as freed */
    display->layers[index] = NULL;

    return 0;

}

guacenc_display* guacenc_display_alloc() {
    return (guacenc_display*) calloc(1, sizeof(guacenc_display));
}

int guacenc_display_free(guacenc_display* display) {

    int i;

    /* Ignore NULL display */
    if (display == NULL)
        return 0;

    /* Free all buffers */
    for (i = 0; i < GUACENC_DISPLAY_MAX_BUFFERS; i++)
        free(display->buffers[i]);

    /* Free all layers */
    for (i = 0; i < GUACENC_DISPLAY_MAX_LAYERS; i++)
        guacenc_layer_free(display->layers[i]);

    /* Free all streams */
    for (i = 0; i < GUACENC_DISPLAY_MAX_STREAMS; i++)
        free(display->image_streams[i]);

    free(display);
    return 0;

}


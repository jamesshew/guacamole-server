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

#ifndef GUACENC_BUFFER_H
#define GUACENC_BUFFER_H

#include "config.h"

/**
 * The image and size storage for either a buffer (a Guacamole layer with a
 * negative index) or a layer (a Guacamole layer with a non-negative index).
 */
typedef struct guacenc_buffer {

    /**
     * The width of this buffer or layer, in pixels.
     */
    int width;

    /**
     * The height of this buffer or layer, in pixels.
     */
    int height;

    /**
     * The number of bytes in each row of image data.
     */
    int stride;

} guacenc_buffer;

/**
 * Allocates and initializes a new buffer object. This allocation is
 * independent of the Guacamole video encoder display; the allocated
 * guacenc_buffer will not automatically be associated with the active display.
 *
 * @return
 *     A newly-allocated and initialized guacenc_buffer, or NULL if allocation
 *     fails.
 */
guacenc_buffer* guacenc_buffer_alloc();

/**
 * Frees all memory associated with the given buffer object. If the buffer
 * provided is NULL, this function has no effect.
 *
 * @param buffer
 *     The buffer to free, which may be NULL.
 */
void guacenc_buffer_free(guacenc_buffer* buffer);

/**
 * Resizes the given buffer to the given dimensions, allocating or freeing
 * memory as necessary, and updating the buffer's width, height, and stride
 * properties.
 *
 * @param buffer
 *     The buffer to resize.
 *
 * @param width
 *     The new width of the buffer, in pixels.
 *
 * @param height
 *     The new height of the buffer, in pixels.
 *
 * @return
 *     Zero if the resize operation is successful, non-zero on error.
 */
int guacenc_buffer_resize(guacenc_buffer* buffer, int width, int height);

#endif


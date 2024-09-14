#ifndef OPAQUE_LINE_H

#define OPAQUE_LINE_H

/**
 * Draws an opaque line.
 * @param start_red The intensity of the red channel at the start of the line.
 *                  Behavior is undefined if NaN, infinity, negative infinity or
 *                  unable to be cast to int.
 * @param start_green The intensity of the green channel at the start of the
 *                    line.  Behavior is undefined if NaN, infinity, negative
 *                    infinity or unable to be cast to int.
 * @param start_blue The intensity of the blue channel at the start of the line.
 *                   Behavior is undefined if NaN, infinity, negative infinity
 *                   or unable to be cast to int.
 * @param start_row The number of rows between the top of the viewport and the
 *                  start of the line.  Behavior is undefined if NaN, infinity,
 *                  negative infinity or unable to be cast to int.
 * @param start_column The number of columns between the left of the viewport
 *                     and the start of the line.  Behavior is undefined if NaN,
 *                     infinity, negative infinity or unable to be cast to int.
 * @param start_depth The depth of the start of the line, where greater values
 *                    are further away.  Behavior is undefined if NaN, infinity,
 *                    negative infinity or unable to be cast to int.
 * @param end_red The intensity of the red channel at the end of the line.
 *                Behavior is undefined if NaN, infinity, negative infinity or
 *                unable to be cast to int.
 * @param end_green The intensity of the green channel at the end of the line.
 *                  Behavior is undefined if NaN, infinity, negative infinity or
 *                  unable to be cast to int.
 * @param end_blue The intensity of the blue channel at the end of the line.
 *                 Behavior is undefined if NaN, infinity, negative infinity or
 *                 unable to be cast to int.
 * @param end_row The number of rows between the top of the viewport and the end
 *                of the line.  Behavior is undefined if NaN, infinity, negative
 *                infinity or unable to be cast to int.
 * @param end_column The number of columns between the left of the viewport and
 *                   the end of the line.  Behavior is undefined if NaN,
 *                   infinity, negative infinity or unable to be cast to int.
 * @param end_depth The depth of the end of the line, where greater values are
 *                  further away.  Behavior is undefined if NaN, infinity,
 *                  negative infinity or unable to be cast to int.
 * @param viewport_rows The height of the viewport, in rows.  Behavior is
 *                      undefined if less than 1.
 * @param viewport_columns The width of the viewport, in columns.  Behavior is
 *                         undefined if less than 1.
 * @param viewport_reds The intensity of the red channel of each pixel within
 *                      the viewport, row-major, starting from the top left
 *                      corner.  Behavior is undefined if any are NaN, infinity,
 *                      negative infinity or unable to be cast to int.
 * @param viewport_greens The intensity of the red channel of each pixel within
 *                        the viewport, row-major, starting from the top left
 *                        corner.  Behavior is undefined if any are NaN,
 *                        infinity, negative infinity or unable to be cast to
 *                        int.
 * @param viewport_blues The intensity of the blue channel of each pixel within
 *                       the viewport, row-major, starting from the top left
 *                       corner.  Behavior is undefined if any are NaN,
 *                       infinity, negative infinity or unable to be cast to
 *                       int.
 * @param viewport_opacities The opacity of each pixel within the viewport,
 *                           row-major, starting from the top left corner, where
 *                           0 is fully transparent and 1 is fully opaque.
 *                           Behavior is undefined for values outside this
 *                           range, NaN, infinity or positive infinity.
 * @param viewport_depths The depth of each pixel within the viewport, where
 *                        greater values are further away, row-major, starting
 *                        from the top left corner.  Behavior is undefined if
 *                        any are NaN, infinity, negative infinity or unable to
 *                        be cast to int.
 */
void opaque_line(
    const float start_red,
    const float start_green,
    const float start_blue,
    const float start_row,
    const float start_column,
    const float start_depth,
    const float end_red,
    const float end_green,
    const float end_blue,
    const float end_row,
    const float end_column,
    const float end_depth,
    const int viewport_rows,
    const int viewport_columns,
    float *const viewport_reds,
    float *const viewport_greens,
    float *const viewport_blues,
    float *const viewport_opacities,
    float *const viewport_depths);

#endif

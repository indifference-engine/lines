#include <stdint.h>
#include "blended_line.h"

static void multiply_add_f32s_f32_f32s(
    const float *const multipliers,
    const float multiplicand,
    const float *const addends,
    float *const results,
    const int quantity)
{
  for (int index = 0; index < quantity; index++)
  {
    results[index] = multipliers[index] * multiplicand + addends[index];
  }
}

static void multiply_f32s_f32(
    const float *const multipliers,
    const float multiplicand,
    float *const products,
    const int quantity)
{
  for (int index = 0; index < quantity; index++)
  {
    products[index] = multipliers[index] * multiplicand;
  }
}

static float min_f32(const float a, const float b)
{
  return a < b ? a : b;
}

static void add_f32s_f32s(
    const float *const augends,
    const float *const addends,
    float *const sums,
    const int quantity)
{
  for (int index = 0; index < quantity; index++)
  {
    sums[index] = augends[index] + addends[index];
  }
}

static float linearly_interpolate_f32_f32_f32(
    const float start,
    const float end,
    const float progress,
    const float inverse_progress)
{
  return start * inverse_progress + end * progress;
}

void blended_line(
    const float start_opacity,
    const float start_red,
    const float start_green,
    const float start_blue,
    const float start_row,
    const float start_column,
    const float start_depth,
    const float end_opacity,
    const float end_red,
    const float end_green,
    const float end_blue,
    const float end_row,
    const float end_column,
    const float end_depth,
    const int viewport_rows,
    const int viewport_columns,
    float *const viewport_opacities,
    float *const viewport_reds,
    float *const viewport_greens,
    float *const viewport_blues,
    float *const viewport_depths)
{
  const int rounded_start_row = start_row < 0 ? ((int)start_row) - 1 : ((int)start_row);
  const int rounded_start_column = start_column < 0 ? ((int)start_column) - 1 : ((int)start_column);

  const int rounded_end_row = end_row < 0 ? ((int)end_row) - 1 : ((int)end_row);
  const int rounded_end_column = end_column < 0 ? ((int)end_column) - 1 : ((int)end_column);

  const int row_delta = rounded_end_row - rounded_start_row;
  const int absolute_row_delta = row_delta >= 0.0f ? row_delta : -row_delta;
  const int column_delta = rounded_end_column - rounded_start_column;
  const int absolute_column_delta = column_delta >= 0.0f ? column_delta : -column_delta;

  int start_primary_axis, end_primary_axis, indices_per_primary_axis, maximum_primary_axis, indices_per_secondary_axis, maximum_secondary_axis;
  float starts[6], ends[6];

  starts[1] = start_depth;
  starts[2] = start_opacity;
  starts[3] = start_red;
  starts[4] = start_green;
  starts[5] = start_blue;
  ends[1] = end_depth;
  ends[2] = end_opacity;
  ends[3] = end_red;
  ends[4] = end_green;
  ends[5] = end_blue;

  if (absolute_row_delta > absolute_column_delta)
  {
    start_primary_axis = start_row;
    end_primary_axis = end_row;
    indices_per_primary_axis = viewport_columns;
    maximum_primary_axis = viewport_rows;
    indices_per_secondary_axis = 1;
    maximum_secondary_axis = viewport_columns;
    starts[0] = start_column;
    ends[0] = end_column;
  }
  else
  {
    start_primary_axis = start_column;
    end_primary_axis = end_column;
    indices_per_primary_axis = 1;
    maximum_primary_axis = viewport_columns;
    indices_per_secondary_axis = viewport_columns;
    maximum_secondary_axis = viewport_rows;
    starts[0] = start_row;
    ends[0] = end_row;
  }

  int first_primary_axis, last_primary_axis;
  float per_pixels[6], *accumulators, progress_per_pixel;

  per_pixels[0] = ends[0] - starts[0];
  per_pixels[1] = ends[1] - starts[1];
  per_pixels[2] = ends[2] - starts[2];
  per_pixels[3] = ends[3] - starts[3];
  per_pixels[4] = ends[4] - starts[4];
  per_pixels[5] = ends[5] - starts[5];

  if (end_primary_axis > start_primary_axis)
  {
    first_primary_axis = start_primary_axis;
    last_primary_axis = end_primary_axis;
    accumulators = starts;
    progress_per_pixel = 1.0f / ((float)(end_primary_axis + 1 - start_primary_axis));
  }
  else
  {
    first_primary_axis = end_primary_axis;
    last_primary_axis = start_primary_axis;
    accumulators = ends;
    progress_per_pixel = 1.0f / ((float)(end_primary_axis - 1 - start_primary_axis));
  }

  multiply_f32s_f32(per_pixels, progress_per_pixel, per_pixels, 6);

  if (first_primary_axis < 0)
  {
    multiply_add_f32s_f32_f32s(per_pixels, -first_primary_axis, accumulators, accumulators, 4);
    first_primary_axis = 0;
  }

  last_primary_axis = min_f32(last_primary_axis, maximum_primary_axis);

  for (int primary_axis = first_primary_axis; primary_axis <= last_primary_axis; primary_axis++)
  {
    const int secondary_axis = accumulators[0];

    if (secondary_axis >= 0 && secondary_axis < maximum_secondary_axis)
    {
      const int index = primary_axis * indices_per_primary_axis + secondary_axis * indices_per_secondary_axis;

      if (accumulators[1] < viewport_depths[index])
      {
        const float source_opacity = accumulators[2];
        const float destination_opacity = viewport_opacities[index] * (1.0f - source_opacity);

        viewport_opacities[index] = source_opacity + destination_opacity;
        viewport_reds[index] = linearly_interpolate_f32_f32_f32(viewport_reds[index], accumulators[3], source_opacity, destination_opacity);
        viewport_greens[index] = linearly_interpolate_f32_f32_f32(viewport_greens[index], accumulators[4], source_opacity, destination_opacity);
        viewport_blues[index] = linearly_interpolate_f32_f32_f32(viewport_blues[index], accumulators[5], source_opacity, destination_opacity);
      }
    }

    add_f32s_f32s(accumulators, per_pixels, accumulators, 6);
  }
}

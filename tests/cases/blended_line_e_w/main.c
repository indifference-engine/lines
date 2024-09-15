#include "../../../src/blended_line.h"
#include "../../helpers/main.h"

int main(int argc, char **argv)
{
  (void)(argc);
  (void)(argv);

  float *const opacities = read_file("inputs/opacities.data");
  float *const reds = read_file("inputs/reds.data");
  float *const greens = read_file("inputs/greens.data");
  float *const blues = read_file("inputs/blues.data");
  float *const depths = read_file("inputs/depths.data");

  blended_line(
      0.6f, 0.3f, 0.8f, 0.1f,
      153.7f, 240.2f, 0.2f,
      0.4f, 0.7f, 0.2f, 0.9f,
      153.7f, 16.3f, 0.4f,
      192, 256, opacities, reds, greens, blues, depths);

  write_file(opacities, "outputs/actual/opacities.data");
  write_file(reds, "outputs/actual/reds.data");
  write_file(greens, "outputs/actual/greens.data");
  write_file(blues, "outputs/actual/blues.data");
  write_file(depths, "outputs/actual/depths.data");

  return 0;
}

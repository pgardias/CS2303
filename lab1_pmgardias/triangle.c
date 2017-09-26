#include <math.h>
#include <stdio.h>

int main() {
  // Init vars
  float A_X, A_Y, B_X, B_Y, C_X, C_Y;

  // Prompt and scan for input
  printf ("Enter the x- and y-coordinates of point A: ");
  scanf ("%f %f", &A_X, &A_Y);
  printf ("Enter the x- and y-coordinates of point B: ");
  scanf ("%f %f", &B_X, &B_Y);
  printf ("Enter the x- and y-coordinates of point C: ");
  scanf ("%f %f", &C_X, &C_Y);

  // Calculate lengths and circumference
  double len_AB = sqrt(((A_X - B_X) * (A_X - B_X)) + ((A_Y - B_Y) * (A_Y - B_Y)));
  double len_BC = sqrt(((B_X - C_X) * (B_X - C_X)) + ((B_Y - C_Y) * (B_Y - C_Y)));
  double len_CA = sqrt(((C_X - A_X) * (C_X - A_X)) + ((C_Y - A_Y) * (C_Y - A_Y)));
  double circ = (len_AB + len_BC + len_CA);
  double s = 0.5 * circ; // For usage in area calculation

  // Calculate area of triangle
  double area = sqrt(s * (s - len_AB) * (s - len_BC) * (s - len_CA));

  // Print results
  printf("Length of AB is %.2f\n", len_AB);
  printf("Length of BC is %.2f\n", len_BC);
  printf("Length of CA is %.2f\n", len_CA);
  printf("Circumference is %.2lf\n", circ);
  printf("Area is %.2lf\n", area);

  return 0;
}

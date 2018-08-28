#include <stdio.h>

int main ()
{
  for (int c = 0; c < 128; c++)
    {
      printf ("Nr: %d, Char: %c\n", c, c);
    }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bm_utils_pointer(void *pointer, char *message)
{
  if (pointer == NULL)
  {
    printf("%s\n", message);
    exit(-1);
  }
}

void bm_utils_copy_string(char *font, char *dst)
{
  bm_utils_pointer(font, "Error: Null pointer detected font");

  dst = (char *)malloc(sizeof(char) * strlen(font) + 2);

  bm_utils_pointer(dst, "Error: Could not allocate memory dst");

  strcpy(dst, font);
}

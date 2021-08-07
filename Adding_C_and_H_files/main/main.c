#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

void app_main(void)
{
  int result = moduleFunction(6, 3);
  printf("Result: %d\n", result);
}

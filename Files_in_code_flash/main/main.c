#include <stdio.h>

void app_main(void)
{
  extern const unsigned char indexHtml[] asm("_binary_index_html_start");
  printf("html = %s\n", indexHtml);
  extern const unsigned char sampleTxt[] asm("_binary_sample_txt_start");
  printf("txt = %s\n", sampleTxt);
  extern const unsigned char imgStart[] asm("_binary_ESP32_jpg_start");
  extern const unsigned char imgEnd[] asm("_binary_ESP32_jpg_end");

  const unsigned int imgSize = imgEnd - imgStart;
  printf("Image Size: %d\n", imgSize);

  printf("Hello world!\n");
}

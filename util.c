#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

_Noreturn void err( const char* msg, ... ) {
  va_list args;
  va_start (args, msg);
  vfprintf(stderr, msg, args);
  va_end (args);
  exit(1);
}


uint8_t** array_to_double_array(const uint8_t* pixel_array,uint64_t width, uint64_t height){
    uint8_t** marray = malloc ( sizeof(uint8_t*) * height);
    for (size_t i = 0; i < height;i++){
        marray[i] = malloc(sizeof(uint8_t)*width);
        for (size_t j = 0;j< width;j++){
            marray[i][j] = pixel_array[(width*i)+j];
        }
    }
    return marray;
}


uint8_t* array_to_pixel_array(uint8_t** pixel_array,uint64_t width,uint64_t height){
    uint8_t* array_pixel = malloc(sizeof(uint8_t)*width*height);
    for (size_t i = 0; i < height;i++){
        for (size_t j = 0;j< width;j++){
            array_pixel[width * i+j] = pixel_array[i][j];
        }
    }
    return array_pixel;
}

void print_double_pixel_array(struct pixel **array, uint32_t width,uint32_t height) {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            printf("Blue: %" PRIu8 " Green %" PRIu8 " Red %" PRIu8 "\n", array[i][j].b, array[i][j].g, array[i][j].r);
        }
    }
}
#ifndef _UTIL_H_
#define _UTIL_H_

_Noreturn void err( const char* msg, ... );
uint8_t** array_to_double_array(const uint8_t* pixel_array,uint64_t width, uint64_t height);
uint8_t* array_to_pixel_array(uint8_t** pixel_array,uint64_t width,uint64_t height);
void print_double_pixel_array(struct pixel **array, uint32_t width,uint32_t height);
#endif

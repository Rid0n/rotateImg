//
// Created by sergey on 20.01.2021.
//

#ifndef ROTATEIMG_IMAGE_H
#define ROTATEIMG_IMAGE_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>








struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct pixel* pixel_init(uint8_t b,uint8_t g,uint8_t r);
struct image image_init (uint64_t width,uint64_t height);
void free_pixel_array(struct pixel* array);
void free_pixel_double_array(struct pixel** array, uint32_t height);
void free_image(struct image* image);
struct pixel** pixel_array_to_double_array(struct pixel* pixel_array,uint64_t width, uint64_t height);
struct pixel* double_array_to_pixel_array(struct pixel** pixel_array,uint64_t width,uint64_t height);
struct pixel** init_double_array(uint32_t width,uint32_t height);
struct pixel** rotateCCW(const struct pixel** source, uint32_t width, uint32_t height);
struct pixel** rotateCW(const struct pixel** source, uint32_t width, uint32_t height);


#endif //ROTATEIMG_IMAGE_H

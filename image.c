//
// Created by sergey on 20.01.2021.
//

#include "image.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>




void swap_image_sizes(struct image* image){
    uint32_t a = image->height;
    image->height=image->width;
    image->width=a;

}


//malloc

struct pixel* pixel_init(uint8_t b,uint8_t g,uint8_t r) {
    struct pixel* pixel = malloc(sizeof(struct pixel));
    pixel->b=b;
    pixel->g=g;
    pixel->r=r;
    return pixel;
}

struct image image_init (uint64_t width,uint64_t height){
    struct pixel* pixel_array = malloc( sizeof(struct pixel) * width * height) ;

    /*
    for (size_t i = 0;i< width*height; i++){
        pixel_array[i] = pixel_init(data[i]);
    }
    */
    struct image image = { width,height,pixel_array };
    return image;

}
struct image image_with_padding_init(uint64_t width,uint64_t height,uint32_t padding){
    struct pixel* pixel_array = malloc( (sizeof(struct pixel) * width+padding) * height) ;

    /*
    for (size_t i = 0;i< width*height; i++){
        pixel_array[i] = pixel_init(data[i]);
    }
    */
    struct image image = { width,height,pixel_array };
    return image;

}
void free_pixel_array(struct pixel* array){
    free(array);
}
void free_pixel_double_array(struct pixel** array, uint32_t height){
    for (size_t i=0;i < height;i++){
        free_pixel_array(array[i]);
    }
    free(array);
}
void free_image(struct image* image) {
    free_pixel_array(image->data);
}

struct pixel** pixel_array_to_double_array(struct pixel* pixel_array,uint64_t width, uint64_t height){
    struct pixel** marray = malloc ( sizeof(struct pixel*) * height);
    for (size_t i = 0; i < height;i++){
        marray[i] = malloc(sizeof(struct pixel)*width);
        for (size_t j = 0;j< width;j++){
            marray[i][j] = pixel_array[(width*i)+j];
        }
    }
    return marray;
}


struct pixel** init_double_array(uint32_t width,uint32_t height){
    struct pixel** marray = malloc ( sizeof(struct pixel*) * height);
    for (size_t i = 0; i < height;i++){
        marray[i] = malloc(sizeof(struct pixel)*width);
    }
    return marray;
}
// clean
struct pixel* double_array_to_pixel_array(struct pixel** pixel_array,uint64_t width,uint64_t height){
    struct pixel* array_pixel = malloc(sizeof(struct pixel)*width*height);
    for (size_t i = 0; i < height;i++){
        for (size_t j = 0;j< width;j++){
            array_pixel[width * i+j] = pixel_array[i][j];
        }
    }
    return array_pixel;
}

struct pixel** rotateCW(struct pixel const** source, uint32_t width, uint32_t height) {

    struct pixel** rotated_array = init_double_array(height,width);
/*
    for (size_t i = 0; i < source->height * source->width; i++) {
        flipped[iHELLO] = source->data[HELLOi]; // formula is derived || no its not i am a silly stinky dummy
    }
*/

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            rotated_array[i][j] = source[j][width-i-1];
        }
    }


    return rotated_array;

}

struct pixel** rotateCCW(struct pixel const** source, uint32_t width, uint32_t height) {

    struct pixel** rotated_array = init_double_array(height,width);
/*
    for (size_t i = 0; i < source->height * source->width; i++) {
        flipped[iHELLO] = source->data[HELLOi];
    }
*/

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            rotated_array[i][j] = source[height-j-1][i];
        }
    }


    return rotated_array;

}
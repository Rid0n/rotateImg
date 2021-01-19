
#include <stdio.h>





#include "bmp.h"
#include "image.h"


int main() {


    char *path = "/home/sergey/CLionProjects/rotateImg/pic.bmp";
    char *savepath = "/home/sergey/CLionProjects/rotateImg/name.bmp";

    struct image image = {0};
    struct bmp_header header = {0};

    FILE *in = fopen(path, "rb");


    if (from_bmp(in, &image, &header)) {
        printf("something's up!");
        return 0;
    }


    struct pixel **original_image = pixel_array_to_double_array(image.data, image.width, image.height);


    struct pixel **rotated_image = rotateCW(original_image, image.width, image.height);


    image.data = double_array_to_pixel_array(rotated_image,image.height,image.width);
    header.biHeight=image.width;
    header.biWidth=image.height;




    if(to_bmp(path,header,image)) {
        printf("Couldn't save file!");

    }
    else {
        printf("Saved!");
    }

    free_image(&image);
    free_pixel_double_array(original_image,image.height);
    free_pixel_double_array(rotated_image,image.width);




    return 0;
}

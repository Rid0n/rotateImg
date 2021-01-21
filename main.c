
#include <stdio.h>


#include "bmp.h"
#include "image.h"
#include "util.h"
/*
void add_padding_to_image(struct image* image){
    uint32_t padding =  get_padding_bmp(image->width); // change
    for (size_t i = 0;i<(sizeof (struct pixel)*image->width+padding)*image->height;i++){
        if (!i%image->width){
            image->data[i] = 0x00;
        }
    }
    *image = image_with_padding_init(image->width,image->height,padding);

}*/

void usage() {
    fprintf(stderr, "Usage: ./rotate_image BMP_FILE_NAME\n");
}

int main(int argc, char** argv ) {
    if (argc != 2) usage();
    if (argc < 2) err("Not enough arguments \n" );
    if (argc > 2) err("Too many arguments \n" );

    char *path = argv[1];//"pic.bmp";


    struct image image = {0};

    FILE *in = open_bmp(path,"rb");

    from_bmp(in,&image);

    close_bmp(in);


    struct pixel **original_image = pixel_array_to_double_array(image.data, image.width, image.height);

    struct pixel **rotated_image = rotateCCW((const struct pixel**)original_image, image.width, image.height);

    swap_image_sizes(&image);

    image.data = double_array_to_pixel_array(rotated_image,image.width,image.height);

    FILE *out = open_bmp(path, "wb");

    if(to_bmp(out,image)) {
        printf("Couldn't save file!");

    }
    else {
        printf("Saved!");
    }
    close_bmp(out);


    free_image(&image);
    free_pixel_double_array(original_image,image.width);
    free_pixel_double_array(rotated_image,image.height);




    return 0;
}

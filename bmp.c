//
// Created by sergey on 20.01.2021.
//
#include "bmp.h"

#include <stdio.h>
#include <stdbool.h>



enum write_status to_bmp(const char* path,const struct bmp_header header,const struct image image) {
    FILE *out = fopen(path, "wb");
    if (!out) return WRITE_ERROR;
    fwrite(&header, sizeof(struct bmp_header), 1, out);
    fwrite(image.data, header.biSizeImage, 1, out);
    fclose(out);
    return WRITE_OK;
}

enum read_status from_bmp ( FILE* in, struct image* image,struct bmp_header* header){


    if (read_header( in, header ) ) {
        *image = image_init(header->biWidth,header->biHeight);
        bool num_read = fread(image->data, header->biSizeImage,1,in);
        if (!num_read) return READ_INVALID_BITS;
        fclose( in );
        return READ_OK;
    }
    else {
        return READ_INVALID_HEADER;
    }

}

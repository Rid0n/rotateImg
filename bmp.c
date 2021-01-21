//
// Created by sergey on 20.01.2021.
//
#include "bmp.h"

#include <stdio.h>
#include <stdbool.h>




#define PRI_SPECIFIER(e) (_Generic( (e), uint16_t : "%" PRIu16, uint32_t: "%" PRIu32, default: "NOT IMPLEMENTED" ))

#define PRINT_FIELD( t, name ) \
    fprintf( f, "%-17s: ",  # name ); \
    fprintf( f, PRI_SPECIFIER( header-> name ) , header-> name );\
    fprintf( f, "\n");


void bmp_header_print( struct bmp_header const* header, FILE* f ) {
    FOR_BMP_HEADER( PRINT_FIELD )
}

#define Type 0x4D42
#define Planes 1
#define BitCount 24
#define BITMAPFILEHEADER 14
#define Size 40

uint32_t get_padding_bmp(uint32_t width)
{
    return (4 - (width * sizeof(struct pixel)) % 4) % 4;
}



bool read_header( FILE* f, struct bmp_header* header ) {
    return fread( header, sizeof( struct bmp_header ), 1, f );
}

enum write_status to_bmp(FILE * file,const struct image image) { // remove header
    struct bmp_header new_header ={0};
    char paddingEssence[3] = {0};

    uint32_t padding = get_padding_bmp(image.width);//into one || width is passed

    create_header_bmp(&new_header,padding,image.width,image.height);
    bmp_header_print(&new_header,stdout);

    if (!file) return WRITE_ERROR;
    if(!fwrite(&new_header, sizeof(struct bmp_header), 1, file)) return WRITE_ERROR;

    for (size_t i =0;i<image.height;++i){
      if (fwrite(image.data+i*image.width,sizeof(struct pixel),image.width,file) != image.width) return WRITE_ERROR;
     if (!fwrite(paddingEssence,padding,1,file) && padding) return WRITE_ERROR;
    }
   // fwrite(image.data, new_header.biSizeImage, 1, file);

    return WRITE_OK;
}
//byte_image_with_padding(&image)
enum read_status from_bmp( FILE* in, struct image* image){
    struct bmp_header header = {0};
    //padding
    if (read_header( in, &header ) ) {
        *image = image_init(header.biWidth,header.biHeight);
        if (header.bfType!=Type) return READ_INVALID_SIGNATURE;
            if (fseek(in, header.bOffBits, SEEK_SET) != 0) return READ_INVALID_BITS;

        uint32_t padding = get_padding_bmp(header.biWidth);
        for (size_t i=0;i<image->height;i++){
            if (fread(image->data + i * image->width, sizeof (struct pixel), image->width, in) < sizeof(struct pixel)) return READ_INVALID_BITS;
            if (fseek(in, padding, SEEK_CUR) != 0) return READ_INVALID_BITS;

        }
        //bool num_read = fread(image->data, sizeof(struct pixel)*header.biWidth*header.biHeight,1,in);
        //if (!num_read) return READ_INVALID_BITS;
        return READ_OK;
    }
    else {
        return READ_INVALID_HEADER;
    }

}
void close_bmp(FILE* file){
    fclose(file);
}
FILE* open_bmp(const char* path, const char* mode){
    return fopen(path,mode);
}

void create_header_bmp(struct bmp_header* h,uint32_t padding,uint32_t biWidth,uint32_t biHeight){
    h->bfType=Type;
    h->biSizeImage=(sizeof(struct pixel)*biWidth+padding)*biHeight;
    h->bfileSize=h->biSizeImage+BITMAPFILEHEADER+Size;
    h->biSize=Size;
    h->biBitCount=BitCount;
    h->biPlanes=Planes;
    h->biHeight=biHeight;
    h->biWidth=biWidth;
    h->bOffBits=BITMAPFILEHEADER+Size;

}



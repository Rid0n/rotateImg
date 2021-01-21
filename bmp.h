//
// Created by sergey on 20.01.2021.
//

#ifndef ROTATEIMG_BMP_H
#define ROTATEIMG_BMP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "image.h"


enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR=1

};

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE=1,
    READ_INVALID_BITS=2,
    READ_INVALID_HEADER=3

};

#define FOR_BMP_HEADER( FOR_FIELD ) \
        FOR_FIELD( uint16_t,bfType)\
        FOR_FIELD( uint32_t,bfileSize)\
        FOR_FIELD( uint32_t,bfReserved)\
        FOR_FIELD( uint32_t,bOffBits)\
        FOR_FIELD( uint32_t,biSize)\
        FOR_FIELD( uint32_t,biWidth)\
        FOR_FIELD( uint32_t,biHeight)\
        FOR_FIELD( uint16_t,biPlanes)\
        FOR_FIELD( uint16_t,biBitCount)\
        FOR_FIELD( uint32_t,biCompression)\
        FOR_FIELD( uint32_t,biSizeImage)\
        FOR_FIELD( uint32_t,biXPelsPerMeter)\
        FOR_FIELD( uint32_t,biYPelsPerMeter)\
        FOR_FIELD( uint32_t,biClrUsed)\
        FOR_FIELD( uint32_t,biClrImportant)

#define DECLARE_FIELD( t, n ) t n ;

struct __attribute__((packed)) bmp_header
{
    FOR_BMP_HEADER( DECLARE_FIELD )
};
uint32_t get_padding_bmp(uint32_t width);
void create_header_bmp(struct bmp_header* h,uint32_t padding,uint32_t biWidth,uint32_t biHeight);
void bmp_header_print( struct bmp_header const* header, FILE* f );
bool read_header( FILE* f, struct bmp_header* header );
bool read_header_from_file( const char* filename, struct bmp_header* header );
enum write_status to_bmp(FILE * file,const struct image image);
enum read_status from_bmp ( FILE* in, struct image* image);
FILE* open_bmp(const char* path, const char* mode);
void close_bmp(FILE* file);


#endif //ROTATEIMG_BMP_H

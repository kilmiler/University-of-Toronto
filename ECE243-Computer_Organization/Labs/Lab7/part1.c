//#include "address_map_arm.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void draw_line(int x0, int y0, int x1, int y1, int line_color);
void swap(int* sp1, int* sp2);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();

volatile int pixel_buffer_start; // global variable

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();
    
    for(int j=0; j<62; j++){
        draw_line(0, j, 319, j, 0x2E1F); //Sky
    }

    for(int i=62; i<65; i++){
        draw_line(0, i, 319, i, 0xFFFF); //White
    }

    for(int j=65; j<135; j++){
        draw_line(0, j, 319, j, 0x6EFE); //blue1
    }

    
    for(int i=0; i<321 ; i=i+20){
        draw_line(1+i, 134, 14+i, 134, 0x2E9D); //blue2
        draw_line(3+i, 133, 12+i, 133, 0x2E9D); //blue2
        draw_line(5+i, 132, 10+i, 132, 0x2E9D); //blue2
    }
    for(int j=135; j<185; j++){
        draw_line(0, j, 319, j, 0x2E9D); //blue2
    }

    for(int i=0; i<321 ; i=i+20){
        draw_line(5+i, 184, 18+i, 184, 0x05FB); //blue3
        draw_line(7+i, 183, 16+i, 183, 0x05FB); //blue3
        draw_line(9+i, 182, 14+i, 182, 0x05FB); //blue3
    }
    for(int j=185; j<240; j++){
        draw_line(0, j, 319, j, 0x05FB); //blue3
    }

    draw_cloud(180, 0, 188, 0);
    
    
    draw_cloud(290, 25, 298, 25);
    

    draw_line(50, 10, 58, 10, 0); //Black

    draw_line(49, 11, 60, 11, 0); //Black
    draw_line(50, 11, 58, 11, 0xFFFF); //White

    draw_line(48, 12, 61, 12, 0); //Black
    draw_line(49, 12, 59, 12, 0xFFFF); //White

    draw_line(47, 13, 62, 13, 0); //Black
    draw_line(48, 13, 60, 13, 0xFFFF); //White

    draw_line(46, 14, 62, 14, 0); //Black
    draw_line(47, 14, 61, 14, 0xFFFF); //White

    draw_line(39, 15, 43, 15, 0); //Black
    draw_line(45, 15, 45, 15, 0); //Black
    draw_line(62, 15, 62, 15, 0); //Black
    draw_line(46, 15, 61, 15, 0xFFFF); //White

    draw_line(37, 16, 68, 16, 0); //Black
    draw_line(39, 16, 42, 16, 0xFFFF); //White
    draw_line(46, 16, 62, 16, 0xFFFF); //White

    draw_line(36, 17, 70, 17, 0); //Black
    draw_line(37, 17, 68, 17, 0xFFFF); //White

    draw_line(35, 18, 71, 18, 0); //Black
    draw_line(36, 18, 70, 18, 0xFFFF); //White

    draw_line(34, 19, 72, 19, 0); //Black
    draw_line(35, 19, 71, 19, 0xFFFF); //White

    draw_line(34, 20, 73, 20, 0); //Black
    draw_line(35, 20, 72, 20, 0xFFFF); //White

    draw_line(34, 21, 74, 21, 0); //Black
    draw_line(35, 21, 73, 21, 0xFFFF); //White

    draw_line(34, 22, 74, 22, 0); //Black
    draw_line(35, 22, 73, 22, 0xFFFF); //White

    draw_line(34, 23, 75, 23, 0); //Black
    draw_line(35, 23, 74, 23, 0xFFFF); //White

    draw_line(34, 24, 76, 24, 0); //Black
    draw_line(35, 24, 74, 24, 0xFFFF); //White

    draw_line(34, 25, 76, 25, 0); //Black
    draw_line(36, 25, 75, 25, 0xFFFF); //White

    draw_line(35, 26, 76, 26, 0); //Black
    draw_line(36, 26, 75, 26, 0xFFFF); //White

    draw_line(35, 27, 76, 27, 0); //Black
    draw_line(37, 27, 75, 27, 0xFFFF); //White

    draw_line(36, 28, 76, 28, 0); //Black
    draw_line(38, 28, 74, 28, 0xFFFF); //White

    draw_line(36, 29, 75, 29, 0); //Black
    draw_line(37, 29, 74, 29, 0xFFFF); //White

    draw_line(35, 30, 75, 30, 0); //Black
    draw_line(37, 30, 73, 30, 0xFFFF); //White

    draw_line(35, 31, 74, 31, 0); //Black
    draw_line(36, 31, 72, 31, 0xFFFF); //White

    draw_line(35, 32, 73, 32, 0); //Black
    draw_line(36, 32, 71, 32, 0xFFFF); //White

    draw_line(35, 33, 72, 33, 0); //Black
    draw_line(36, 33, 70, 33, 0xFFFF); //White

    draw_line(35, 34, 71, 34, 0); //Black
    draw_line(37, 34, 67, 34, 0xFFFF); //White

    draw_line(36, 35, 68, 35, 0); //Black
    draw_line(37, 35, 46, 35, 0xFFFF); //White
    draw_line(48, 35, 63, 35, 0xFFFF); //White

    draw_line(36, 36, 64, 36, 0); //Black
    draw_line(38, 36, 44, 36, 0xFFFF); //White
    draw_line(49, 36, 62, 36, 0xFFFF); //White

    draw_line(37, 37, 39, 37, 0); //Black
    draw_line(44, 37, 45, 37, 0); //Black
    draw_line(48, 37, 48, 37, 0); //Black
    draw_line(62, 37, 63, 37, 0); //Black
    draw_line(39, 37, 43, 37, 0xFFFF); //White
    draw_line(49, 37, 61, 37, 0xFFFF); //White

    draw_line(38, 38, 43, 38, 0); //Black
    draw_line(49, 38, 49, 38, 0); //Black
    draw_line(61, 38, 62, 38, 0); //Black
    draw_line(50, 38, 60, 38, 0xFFFF); //White

    draw_line(50, 39, 61, 39, 0); //Black
    draw_line(51, 39, 59, 39, 0xFFFF); //White

    draw_line(51, 40, 60, 40, 0); //Black
    draw_line(52, 40, 57, 40, 0xFFFF); //White

    draw_line(52, 41, 57, 41, 0); //Black

    return 0;
}


void draw_cloud(int x0, int y0, int x1, int y1){
    draw_line(x0, y0, x1, y0, 0); //Black

    draw_line(x0-1, y0+1, x1+2, y0+1, 0); //Black
    draw_line(x0, y0+1, x1, y0+1, 0xFFFF); //White

    draw_line(x0-2, y0+2, x1+3, y0+2, 0); //Black
    draw_line(x0-1, y0+2, x1+1, y0+2, 0xFFFF); //White

    draw_line(x0-3, y0+3, x1+4, y0+3, 0); //Black
    draw_line(x0-2, y0+3, x1+2, y0+3, 0xFFFF); //White

    draw_line(x0-4, y0+4, x1+4, y0+4, 0); //Black
    draw_line(x0-3, y0+4, x1+3, y0+4, 0xFFFF); //White

    draw_line(x0-11, y0+5, x1-15, y0+5, 0); //Black
    draw_line(x0-5, y0+5, x1-13, y0+5, 0); //Black
    draw_line(x0+12, y0+5, x1+4, y0+5, 0); //Black
    draw_line(x0-4, y0+5, x1+3, y0+5, 0xFFFF); //White

    draw_line(x0-13, y0+6, x1+10, y0+6, 0); //Black
    draw_line(x0-11, y0+6, x1-16, y0+6, 0xFFFF); //White
    draw_line(x0-4, y0+6, x1+4, y0+6, 0xFFFF); //White

    draw_line(x0-14, y0+7, x1+12, y0+7, 0); //Black
    draw_line(x0-13, y0+7, x1+10, y0+7, 0xFFFF); //White

    draw_line(x0-15, y0+8, x1+13, y0+8, 0); //Black
    draw_line(x0-14, y0+8, x1+12, y0+8, 0xFFFF); //White

    draw_line(x0-16, y0+9, x1+14, y0+9, 0); //Black
    draw_line(x0-15, y0+9, x1+13, y0+9, 0xFFFF); //White

    draw_line(x0-16, y0+10, x1+15, y0+10, 0); //Black
    draw_line(x0-15, y0+10, x1+14, y0+10, 0xFFFF); //White

    draw_line(x0-16, y0+11, x1+16, y0+11, 0); //Black
    draw_line(x0-15, y0+11, x1+15, y0+11, 0xFFFF); //White

    draw_line(x0-16, y0+12, x1+16, y0+12, 0); //Black
    draw_line(x0-15, y0+12, x1+15, y0+12, 0xFFFF); //White

    draw_line(x0-16, y0+13, x1+17, y0+13, 0); //Black
    draw_line(x0-15, y0+13, x1+16, y0+13, 0xFFFF); //White

    draw_line(x0-16, y0+14, x1+18, y0+14, 0); //Black
    draw_line(x0-15, y0+14, x1+16, y0+14, 0xFFFF); //White

    draw_line(x0-16, y0+15, x1+18, y0+15, 0); //Black
    draw_line(x0-14, y0+15, x1+17, y0+15, 0xFFFF); //White

    draw_line(x0-15, y0+16, x1+18, y0+16, 0); //Black
    draw_line(x0-14, y0+16, x1+17, y0+16, 0xFFFF); //White

    draw_line(x0-15, y0+17, x1+18, y0+17, 0); //Black
    draw_line(x0-13, y0+17, x1+17, y0+17, 0xFFFF); //White

    draw_line(x0-14, y0+18, x1+18, y0+18, 0); //Black
    draw_line(x0-12, y0+18, x1+16, y0+18, 0xFFFF); //White

    draw_line(x0-14, y0+19, x1+17, y0+19, 0); //Black
    draw_line(x0-13, y0+19, x1+16, y0+19, 0xFFFF); //White

    draw_line(x0-15, y0+20, x1+17, y0+20, 0); //Black
    draw_line(x0-13, y0+20, x1+15, y0+20, 0xFFFF); //White

    draw_line(x0-15, y0+21, x1+16, y0+21, 0); //Black
    draw_line(x0-14, y0+21, x1+14, y0+21, 0xFFFF); //White

    draw_line(x0-15, y0+22, x1+15, y0+22, 0); //Black
    draw_line(x0-14, y0+22, x1+13, y0+22, 0xFFFF); //White

    draw_line(x0-15, y0+23, x1+14, y0+23, 0); //Black
    draw_line(x0-14, y0+23, x1+12, y0+23, 0xFFFF); //White

    draw_line(x0-15, y0+24, x1+13, y0+24, 0); //Black
    draw_line(x0-13, y0+24, x1+9, y0+24, 0xFFFF); //White

    draw_line(x0-14, y0+25, x1+10, y0+25, 0); //Black
    draw_line(x0-13, y0+25, x1-12, y0+25, 0xFFFF); //White
    draw_line(x0-2, y0+25, x1+5, y0+25, 0xFFFF); //White

    draw_line(x0-14, y0+26, x1+6, y0+26, 0); //Black
    draw_line(x0-12, y0+26, x1-14, y0+26, 0xFFFF); //White
    draw_line(x0-1, y0+26, x1+4, y0+26, 0xFFFF); //White

    draw_line(x0-13, y0+27, x1-19, y0+27, 0); //Black
    draw_line(x0-6, y0+27, x1-13, y0+27, 0); //Black
    draw_line(x0-2, y0+27, x1-10, y0+27, 0); //Black
    draw_line(x0+12, y0+27, x1+5, y0+27, 0); //Black
    draw_line(x0-11, y0+27, x1-15, y0+27, 0xFFFF); //White
    draw_line(x0-1, y0+27, x1+3, y0+27, 0xFFFF); //White

    draw_line(x0-12, y0+28, x1-15, y0+28, 0); //Black
    draw_line(x0-1, y0+28, x1-9, y0+28, 0); //Black
    draw_line(x0+11, y0+28, x1+4, y0+28, 0); //Black
    draw_line(x0, y0+28, x1+2, y0+28, 0xFFFF); //White

    draw_line(x0, y0+29, x1+3, y0+29, 0); //Black
    draw_line(x0+1, y0+29, x1+1, y0+29, 0xFFFF); //White

    draw_line(x0+1, y0+30, x1+2, y0+30, 0); //Black
    draw_line(x0+2, y0+30, x1-1, y0+30, 0xFFFF); //White

    draw_line(x0+2, y0+31, x1-1, y0+31, 0); //Black
}


void draw_line (int x0, int y0, int x1, int y1, int line_color) {
    bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    
    if(is_steep){
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    if(x0 > x1){
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;

    int y_step;
    if(y0 < y1){
        y_step = 1;
    }else{
        y_step = -1;
    }
    
    int x;
    for(x = x0; x < x1+1; x++){
        if(is_steep){
            plot_pixel(y, x, line_color);
        }else{
            plot_pixel(x, y, line_color);
        }

        error = error + deltay;
        if(error >= 0){
            y = y + y_step;
            error = error - deltax;
        }
    } 
}

void swap(int* sp1, int* sp2){
    int temp = *sp1;
    *sp1 = *sp2;
    *sp2 = temp;
}

void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void clear_screen(){
    int blank = 0; //(00000 000000 00000)2 for Black color

    for(int x=0; x<320; x++){
        for(int y=0; y<240; y++){
            plot_pixel(x, y, blank);
        }
    }

}
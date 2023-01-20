#include "address_map_arm.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void draw_line(int x0, int y0, int x1, int y1, int line_color);
void swap(int* sp1, int* sp2);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void Check_sBit();

volatile int pixel_buffer_start; // global variable
volatile int* pixel_ctrl_ptr = (int *)0xFF203020;
volatile int* status = (int *)0xFF20302C;

int main(void)
{
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    bool down = true;
    int black = 0; //(00000 000000 00000)2 for Black color
    int red = 0xF800; //Made line Red color
    int y = 0;

    clear_screen();
    //endless loop
    while(true){

        if(down){
            y = y + 1; //go down 1
            draw_line(0, y, 319, y, red);
            draw_line(0, y-1, 319, y-1, black);
            //when it reaches bottom (UP)
            if(y == 239){
                down = false;
            }
        }else{
            y = y - 1; //go up 1
            draw_line(0, y, 319, y, red);
            draw_line(0, y+1, 319, y+1, black);
            //when it reaches top (DOWN)
            if(y == 0){
                down = true;
            }
        }

        Check_sBit();
    }

    return 0;
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
    int blank = 0; //(00000 000000 00000)2 for white color

    for(int x=0; x<320; x++){
        for(int y=0; y<240; y++){
            plot_pixel(x, y, blank);
        }
    }

}

void Check_sBit(){
    *pixel_ctrl_ptr = 1; //Writing 1 to Buffer reg sets S=1

    while( ((*status) & 0x1) != 0){
        //wait until S=0 //S=0 when swap occured
    }
}

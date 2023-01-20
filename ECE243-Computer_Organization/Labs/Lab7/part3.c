#include "address_map_arm.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void draw_line(int x0, int y0, int x1, int y1, int line_color);
void swap(int* sp1, int* sp2);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void wait_for_vsync();

volatile int pixel_buffer_start; // global variable
volatile int* pixel_ctrl_ptr = (int *)0xFF203020;
volatile int* status = (int *)0xFF20302C;

typedef struct rectangle{
    int X;
    int Y;
    int dX;
    int dY;
    int color;
}Rec;

void plotSquare(Rec rect);

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)
    srand(time(0));
    Rec rect[8];

    for(int i=0; i<8; i++){
        //size will be 5x5
        rect[i].X = rand() % 316; //0 to 315
        rect[i].Y = rand() % 236; //0 to 235
        rect[i].dX = rand() % 2 * 2 - 1; //-1 or 1
        rect[i].dY = rand() % 2 * 2 - 1; //-1 to 1
        rect[i].color = 0x001F; //Blue Color
    }

    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the 
                                        // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer

    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        clear_screen();

        //Drawing Lines
        draw_line(rect[7].X+2, rect[7].Y+2, rect[0].X+2, rect[0].Y+2, 0xF800);
        for(int i=0; i<7; i++){
            draw_line(rect[i].X+2, rect[i].Y+2, rect[i+1].X+2, rect[i+1].Y+2, 0xF800);
        }
        //Then Draw Boxes (so that boxes are on top of lines)
        for(int i=0; i<8; i++){
            plotSquare(rect[i]);
        }

        //Code for updating the locations of boxes
        for(int i=0; i<8; i++){
            rect[i].X = rect[i].X + rect[i].dX;
            if(rect[i].X > 315){
                rect[i].X = 315;
                rect[i].dX = - rect[i].dX;
            }else if(rect[i].X < 0){
                rect[i].X = 0;
                rect[i].dX = -rect[i].dX;
            }

            rect[i].Y = rect[i].Y + rect[i].dY;
            if(rect[i].Y > 235){
                rect[i].Y = 235;
                rect[i].dY = - rect[i].dY;
            }else if(rect[i].Y < 0){
                rect[i].Y = 0;
                rect[i].dY = -rect[i].dY;
            }
        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
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
    int x;
    int y;
    int blank = 0; //(00000 000000 00000)2 for white color

    for(x=0; x<320; x++){
        for(y=0; y<240; y++){
            plot_pixel(x, y, blank);
        }
    }

}

void wait_for_vsync(){
    *pixel_ctrl_ptr = 1; //Writing 1 to Buffer reg sets S=1

    while( ((*status) & 0x1) != 0){
        //wait until S=0 //S=0 when swap occured
    }
}

void plotSquare(Rec rect){
    for(int i=0; i<5; i++){
        draw_line(rect.X, rect.Y + i, rect.X + 4, rect.Y + i, rect.color); //5x5 Square
    }
}

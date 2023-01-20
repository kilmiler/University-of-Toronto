//#include "address_map_arm.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//colours
short int orange = 0xFCA0;
short int black = 0x0000;
short int white = 0xFFFF;
short int light_brown = 0xD4C4;
short int dark_brown = 0x7AC2;
short int beige = 0xFF16;
short int grey = 0x9CF3;
short int dark_red = 0x9841;

//drawing functions
void draw_background();
void draw_water();
void draw_cloud(int x0, int y0, int x1, int y1);
void draw_seaweeds();
void draw_seaweed(int x, int y);
void draw_sand();
void draw_bubbles(int x, int y);
void draw_bubble_s(int x, int y);
void draw_bubble_b(int x, int y);
void draw_fishL(int x, int y);
void draw_fishR(int x, int y);
void draw_fish_eye(int x, int y);
void draw_fishing_boat(int x, int y);
void draw_GAMEOVER(int x, int y);
void draw_YOUWIN(int x, int y);
void draw_G(int x, int y);
void draw_A(int x, int y);
void draw_M(int x, int y);
void draw_E(int x, int y);
void draw_O(int x, int y);
void draw_V(int x, int y);
void draw_R(int x, int y);
void draw_Y(int x, int y);
void draw_U(int x, int y);
void draw_W(int x ,int y);
void draw_I(int x, int y);
void draw_N(int x, int y);

//drawing helper functions
void draw_line(int x0, int y0, int x1, int y1, int line_color);
void draw_line1(int x, int y, int len, short int color, bool is_vertical); //line width 1 pix
void draw_line2(int x, int y, int len, short int color, bool is_vertical); //line width 2 pix
void draw_line4(int x, int y, int len, short int color, bool is_vertical);
void draw_stair(int x, int y, int len, short int color, bool is_rightUP);


void swap(int* sp1, int* sp2);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void draw_all_white();
void wait_for_vsync();

//global variables
bool isWinner = false;
bool isGameover = false;
int speed_cnt = 1;
int bubble_cnt = 0;
int score_cnt = 0;
int death_cnt = 0;
int game_cnt = 0;

//address pointers
volatile int pixel_buffer_start; // global variable
volatile int* pixel_ctrl_ptr = (int *)0xFF203020;
volatile int* status = (int *)0xFF20302C;
volatile int *LEDR_ptr = (int *)0xFF200000;
volatile int *KEY_ptr = (int *)0xFF20005C;
volatile int *SW_ptr = (int *)0xFF200040;
volatile int *HEX_ptr = (int *)0xFF200020;

//structures
typedef struct Hook{
    int X;
    int Y;
    int dY;
    int color;
    int hook_zoneX[12];
    int hook_zoneY[12];
}Hook;

typedef struct Fish
{
    short int X;
    short int Y;
    short int dX;
    bool isLeft; //fish facing left or right
    bool isAlive;
    bool bubbleDrawn;
    int death_zoneX[59];
    int death_zoneY[59];
    
}Fish;

//plothook function
void plotHook(Hook Hook);

int main(void){
    srand(time(0));
    //declare Hook
    Hook Hook[1];
    Hook[0].X = 160;
    Hook[0].Y = 65;
    Hook[0].dY = 4;
    Hook[0].color = dark_red;
    
    // declare Fish
    Fish fish[5];
    fish[0].X = rand() % 250 + 35;//0 - 249 //35 - 284
    fish[0].Y = 89;
    fish[0].dX = rand() % 3 - 4; //-4 to -2
    fish[0].isLeft = true;
    fish[0].isAlive = true;
    fish[0].bubbleDrawn = false;
    
    fish[1].X = rand() % 250 + 35;
    fish[1].Y = 121;
    fish[1].dX = rand() % 3 + 2; // 2 to 4
    fish[1].isLeft = false;
    fish[1].isAlive = true;
    fish[1].bubbleDrawn = false;
    
    fish[2].X = rand() % 250 + 35;
    fish[2].Y = 153;
    fish[2].dX = rand() % 3 - 4;
    fish[2].isLeft = true;
    fish[2].isAlive = true;
    fish[2].bubbleDrawn = false;
    
    fish[3].X = rand() % 250 + 35;
    fish[3].Y = 185;
    fish[3].dX = rand() % 3 + 2; // 2 to 4
    fish[3].isLeft = false;
    fish[3].isAlive = true;
    fish[3].bubbleDrawn = false;
    
    fish[4].X = rand() % 250 + 35;
    fish[4].Y = 217;
    fish[4].dX = rand() % 3 - 4;
    fish[4].isLeft = true;
    fish[4].isAlive = true;
    fish[4].bubbleDrawn = false;
    
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
        //clear_screen();
        if(!isWinner && !isGameover){
            draw_background();
        }
        
        //display “YOU WIN” or “GAME OVER”
        if(isWinner){
            draw_all_white();
            draw_YOUWIN(54,105);
        }
        else if(isGameover){
            draw_all_white();
            draw_GAMEOVER(97,88);
        }
        
        //Updating Score
        if(score_cnt == 0){
            *HEX_ptr = 0x0000003F;
        }else if(score_cnt == 1){
            *HEX_ptr = 0x00000006;
        }else if(score_cnt == 2){
            *HEX_ptr = 0x0000005B;
        }else if(score_cnt == 3){
            *HEX_ptr = 0x0000004F;
        }else if(score_cnt == 4){
            *HEX_ptr = 0x00000066;
        }else if(score_cnt == 5){
            *HEX_ptr = 0x0000006D;
        }
        
        //saving hook_zone : when fish meets this zone -> fish dies
        for(int i = 0; i < 4; i++){
            Hook[0].hook_zoneX[i] = Hook[0].X-i;
            Hook[0].hook_zoneY[i] = Hook[0].Y+4;
        }
        for(int i = 0; i < 4; i++){
            Hook[0].hook_zoneX[i+4] = Hook[0].X-i;
            Hook[0].hook_zoneY[i+4] = Hook[0].Y+4;
        }
        for(int i = 0; i < 4; i++){
            Hook[0].hook_zoneX[i+8] = Hook[0].X-i;
            Hook[0].hook_zoneY[i+8] = Hook[0].Y+4;
        }
        
        //saving fish death_zone : when hook meets this zone -> fish dies
        
        for(int i = 0; i < 5; i++){
            if(fish[i].isLeft == true){
                fish[i].death_zoneX[0] = fish[i].X;
                fish[i].death_zoneY[0] = fish[i].Y;
                
                fish[i].death_zoneX[1] = fish[i].X;
                fish[i].death_zoneY[1] = fish[i].Y+1;
                
                fish[i].death_zoneX[2] = fish[i].X;
                fish[i].death_zoneY[2] = fish[i].Y+2;
                
                int cnt = 3;
                
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y-2;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y-1;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+1;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+2;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+3;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X+1+j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+4;
                    cnt++;
                }
                
            } //if
            else if(fish[i].isLeft == false){
                fish[i].death_zoneX[0] = fish[i].X;
                fish[i].death_zoneY[0] = fish[i].Y;
                
                fish[i].death_zoneX[1] = fish[i].X;
                fish[i].death_zoneY[1] = fish[i].Y+1;
                
                fish[i].death_zoneX[2] = fish[i].X;
                fish[i].death_zoneY[2] = fish[i].Y+2;
                
                int cnt = 3;
                
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y-2;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y-1;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+1;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+2;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+3;
                    cnt++;
                }
                for(int j = 0; j < 8; j++){
                    fish[i].death_zoneX[cnt] = fish[i].X-1-j;
                    fish[i].death_zoneY[cnt] = fish[i].Y+4;
                    cnt++;
                }
            }
        } //for
        
        
        //checking if the hook meets the fish
        for(int i = 0; i < 5; i++){ //checking all the fish
            if(fish[i].isAlive == true){
                for(int j = 0; j < 59; j++){ //checking all death_zone
                    for(int k = 0; k < 12; k++){ //checking all hook_zone
                        if(fish[i].death_zoneX[j] == Hook[0].hook_zoneX[k] && fish[i].death_zoneY[j] == Hook[0].hook_zoneY[k]){
                            fish[i].isAlive = false; //fish meets hook -> dead
                            bubble_cnt = 0;
                        }
                    }
                }
            }
        }
        
        //Check Number of fish Alive to Display Score
        death_cnt = 0;
        for(int i = 0; i < 5; i++){
            if(fish[i].isAlive == false){
                death_cnt++;
            }
        }
        score_cnt = death_cnt;
        
        //Draw Fish
        if(!isWinner && !isGameover){
            for(int i = 0; i < 5; i++){
                if(fish[i].isLeft == true && fish[i].isAlive == true){
                    draw_fishL(fish[i].X, fish[i].Y);
                }
                else if(fish[i].isLeft == false && fish[i].isAlive == true){
                    draw_fishR(fish[i].X, fish[i].Y);
                }
            }
        }
        
        //Draw Bubble on Spot of Deleted Fish
        for(int i = 0; i < 5; i++){
            if(fish[i].isAlive == false && fish[i].bubbleDrawn == false){
                if(bubble_cnt == 0){
                    draw_bubbles(fish[i].X, fish[i].Y+5);
                    bubble_cnt = 1;
                }else if(bubble_cnt == 1){
                    draw_bubbles(fish[i].X+5, fish[i].Y);
                    bubble_cnt = 2;
                }else if(bubble_cnt == 2){
                    draw_bubbles(fish[i].X, fish[i].Y-5);
                    bubble_cnt = 3;
                    fish[i].bubbleDrawn = true;
                }
            }
        }
        
        if(!isWinner && !isGameover){
            //Drawing Rope
            draw_line(Hook[0].X, 62, Hook[0].X, Hook[0].Y, grey);
            //Then Draw Hook (so that Hook is on top of Rope)
            plotHook(Hook[0]);
        }
        
        //Code for updating speed of Hook
        unsigned SW_val = (unsigned int) *SW_ptr;// read SW0 value
        if(SW_val == 0 && Hook[0].Y == 65){
            Hook[0].Y = 65;
            if(speed_cnt == 0){
                Hook[0].dY = 2;
            }else if(speed_cnt == 1){
                Hook[0].dY = 4;
            }else if(speed_cnt == 2){
                Hook[0].dY = 8;
            }
        }else if(SW_val == 1 && Hook[0].Y == 231){
            Hook[0].Y = 231;
            if(speed_cnt == 0){
                Hook[0].dY = -2;
            }else if(speed_cnt == 1){
                Hook[0].dY = -4;
            }else if(speed_cnt == 2){
                Hook[0].dY = -8;
            }
        }
        
        
        if(*KEY_ptr == 0b0001) { //KEY0: slow
            speed_cnt = 0;
            if(Hook[0].dY > 0){
                Hook[0].dY = 2;
            }else if(Hook[0].dY < 0){
                Hook[0].dY = -2;
            }
        }else if(*KEY_ptr == 0b0010) { //KEY1: normal
            speed_cnt = 1;
            if(Hook[0].dY > 0){
                Hook[0].dY = 4;
            }else if(Hook[0].dY < 0){
                Hook[0].dY = -4;
            }
        }else if(*KEY_ptr == 0b0100) { //KEY2: fast
            speed_cnt = 2;
            if(Hook[0].dY > 0){
                Hook[0].dY = 8;
            }else if(Hook[0].dY < 0){
                Hook[0].dY = -8;
            }
        }
        if(*KEY_ptr == 0b1000) { //KEY3: reset game
            speed_cnt = 1;
            bubble_cnt = 0;
            score_cnt = 0;
            death_cnt = 0;
            game_cnt = 0;
            isWinner = false;
            isGameover = false;
            for(int i = 0; i < 5; i++){
                fish[i].X = rand() % 240 + 40; // 0-239 // 40-279
                if(fish[i].X + fish[i].dX < 0){
                    fish[i].isLeft = false;
                }else if(fish[i].X + fish[i].dX > 319){
                    fish[i].isLeft = true;
                }
                fish[i].isAlive = true;
                fish[i].bubbleDrawn = false;
            }
            Hook[0].X = 160;
            Hook[0].Y = 65;
            Hook[0].dY = 4;
            Hook[0].color = dark_red;
        }
        //clear capture
        *KEY_ptr = 0xF;
        
        
        
        
        //Code for updating the location of Hook
        if(Hook[0].dY > 0){ //hook going down
            if(SW_val == 1){
                Hook[0].dY = -Hook[0].dY;
            }else if(Hook[0].Y > 232){//233
                Hook[0].Y = 231;
                Hook[0].dY = 0;
            }
        }else if(Hook[0].dY < 0){ //hook going up
            if(SW_val == 0){
                Hook[0].dY = -Hook[0].dY;
            }else if(Hook[0].Y < 66){//65
                Hook[0].Y = 65;
                Hook[0].dY = 0;
            }
        }
        Hook[0].Y = Hook[0].Y + Hook[0].dY;
        
        
        
        //Code for updating the location of Fish
        for(int i = 0; i < 5; i++){
            fish[i].X = fish[i].X + fish[i].dX;
            if(fish[i].X < 0){
                fish[i].X = 36;
                fish[i].isLeft = false;
                fish[i].dX = - fish[i].dX;
            }
            else if(fish[i].X > 319){
                fish[i].X = 282;
                fish[i].isLeft = true;
                fish[i].dX = - fish[i].dX;
            }
        }
        
        //activate LED time count
        if(!isWinner && !isGameover){
            if(game_cnt < 25){ //game start
                *LEDR_ptr = 0b1111111111;
            }
            else if(game_cnt < 50){
                *LEDR_ptr = 0b0111111111; //This turns on all LEDs
            }
            else if(game_cnt < 75){
                *LEDR_ptr = 0b0011111111; //This turns off the 1st LED
            }
            else if(game_cnt < 100){
                *LEDR_ptr = 0b0001111111;
            }
            else if(game_cnt < 125){
                *LEDR_ptr = 0b0000111111;
            }
            else if(game_cnt < 150){
                *LEDR_ptr = 0b0000011111;
            }
            else if(game_cnt < 175){
                *LEDR_ptr = 0b0000001111;
            }
            else if(game_cnt < 200){
                *LEDR_ptr = 0b0000000111;
            }
            else if(game_cnt < 225){
                *LEDR_ptr = 0b0000000011;
            }
            else if(game_cnt < 250){
                *LEDR_ptr = 0b0000000001;
            }
            if(game_cnt == 249){ //game over
                *LEDR_ptr = 0b0000000000;
                isGameover = true;
            }
        }
        
        //check if the player wins
        if(score_cnt == 5){
            isWinner = true;
        }
        
        game_cnt++; //game time count
        
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
}

void draw_background(){
    draw_water();
    draw_cloud(50, 10, 58, 10);
    draw_cloud(180, 2, 188, 2);
    draw_cloud(290, 25, 298, 25);
    draw_sand();
    draw_seaweeds();
    draw_fishing_boat(57, 45);
    //For boat
    //17 down
    //103 right
}

void draw_water(){
    for(int j=0; j<62; j++){
        draw_line(0, j, 319, j, 0x2E1F); //Sky
    }
    for(int j=62; j<65; j++){
        draw_line(0, j, 319, j, 0x96FE); //Blue0
    }
    
    for(int j=65; j<125; j++){
        draw_line(0, j, 319, j, 0x6EFE); //Blue1
    }
    for(int i=0; i<321 ; i=i+20){
        draw_line(1+i, 124, 14+i, 124, 0x2E9D); //Blue2
        draw_line(3+i, 123, 12+i, 123, 0x2E9D); //Blue2
        draw_line(5+i, 122, 10+i, 122, 0x2E9D); //Blue2
    }
    for(int j=125; j<180; j++){
        draw_line(0, j, 319, j, 0x2E9D); //Blue2
    }
    for(int i=0; i<321 ; i=i+20){
        draw_line(10+i, 179, 23+i, 179, 0x05FB); //Blue3
        draw_line(12+i, 178, 21+i, 178, 0x05FB); //Blue3
        draw_line(14+i, 177, 19+i, 177, 0x05FB); //Blue3
    }
    for(int j=180; j<230; j++){
        draw_line(0, j, 319, j, 0x05FB); //Blue3
    }
    for(int j=230; j<240; j++){
        draw_line(0, j, 319, j, 0xF693); //Sand
    }
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

void draw_seaweeds(){
    draw_seaweed(5, 235);
    draw_seaweed(30, 236);
    draw_seaweed(40, 231);
    draw_seaweed(55, 237);
    draw_seaweed(80, 234);
    draw_seaweed(100, 232);
    draw_seaweed(130, 238);
    draw_seaweed(145, 237);
    draw_seaweed(180, 232);
    draw_seaweed(220, 233);
    draw_seaweed(250, 234);
    draw_seaweed(280, 238);
    draw_seaweed(300, 232);
    draw_seaweed(310, 239);
}

void draw_seaweed(int x, int y){
    draw_line(x, y, x+1, y, 0x2D02);
    draw_line(x-2, y-1, x+2, y-1, 0x2D02);
    plot_pixel(x-2, y-2, 0x2D02);
    plot_pixel(x, y-2, 0x2D02);
    plot_pixel(x+2, y-2, 0x2D02);
    plot_pixel(x+3, y-2, 0x2D02);
    plot_pixel(x-3, y-3, 0x2D02);
    plot_pixel(x-2, y-3, 0x2D02);
    plot_pixel(x, y-3, 0x2D02);
    plot_pixel(x+3, y-3, 0x2D02);
    plot_pixel(x+4, y-3, 0x2D02);
    plot_pixel(x-3, y-4, 0x2D02);
    plot_pixel(x, y-4, 0x2D02);
    plot_pixel(x+1, y-4, 0x2D02);
    plot_pixel(x+4, y-4, 0x2D02);
    plot_pixel(x-3, y-5, 0x2D02);
    plot_pixel(x+1, y-5, 0x2D02);
    plot_pixel(x+4, y-5, 0x2D02);
    plot_pixel(x-4, y-6, 0x2D02);
    plot_pixel(x+1, y-6, 0x2D02);
    plot_pixel(x+4, y-6, 0x2D02);
    plot_pixel(x-4, y-7, 0x2D02);
    plot_pixel(x+1, y-7, 0x2D02);
    plot_pixel(x+4, y-7, 0x2D02);
    plot_pixel(x-4, y-8, 0x2D02);
    plot_pixel(x, y-8, 0x2D02);
    plot_pixel(x+1, y-8, 0x2D02);
    plot_pixel(x+4, y-8, 0x2D02);
    plot_pixel(x+5, y-8, 0x2D02);
    plot_pixel(x-4, y-9, 0x2D02);
    plot_pixel(x, y-9, 0x2D02);
    plot_pixel(x+5, y-9, 0x2D02);
    plot_pixel(x-4, y-10, 0x2D02);
    plot_pixel(x, y-10, 0x2D02);
    plot_pixel(x+5, y-10, 0x2D02);
    plot_pixel(x-5, y-11, 0x2D02);
    plot_pixel(x-4, y-11, 0x2D02);
    plot_pixel(x, y-11, 0x2D02);
    plot_pixel(x+5, y-11, 0x2D02);
    plot_pixel(x-5, y-12, 0x2D02);
    draw_line(x+5, y-12, x+6, y-12, 0x2D02);
}

void draw_sand(){
    plot_pixel(10, 231, 0); //Black
    plot_pixel(40, 234, 0); //Black
    plot_pixel(50, 233, 0); //Black
    plot_pixel(80, 232, 0); //Black
    plot_pixel(100, 232, 0); //Black
    plot_pixel(110, 231, 0); //Black
    plot_pixel(150, 235, 0); //Black
    plot_pixel(180, 238, 0); //Black
    plot_pixel(190, 233, 0); //Black
    plot_pixel(200, 231, 0); //Black
    plot_pixel(230, 232, 0); //Black
    plot_pixel(280, 238, 0); //Black
    plot_pixel(300, 235, 0); //Black
    plot_pixel(310, 239, 0); //Black
}

void draw_bubbles(int x, int y){
    draw_bubble_s(x, y);
    draw_bubble_s(x-8, y-8);
    draw_bubble_b(x+3, y-24);
}

void draw_bubble_s(int x, int y){
    draw_line(x, y, x+2, y, white);
    plot_pixel(x-1, y+1, white);
    plot_pixel(x+3, y+1, white);
    plot_pixel(x-2, y+2, white);
    plot_pixel(x+4, y+2, white);
    plot_pixel(x-3, y+3, white);
    plot_pixel(x+5, y+3, white);
    plot_pixel(x-3, y+4, white);
    plot_pixel(x+5, y+4, white);
    plot_pixel(x-3, y+5, white);
    plot_pixel(x+5, y+5, white);
    plot_pixel(x-2, y+6, white);
    plot_pixel(x+4, y+6, white);
    plot_pixel(x-1, y+7, white);
    plot_pixel(x+3, y+7, white);
    draw_line(x, y+8, x+2, y+8, white);
}
void draw_bubble_b(int x, int y){
    draw_line(x, y, x+6, y, white);
    draw_line(x-2, y+1, x-1, y+1, white);
    draw_line(x+7, y+1, x+8, y+1, white);
    draw_line(x-3, y+2, x-2, y+2, white);
    draw_line(x+8, y+2, x+9, y+2, white);
    plot_pixel(x-3, y+3, white);
    plot_pixel(x+9, y+3, white);
    plot_pixel(x-4, y+4, white);
    plot_pixel(x+10, y+4, white);
    plot_pixel(x-4, y+5, white);
    plot_pixel(x+10, y+5, white);
    plot_pixel(x-5, y+6, white);
    plot_pixel(x+11, y+6, white);
    plot_pixel(x-5, y+7, white);
    plot_pixel(x+11, y+7, white);
    plot_pixel(x-5, y+8, white);
    plot_pixel(x+11, y+8, white);
    plot_pixel(x-5, y+9, white);
    plot_pixel(x+11, y+9, white);
    plot_pixel(x-5, y+10, white);
    plot_pixel(x+11, y+10, white);
    plot_pixel(x-5, y+11, white);
    plot_pixel(x+11, y+11, white);
    plot_pixel(x-4, y+12, white);
    plot_pixel(x+10, y+12, white);
    plot_pixel(x-4, y+13, white);
    plot_pixel(x+10, y+13, white);
    plot_pixel(x-3, y+14, white);
    plot_pixel(x+9, y+14, white);
    draw_line(x-3, y+15, x-2, y+15, white);
    draw_line(x+8, y+15, x+9, y+15, white);
    draw_line(x-2, y+16, x-1, y+16, white);
    draw_line(x+7, y+16, x+8, y+16, white);
    draw_line(x, y+17, x+6, y+17, white);
}

void draw_fishing_boat(int x, int y){ // (x,y) start coord
    //boat
    draw_line2(x, y, 66, dark_brown, false); //fishing boat top edge
    draw_line2(x+66, y, 17, dark_brown, true); //right edge
    plot_pixel(x, y+2, dark_brown); //left edge
    draw_stair(x+1, y+2, 14, dark_brown, false); //left edge
    draw_line1(x+2, y+2, 64, light_brown, false);
    draw_line1(x+3, y+3, 63, light_brown, false);
    draw_line1(x+4, y+4, 62, light_brown, false);
    plot_pixel(x+5, y+5, dark_brown);
    draw_line2(x+6, y+5, 60, dark_brown, false);
    draw_line1(x+7, y+7, 59, light_brown, false);
    draw_line1(x+8, y+8, 58, light_brown, false);
    draw_line1(x+9, y+9, 57, light_brown, false);
    plot_pixel(x+10, y+10, dark_brown);
    draw_line2(x+11, y+10, 55, dark_brown, false);
    draw_line1(x+12, y+12, 54, light_brown, false);
    draw_line1(x+13, y+13, 53, light_brown, false);
    draw_line1(x+14, y+14, 52, light_brown, false);
    draw_line1(x+15, y+15, 2, dark_brown, true); //bottom edge
    draw_line2(x+16, y+15, 50, dark_brown, false);
    //fisher
    draw_line2(x+54, y-12, 12, black, true); //body
    draw_line1(x+56, y-12, 12, black, true);
    draw_line1(x+54, y-13, 3, beige, false);
    draw_line1(x+53, y-14, 5, beige, false);
    draw_line1(x+52, y-15, 7, beige, false);
    draw_line1(x+51, y-16, 9, beige, false);
    draw_stair(x+50, y-16, 4, black, false); //face bottom left edge
    draw_line2(x+50, y-18, 11, beige, false);
    draw_line2(x+50, y-20, 8, beige, false);
    draw_line1(x+51, y-21, 9, beige, false);
    draw_line1(x+49, y-21, 6, black, true); //face left edge
    draw_stair(x+50, y-21, 4, black, true); //face top left edge
    draw_line1(x+52, y-22, 7, beige, false);
    draw_line1(x+53, y-23, 5, beige, false);
    draw_line1(x+54, y-24, 3, beige, false);
    draw_line1(x+54, y-25, 3, black, false); //face top edge
    draw_stair(x+57, y-25, 4, black, false); //face top right edge
    draw_line1(x+61, y-21, 6, black, true); //face right edge
    draw_line2(x+59, y-20, 2, beige, true);
    draw_line1(x+58, y-20, 2, black, true); //eye
    draw_stair(x+57, y-12, 4, black, true); //face bottom right edge
    draw_line2(x+57, y-6, 2, black, true); //arm
    draw_line2(x+59, y-7, 2, black, true); //arm
    draw_stair(x+61, y-7, 8, dark_red, true); //fishing rod
    draw_line1(x+69, y-15, 3, dark_red, false);
    draw_stair(x+72, y-15, 31, grey, false); //fishing rope
    plot_pixel(x+103, y+16, grey);
}

void draw_fishL(int x, int y){ // (x,y) start coord
    draw_line2(x, y, 3, black, true); //fish mouth
    draw_stair(x+1, y-1, 6, black, true); //fish face top edge
    draw_stair(x+1, y+3, 6, black, false); //fish face bottom edge
    
    //fish face
    draw_line1(x+2, y-1, 5, orange, true);
    draw_line2(x+3, y-2, 7, orange, true);
    plot_pixel(x+4, y-3, orange);
    plot_pixel(x+4, y+5, orange);
    draw_line2(x+5, y-4, 11, orange, true);
    plot_pixel(x+6, y-5, orange);
    plot_pixel(x+6, y+7, orange);
    //fish top edge
    draw_line2(x+7, y-8, 2, black, true);
    draw_line2(x+9, y-9, 2, black, true);
    draw_line2(x+11, y-10, 9, black, false);
    draw_line2(x+20, y-9, 2, black, true);
    draw_stair(x+22, y-8, 5, black, false);
    plot_pixel(x+26, y-2, black);
    draw_line2(x+27, y-2, 2, black, true);
    draw_stair(x+29, y-2, 4, black, true);
    plot_pixel(x+32, y-7, black);
    draw_line2(x+33, y-8, 3, black, false);
    draw_line2(x+34, y-6, 18, black, true);
    //fish bottom edge
    draw_line2(x+7, y+9, 4, black, false);
    draw_line2(x+11, y+10, 9, black, false);
    draw_line2(x+20, y+9, 2, black, true);
    draw_stair(x+22, y+9, 5, black, true);
    draw_line2(x+27, y+3, 2, black, true);
    draw_line1(x+29, y+4, 2, black, true);
    draw_stair(x+30, y+6, 4, black, false);
    //fish body
    draw_line2(x+7, y-6, 3, orange, true);
    draw_line1(x+7, y-3, 3, orange, true);
    draw_line2(x+9, y-7, 4, orange, true);
    draw_fish_eye(x+8, y-3);
    draw_line2(x+11, y-8, 18, orange, true);
    draw_line2(x+13, y-8, 18, orange, true);
    draw_line2(x+15, y-8, 18, white, true);
    draw_line2(x+17, y-8, 18, orange, true);
    plot_pixel(x+19, y-8, orange);
    draw_line2(x+19, y-7, 16, orange, true);
    plot_pixel(x+21, y-7, white);
    draw_line2(x+21, y-6, 14, white, true);
    plot_pixel(x+23, y-5, orange);
    draw_line2(x+23, y-4, 10, orange, true);
    draw_line1(x+25, y-3, 2, orange, true);
    draw_line2(x+25, y-1, 5, orange, true);
    draw_line2(x+27, y, 3, white, true);
    draw_line2(x+29, y-1, 5, orange, true);
    plot_pixel(x+30, y-2, orange);
    draw_line2(x+31, y-3, 10, orange, true);
    plot_pixel(x+32, y-4, orange);
    draw_line1(x+33, y-5, 14, white, true);
    draw_line2(x+7, y, 9, orange, true);
    draw_line1(x+9, y, 2, orange, false);
    draw_line2(x+9, y+1, 8, white, true);
    plot_pixel(x+19, y+9, orange);
    plot_pixel(x+21, y+8, white);
    plot_pixel(x+23, y+6, orange);
    plot_pixel(x+2, y+4, orange);
    draw_line1(x+5, y+4, 2, orange, true);
    plot_pixel(x+7, y+7, orange);
    plot_pixel(x+9, y+8, white);
}

void draw_fishR(int x, int y){ // (x,y) start coord
    draw_line2(x-1, y, 3, black, true); //fish mouth
    
    draw_stair(x-6, y-7, 6, black, false); //fish face top edge
    draw_stair(x-6, y+9, 6, black, true); //fish face bottom edge
    
    
    //fish face
    draw_line1(x-2, y-1, 5, orange, true);
    draw_line2(x-4, y-2, 7, orange, true);
    plot_pixel(x-4, y-3, orange);
    plot_pixel(x-4, y+5, orange);
    draw_line2(x-6, y-4, 11, orange, true);
    plot_pixel(x-6, y-5, orange);
    plot_pixel(x-6, y+7, orange);
    
    //fish top edge
    draw_line2(x-8, y-8, 2, black, true);
    draw_line2(x-10, y-9, 2, black, true);
    draw_line2(x-19, y-10, 9, black, false);
    draw_line2(x-21, y-9, 2, black, true);
    draw_stair(x-26, y-3, 5, black, true);
    plot_pixel(x-26, y-2, black);
    draw_line2(x-28, y-2, 2, black, true);
    draw_stair(x-32, y-6, 4, black, false);
    plot_pixel(x-32, y-7, black);
    draw_line2(x-35, y-8, 3, black, false);
    draw_line2(x-35, y-6, 18, black, true);
    
    //fish bottom edge
    draw_line2(x-10, y+9, 4, black, false);
    draw_line2(x-19, y+10, 9, black, false);
    draw_line2(x-21, y+9, 2, black, true);
    draw_stair(x-26, y+4, 5, black, false);
    draw_line2(x-28, y+3, 2, black, true);
    draw_line1(x-29, y+4, 2, black, true);
    draw_stair(x-33, y+10, 4, black, true);
    
    //fish body
    draw_line2(x-8, y-6, 3, orange, true);
    draw_line1(x-7, y-3, 3, orange, true);
    draw_line2(x-10, y-7, 4, orange, true);
    draw_fish_eye(x-10, y-3);
    draw_line2(x-12, y-8, 18, orange, true);
    draw_line2(x-14, y-8, 18, orange, true);
    draw_line2(x-16, y-8, 18, white, true);
    draw_line2(x-18, y-8, 18, orange, true);
    plot_pixel(x-19, y-8, orange);
    draw_line2(x-20, y-7, 16, orange, true);
    plot_pixel(x-21, y-7, white);
    draw_line2(x-22, y-6, 14, white, true);
    plot_pixel(x-23, y-5, orange);
    draw_line2(x-24, y-4, 10, orange, true);
    draw_line1(x-25, y-3, 2, orange, true);
    draw_line2(x-26, y-1, 5, orange, true);
    draw_line2(x-28, y, 3, white, true);
    draw_line2(x-30, y-1, 5, orange, true);
    plot_pixel(x-30, y-2, orange);
    draw_line2(x-32, y-3, 10, orange, true);
    plot_pixel(x-32, y-4, orange);
    draw_line1(x-33, y-5, 14, white, true);
    draw_line2(x-8, y, 9, orange, true);
    draw_line1(x-10, y, 2, orange, false);
    draw_line2(x-10, y+1, 8, white, true);
    plot_pixel(x-19, y+9, orange);
    plot_pixel(x-21, y+8, white);
    plot_pixel(x-23, y+6, orange);
    plot_pixel(x-2, y+4, orange);
    draw_line1(x-5, y+4, 2, orange, true);
    plot_pixel(x-7, y+7, orange);
    plot_pixel(x-9, y+8, white);
    
}

void draw_GAMEOVER(int x, int y){
    draw_G(x, y);
    draw_A(x+32, y);
    draw_M(x+64, y);
    draw_E(x+96, y);
    draw_O(x, y+34);
    draw_V(x+32, y+34);
    draw_E(x+64, y+34);
    draw_R(x+96, y+34);
}

void draw_YOUWIN(int x, int y){
    draw_Y(x, y);
    draw_O(x+32, y);
    draw_U(x+64, y);
    draw_W(x+110, y);
    draw_I(x+150, y);
    draw_N(x+182, y);
}


void draw_G(int x, int y){
    draw_line4(x+4, y, 20, black, false); //Gtop
    draw_line4(x, y+4, 20, black, true); //Gleft
    draw_line4(x+4, y+4, 20, black, true); //Gleft
    draw_line4(x+20, y+4, 8, black, false); //Gtop right
    draw_line4(x+16, y+12, 12, black, false);
    draw_line4(x+20, y+16, 8, black, false);
    draw_line4(x+20, y+20, 8, black, false);
    draw_line4(x+4, y+24, 20, black, false);
}

void draw_A(int x, int y){
    draw_line4(x+8, y, 12, black, false); //Atop
    draw_line4(x+4, y+4, 8, black, false);
    draw_line4(x+16, y+4, 8, black, false);
    draw_line4(x, y+8, 20, black, true); //Aleft
    draw_line4(x+4, y+8, 20, black, true);
    draw_line4(x+8, y+16, 12, black, false); //Amid
    draw_line4(x+20, y+8, 20, black, true); //Aright
    draw_line4(x+24, y+8, 20, black, true);
}

void draw_M(int x, int y){
    draw_line4(x, y, 28, black, true);
    draw_line4(x+4, y+4, 24, black, true);
    draw_line4(x+8, y+8, 8, black, true);
    draw_line4(x+12, y+12, 8, black, true);
    draw_line4(x+16, y+8, 8, black, true);
    draw_line4(x+20, y+4, 24, black, true);
    draw_line4(x+24, y, 28, black, true);
}

void draw_E(int x, int y){
    draw_line4(x, y, 28, black, true);
    draw_line4(x+4, y, 28, black, true);
    draw_line4(x+8, y, 20, black, false);
    draw_line4(x+8, y+12, 16, black, false);
    draw_line4(x+8, y+24, 20, black, false);
}

void draw_O(int x, int y){
    draw_line4(x+4, y, 20, black, false); //Otop
    draw_line4(x, y+4, 20, black, true);
    draw_line4(x+4, y+4, 20, black, true);
    draw_line4(x+20, y+4, 20, black, true);
    draw_line4(x+24, y+4, 20, black, true);
    draw_line4(x+4, y+24, 20, black, false);
}

void draw_V(int x, int y){
    draw_line4(x, y, 20, black, true);
    draw_line4(x+4, y, 20, black, true);
    draw_line4(x+20, y, 20, black, true);
    draw_line4(x+24, y, 20, black, true);
    draw_line4(x+4, y+20, 8, black, false);
    draw_line4(x+16, y+20, 8, black, false);
    draw_line4(x+8, y+24, 12, black, false);
}

void draw_R(int x, int y){
    draw_line4(x, y, 28, black, true);
    draw_line4(x+4, y, 28, black, true);
    draw_line4(x+8, y, 16, black, false);
    draw_line4(x+20, y+4, 8, black, true);
    draw_line4(x+24, y+4, 8, black, true);
    draw_line4(x+8, y+12, 16, black, false);
    draw_line4(x+12, y+16, 8, black, false);
    draw_line4(x+16, y+20, 8, black, false);
    draw_line4(x+20, y+24, 8, black, false);
}

void draw_Y(int x, int y){
    draw_line4(x, y, 12, black, true);
    draw_line4(x+4, y, 12, black, true);
    draw_line4(x+20, y, 12, black, true);
    draw_line4(x+24, y, 12, black, true);
    draw_line4(x+4, y+12, 20, black, false);
    draw_line4(x+10, y+16, 12, black, true);
    draw_line4(x+14, y+16, 12, black, true);
}

void draw_U(int x, int y){
    draw_line4(x, y, 24, black, true);
    draw_line4(x+4, y, 24, black, true);
    draw_line4(x+20, y, 24, black, true);
    draw_line4(x+24, y, 24, black, true);
    draw_line4(x+4, y+24, 20, black, false);
}

void draw_W(int x, int y){
    draw_line4(x, y, 28, black, true);
    draw_line4(x+4, y, 28, black, true);
    draw_line4(x+8, y+16, 12, black, true);
    draw_line4(x+12, y+16, 8, black, true);
    draw_line4(x+16, y+12, 8, black, true);
    draw_line4(x+20, y+16, 8, black, true);
    draw_line4(x+24, y+16, 12, black, true);
    draw_line4(x+28, y, 28, black, true);
    draw_line4(x+32, y, 28, black, true);
}

void draw_I(int x, int y){
    draw_line4(x, y, 28, black, false);
    draw_line4(x+8, y+4, 20, black, true);
    draw_line4(x+12, y+4, 20, black, true);
    draw_line4(x+16, y+4, 20, black, true);
    draw_line4(x, y+24, 28, black, false);
}

void draw_N(int x, int y){
    draw_line4(x, y, 28, black, true);
    draw_line4(x+4, y, 28, black, true);
    draw_line4(x+8, y+4, 8, black, true);
    draw_line4(x+12, y+8, 10, black, true);
    draw_line4(x+16, y+12, 12, black, true);
    draw_line4(x+20, y, 28, black, true);
    draw_line4(x+24, y, 28, black, true);
}


void plotHook(Hook Hook){
    draw_line(Hook.X, Hook.Y, Hook.X, Hook.Y + 5, Hook.color);
    plot_pixel(Hook.X - 1, Hook.Y + 6, Hook.color);
    plot_pixel(Hook.X - 2, Hook.Y + 6, Hook.color);
    plot_pixel(Hook.X - 3, Hook.Y + 5, Hook.color);
    plot_pixel(Hook.X - 3, Hook.Y + 4, Hook.color);
}

void draw_line1(int x, int y, int len, short int color, bool is_vertical){
    if(is_vertical){
        for(int i = 0; i < len; i++){
            plot_pixel(x, y+i, color);
        }
    }
    else{
        for(int i = 0; i < len; i++){
            plot_pixel(x+i, y, color);
        }
    }
}

void draw_line2(int x, int y, int len, short int color, bool is_vertical){
    if(is_vertical){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < len; j++){
                plot_pixel(x+i, y+j, color);
            }
        }
    }
    else{
        for(int i = 0; i < len; i++){
            for(int j = 0; j < 2; j++){
                plot_pixel(x+i, y+j, color);
            }
        }
    }
}

void draw_line4(int x, int y, int len, short int color, bool is_vertical){
    
    if(is_vertical){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < len; j++){
                plot_pixel(x+i, y+j, color);
            }
        }
    }
    else{
        for(int i = 0; i < len; i++){
            for(int j = 0; j < 4; j++){
                plot_pixel(x+i, y+j, color);
            }
        }
    }
}


void draw_stair(int x, int y, int len, short int color, bool is_rightUP){
    if(is_rightUP){
        for(int i = 0; i < len; i++){
            for(int j = 0; j < 2; j++){
                plot_pixel(x+i, y-j-i, color);
            }
        }
    }
    else{
        for(int i = 0; i < len; i++){
            for(int j = 0; j < 2; j++){
                plot_pixel(x+i, y+j+i, color);
            }
        }
    }
}

void draw_fish_eye(int x, int y){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            plot_pixel(x+i, y+j, black);
        }
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
    memset((short int*) pixel_buffer_start, 0, 245760 );
}

void draw_all_white(){
    int x;
    int y;
    for(x=0; x<320; x++){
        for(y=0; y<240; y++){
            plot_pixel(x, y, white);
        }
    }
}

void wait_for_vsync(){
    *pixel_ctrl_ptr = 1; //Writing 1 to Buffer reg sets S=1
    while( ((*status) & 0x1) != 0){
        //wait until S=0 //S=0 when swap occured
    }
}








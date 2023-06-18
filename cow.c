#include "cow.h"
#include <allegro5/allegro.h>

// the state of character
enum {STOP = 0, MOVE}; //enum 後面這坨從０開始計數 move從1開始，stop從0開始
typedef struct animal_cow
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // down: false, up: true
    int state; // the state of character
    bool live, lr_dir;
    ALLEGRO_BITMAP *img_move[2];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}animal_cow;
animal_cow cow;
ALLEGRO_SAMPLE *c_sample = NULL;
void cow_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/cow_move%d.png", i );
        //temp就會變成："./image/char_move0.png", "./image/char_move1.png", ...
        cow.img_move[i-1] = al_load_bitmap(temp);
        printf("%p", cow.img_move[i-1]);
        //這再一個一個move
    }

    // initial the geometric information of character
    cow.width = 1000; //al_get_bitmap_width(cow.img_move[0]);
    cow.height = 1000; //al_get_bitmap_height(cow.img_move[0]);
    cow.x = 800;
    cow.y = 400;
    cow.dir = false;
    cow.lr_dir = false; //false = left, true = right

    // initial the animation component
    cow.state = STOP;
    cow.anime = 0;
    cow.anime_time = 30;
    cow.live = true;

}

void cow_destroy(){
    al_destroy_bitmap(cow.img_move[0]);
    al_destroy_bitmap(cow.img_move[1]);
}
void cow_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            cow.anime++;
            cow.anime %= cow.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        cow.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void cow_update(){
    if(cow.live == true){//if(key_state[ALLEGRO_KEY_P])
        if (cow.anime == 0){
            cow.state = STOP;
        }
        if (cow.dir == false) { 
            cow.y += rand()%10+1;
            cow.state = MOVE;
        }
        if (cow.dir == true) { 
            cow.y -= rand()%10+1;
            cow.state = MOVE;
        }
        if (cow.y >= 1100){
            cow.state = STOP;
            cow.dir = true;
        }
        if (cow.y <= 50){
            cow.state = STOP;
            cow.dir = false;
        }
        if (cow.lr_dir == false) { 
            cow.x -= rand()%10+1;
            cow.state = MOVE;
        }
        if (cow.lr_dir == true) { 
            cow.x += rand()%10+1;
            cow.state = MOVE;
        }
        if(cow.x <= 692){
            cow.lr_dir = true;
        }
        if(cow.x >= 1650){
            cow.lr_dir = false;
        }
    }
    al_rest(0.01);
    cow_x_coord = cow.x;
    cow_y_coord = cow.y;
}

void cow_draw(){
    // with the state, draw corresponding image
    if( cow.state == STOP ){
        if( cow.lr_dir ){
            al_draw_bitmap(cow.img_move[0], cow.x, cow.y, 0);
        }else{
            al_draw_bitmap(cow.img_move[0], cow.x, cow.y, 0);
        }
    }else if( cow.state == MOVE ){
        if( cow.lr_dir ){
            if( cow.anime < cow.anime_time/2 ){
                al_draw_bitmap(cow.img_move[0], cow.x, cow.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(cow.img_move[1], cow.x, cow.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( cow.anime < cow.anime_time/2 ){
                al_draw_bitmap(cow.img_move[0], cow.x, cow.y, 0);
            }else{
                al_draw_bitmap(cow.img_move[1], cow.x, cow.y, 0);
            }
        }
    }
}
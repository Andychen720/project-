#include "mower.h"
// the state of character
enum {STOP = 0, MOVE};//enum 後面這坨從０開始計數 move從1開始，stop從0開始
typedef struct mower
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[1];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    bool live;
    bool touch;
}mower;
mower mow;
ALLEGRO_SAMPLE * W_sample = NULL;
void mower_init(){
    // load character images
    char temp[50];
    sprintf( temp, "./image/mower_move%d.png", 1 );
    mow.img_move[0] = al_load_bitmap(temp);
    printf("%p", mow.img_move[0]);

    // initial the geometric information of character
    mow.width = al_get_bitmap_width(mow.img_move[0]);
    mow.height = al_get_bitmap_height(mow.img_move[0]);
    mow.x = 240;
    mow.y = 180;
    mow.dir = false;
    mow.live = true;

    // initial the animation component
    mow.state = STOP;
    mow.anime = 0;
    mow.anime_time = 30;
    mow.touch = false;

}
void mower_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            mow.anime++;
            mow.anime %= mow.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        mow.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void mower_destroy(){
    al_destroy_bitmap(mow.img_move[0]);
}
int mower_collision(int x, int y, int s){
    if(abs(mow.x - x) < s){
        if(abs(mow.y - y) < s){
            return 1;
        }
    }else{
        return 0;
    }
    
}
void mower_update(){
    mow.dir = chara_direction;
    if(mower_fire == true){
        mow.x += 5;
        mow.state = MOVE;
        if (mow.x >= 1890 ){ 
            mow.state = STOP;
            mower_fire = false;
            mow.x = 240;
            mow.y = 190;
            if(mow.touch == true){
                score_beef++;
            }
        }
        printf("%d %d %d %d\n", mow.x, mow.y, cow_x_coord, cow_y_coord);
        if(mower_collision(cow_x_coord, cow_y_coord, 50) == 1){
            debug(1);
            mow.touch = true;
            mow.x = 1890;
        }
        al_rest(0.001);
    }
}
void mower_draw(){
    al_draw_bitmap(mow.img_move[0], mow.x, mow.y, 0);
}
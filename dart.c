#include "dart.h"
// the state of character
enum {STOP = 0, MOVE};//enum 後面這坨從０開始計數 move從1開始，stop從0開始
typedef struct dart
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
}dart;
dart drt;
ALLEGRO_SAMPLE * Q_sample = NULL;
void dart_init(){
    // load character images
    char temp[50];
    sprintf( temp, "./image/dart_move%d.png", 1 );
    drt.img_move[0] = al_load_bitmap(temp);
    printf("%p", drt.img_move[0]);

    // initial the geometric information of character
    drt.width = al_get_bitmap_width(drt.img_move[0]);
    drt.height = al_get_bitmap_height(drt.img_move[0]);
    drt.x = 550;
    drt.y = 680;
    drt.dir = false;
    drt.live = true;

    // initial the animation component
    drt.state = STOP;
    drt.anime = 0;
    drt.anime_time = 30;
    drt.touch = false;

}
void dart_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            drt.anime++;
            drt.anime %= drt.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        drt.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void dart_destroy(){
    al_destroy_bitmap(drt.img_move[0]);
}
int dart_collision(int x, int y, int s){
    if(abs(drt.x - x) < s){
        if(abs(drt.y - y) < s){
            return 1;
        }
    }else{
        return 0;
    }
    
}
void dart_update(){
    drt.dir = chara_direction;
    if(dart_fire == true){
        drt.x += 5;
        drt.state = MOVE;
        if (drt.x >= 1890 ){ 
            drt.state = STOP;
            dart_fire = false;
            drt.x = 550;
            drt.y = 680;
            if(drt.touch == true){
                score_beef++;
            }
        }
        printf("%d %d %d %d\n", drt.x, drt.y, cow_x_coord, cow_y_coord);
        if(dart_collision(cow_x_coord, cow_y_coord, 15) == 1){
            debug(1);
            drt.touch = true;
            drt.x = 1890;
        }
        al_rest(0.001);
    }
}
void dart_draw(){
    al_draw_bitmap(drt.img_move[0], drt.x, drt.y, 0);
}
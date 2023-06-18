#include "arrow.h"
// the state of character
enum {STOP = 0, MOVE};//enum 後面這坨從０開始計數 move從1開始，stop從0開始
typedef struct arrow
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
}arrow;
arrow arw;
ALLEGRO_SAMPLE * R_sample = NULL;
void arrow_init(){
    // load character images
    char temp[50];
    sprintf( temp, "./image/arrow_move%d.png", 1 );
    arw.img_move[0] = al_load_bitmap(temp);
    printf("%p", arw.img_move[0]);

    // initial the geometric information of character
    arw.width = al_get_bitmap_width(arw.img_move[0]);
    arw.height = al_get_bitmap_height(arw.img_move[0]);
    arw.x = -10;
    arw.y = 1000;
    arw.dir = false;
    arw.live = true;

    // initial the animation component
    arw.state = STOP;
    arw.anime = 0;
    arw.anime_time = 30;
    arw.touch = false;

}
void arrow_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            arw.anime++;
            arw.anime %= arw.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        arw.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void arrow_destroy(){
    al_destroy_bitmap(arw.img_move[0]);
}
int arrow_collision(int x, int y, int s){
    if(abs(arw.x - x) < s){
        if(abs(arw.y - y) < s){
            return 1;
        }
    }else{
        return 0;
    }
    
}
void arrow_update(){
    arw.dir = chara_direction;
    if(arrow_fire == true){
        arw.x += 5;
        arw.state = MOVE;
        if (arw.x >= 1890 ){ 
            arw.state = STOP;
            arrow_fire = false;
            arw.x = -50;
            arw.y = 1000;
            if(arw.touch == true){
                score_beef++;
            }
            printf("score_beef = %d", score_beef);
        }
        printf("%d %d %d %d\n", arw.x, arw.y, cow_x_coord, cow_y_coord);
        if(arrow_collision(cow_x_coord, cow_y_coord, 30) == 1){
            arw.touch = true;
            arw.x = 1890;
        }
        al_rest(0.001);
    }
}
void arrow_draw(){
    al_draw_bitmap(arw.img_move[0], arw.x, arw.y, 0);
}
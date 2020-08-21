#include "sprite.hpp"

#define TEX_NUM 421

Texture *textures[TEX_NUM];

Sprite::Sprite(int texture_number, Screen *s)
    : texture_number(texture_number), s(s) {
    this->pos.x = 0;
    this->pos.y = 0;
    this->pos.w = textures[this->texture_number]->get_width();
    this->pos.h = textures[this->texture_number]->get_height();
}

void Sprite::blit(){
    this->s->blit_screen(textures[this->texture_number], &this->pos);
}

/******************************************************************/

void load_all_textures(Screen *s){
    char path[] = "data/lands/land_001";
    for(int i = 1; i < TEX_NUM; i++){
        // changer le numéro de fin, padding...
        if (i < 10){
            path[7] = '0' + i;
        }
        else if (i < 10){
            path[6] = '0' + (i / 10);
            path[7] = '0' + (i % 10);
        }
        else {
            path[5] = '0' + (i / 100);
            path[6] = '0' + (i / 10);
            path[7] = '0' + (i % 10);
        }
        textures[i] = new Texture(path, s);
    }
}

void free_all_textures(){
    for(Texture *t : textures){
        delete t;
    }
}

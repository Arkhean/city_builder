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

void Sprite::move(int x, int y){
    this->pos.x = x;
    this->pos.y = y + 30 - this->pos.h;
}

void Sprite::blit(Texture *target){
    target->blit(s, textures[this->texture_number], &this->pos);
}

/******************************************************************/

void load_all_textures(Screen *s){
    char path[] = "data/lands/land_001.png";
    for(int i = 0; i < TEX_NUM; i++){
        // changer le numéro de fin, padding...
        int n = i + 1;
        if (n < 10){
            path[18] = '0' + n;
        }
        else if (n < 10){
            path[17] = '0' + (n / 10);
            path[18] = '0' + (n % 10);
        }
        else {
            path[16] = '0' + (n / 100);
            path[17] = '0' + ((n / 10) % 10);
            path[18] = '0' + (n % 10);
        }
        textures[i] = new Texture(path, s);
        if (textures[i] == NULL){
            std::cout << "error texture load\n";
            exit(1);
        }
    }
    std::cout << "all textures loaded\n";
}

void free_all_textures(){
    for(Texture *t : textures){
        delete t;
    }
}

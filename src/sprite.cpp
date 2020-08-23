#include "sprite.hpp"

Texture *textures[LAND_TEXTURES+BUILDING_NUMBER];

Sprite::Sprite(int texture_number)
    : texture_number(texture_number) {
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
    target->blit(textures[this->texture_number], &this->pos);
}

/******************************************************************/

void load_all_textures(Screen *s){
    /* lands */
    char path[] = "data/lands/land_001.png";
    for(int i = 0; i < LAND_TEXTURES; i++){
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
        textures[i] = new Texture(s, path);
        if (textures[i] == NULL){
            std::cout << "error texture load\n";
            exit(1);
        }
    }
    /* buildings */
    char path2[] = "data/buildings/building_001.png";
    for(int i = 0; i < BUILDING_NUMBER; i++){
        int n = i + 1;
        if (n < 10){
            path2[26] = '0' + n;
        }
        else if (n < 10){
            path2[25] = '0' + (n / 10);
            path2[26] = '0' + (n % 10);
        }
        else {
            path2[24] = '0' + (n / 100);
            path2[25] = '0' + ((n / 10) % 10);
            path2[26] = '0' + (n % 10);
        }
        textures[LAND_TEXTURES+i] = new Texture(s, path2);
        if (textures[LAND_TEXTURES+i] == NULL){
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

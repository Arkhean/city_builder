#include "sprite.hpp"

std::string names[] = {
    "Marché",
    "Ferme", "Mine de fer", "Puits d'argile", "Cabane de bûcheron", "Ecole",
    "Université", "Atelier de vin", "Atelier d'huile", "Atelier d'armes",
    "Atelier de meubles", "Théâtre", "Colisée", "Sénat",
    "Préfecture", "Fort", "Caserne", "Barbier",
    "Médecin", "Thermes", "Hôpital",
    "Temple de Cérès", "Temple de Neptune",
    "Temple de Mercure", "Temple de Mars", "Temple de Vénus",
    "Oracle", "Pêcherie", "", "", "",
    "Puits", "Fontaine", "Atelier de poterie",
    "Champs de blé", "", "", "", "",
    "Champs de légumes", "", "", "", "",
    "Vergers", "", "", "", "",
    "Oliveraie", "", "", "", "",
    "Vignes", "", "", "", "",
    "Enclos à bétail", "", "", "", "",
    "Habitations", "Entrepôt",
    "Herbes", "Arbres", "Eau", "Rocher", "Route", "vide",
};

Texture *textures[LAND_NUMBER+BUILDING_NUMBER];

Sprite::Sprite(int texture_number, int x, int y, int size)
    : texture_number(texture_number) {
    int w = textures[texture_number]->get_width();
    int h = textures[texture_number]->get_height();
    this->pos.x = x + 58+(size-1)*29 - w;
    this->pos.y = y + 30 - h;
    this->pos.w = w;
    this->pos.h = h;
}

void Sprite::move(int x, int y, int size){
    this->pos.x = x + 58+(size-1)*29 - this->pos.w;
    this->pos.y = y + 30 - this->pos.h;
}

void Sprite::blit(Texture *target){
    target->blit(textures[this->texture_number], &this->pos);
}

/******************************************************************/

void load_all_textures(Screen *s){
    /* lands */
    char path[] = "data/lands/land_001.png";
    for(int i = 0; i < LAND_NUMBER; i++){
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
        textures[LAND_NUMBER+i] = new Texture(s, path2);
        if (textures[LAND_NUMBER+i] == NULL){
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

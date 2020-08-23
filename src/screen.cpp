#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "screen.hpp"
#include "math.h"

TTF_Font * police = NULL;

void init_SDL_TTF(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1){
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    TTF_Init();
    police = TTF_OpenFont("./data/DejaVuSans.ttf", 20);
    if (police == NULL){
        std::cout << "erreur openFont\n";
        exit(1);
    }
}

void quit_SDL_TTF(){
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
}

void initRect (SDL_Rect *rectangle, int x, int y, int w, int h){
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = w;
    rectangle->h = h;
}

// =============================================================================

Screen::Screen(int width, int height){
    this->cadre = new SDL_Rect;
    this->ecran = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    this->rend = SDL_CreateRenderer(this->ecran, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    this->frame = SDL_CreateTexture(this->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    initRect(this->cadre, 0, 0, width, height);
    SDL_RenderClear(this->rend);
    SDL_SetRenderTarget(this->rend, this->frame);
    SDL_RenderClear(this->rend);
    SDL_SetRenderTarget(this->rend, NULL);
}

void Screen::clear(){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(this->rend);
    SDL_SetRenderTarget(this->rend, this->frame);
    SDL_RenderClear(this->rend);
    SDL_SetRenderTarget(this->rend, NULL);
}

Screen::~Screen(){
    SDL_DestroyTexture(this->frame);
    SDL_DestroyRenderer(this->rend);
    SDL_DestroyWindow(this->ecran);
    delete this->cadre;
}

void Screen::update(){
    SDL_RenderCopy(this->rend, this->frame, NULL, NULL);
    SDL_RenderPresent(this->rend);
}

void Screen::blit_screen(Texture * t, SDL_Rect * where, SDL_Rect * partie){
    SDL_SetRenderTarget(this->rend, this->frame);
    SDL_RenderCopy(this->rend, t->text, partie, where);
    SDL_SetRenderTarget(this->rend, NULL);
    t->get_cadre()->x = where != NULL ? where->x : 0;
    t->get_cadre()->y = where != NULL ? where->y : 0;
}

SDL_Renderer * Screen::get_rend(){
    return this->rend;
}

int Screen::get_width(){
    return this->cadre->w;
}
int Screen::get_height(){
    return this->cadre->h;
}

void Screen::draw_line(int x1, int y1, int x2, int y2, SDL_Color color){
    SDL_SetRenderTarget(rend, frame);
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(rend, x1, y1, x2, y2);
    SDL_SetRenderTarget(rend, NULL);
}

void Screen::draw_circle(int cx, int cy, int radius, SDL_Color color){
    //static const int BPP = 4;
    SDL_SetRenderTarget(rend, frame);
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
	for (double dy = 1; dy <= radius; dy += 1.0){
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		//int x = cx - dx;
		SDL_RenderDrawLine(rend, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(rend, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
	}
    SDL_SetRenderTarget(rend, NULL);
}

// =============================================================================
Texture::Texture(Screen * s, int width, int height){
    this->surface = NULL;
    this->cadre = new SDL_Rect;
    this->text = SDL_CreateTexture(s->get_rend(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    initRect(this->cadre, 0, 0, width, height);
}

Texture::Texture(std::string str, Screen * s, SDL_Color color){
    this->text = NULL;
    this->surface = NULL;
    this->cadre = new SDL_Rect;
    if (str.length() > 4 && (str.find(".png") != std::string::npos || str.find(".jpg")!= std::string::npos)){
        this->surface = IMG_Load(str.c_str());
        if (this->surface == NULL){std::cout << "error : " << str << " not found !" <<std::endl;}
        this->text = SDL_CreateTextureFromSurface(s->get_rend(), this->surface);
        initRect(this->cadre, 0, 0, this->surface->w, this->surface->h);
        if (this->text == NULL){std::cout << "error converting" << std::endl;}
    }
    else if (str.length() > 0){
        this->surface = TTF_RenderText_Blended(police, str.c_str(), color);
        this->text = SDL_CreateTextureFromSurface(s->get_rend(), this->surface);
        initRect(this->cadre, 0, 0, surface->w, surface->h);
    }
    else{
        std::cout << "error : string of null length !" << std::endl;
    }
}

Texture::~Texture(){
    SDL_DestroyTexture(this->text);
    SDL_FreeSurface(this->surface);
    delete this->cadre;
}

SDL_Rect * Texture::get_cadre(){
    return this->cadre;
}

int Texture::get_width(){
    return this->cadre->w;
}
int Texture::get_height(){
    return this->cadre->h;
}

Uint32 Texture::get_pixel(int x, int y){
    int nbopp = surface->format->BitsPerPixel/8;
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * nbopp;
    switch (nbopp){
    case 1 :
        return *p;
    case 2 :
        return *(Uint16*)p;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0]<<16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4 :
        return *(Uint32*)p;
    default :
        return 0;
    }
}

void Texture::set_pixel(Screen *s, int x, int y, SDL_Color color){
    Uint32 *pixels = (Uint32*)this->surface->pixels; /* Nos pixels sont sur 32 bits */
    Uint32 couleur = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
    pixels[y * surface->w + x] = couleur;
    SDL_DestroyTexture(this->text);
    this->text = SDL_CreateTextureFromSurface(s->get_rend(), this->surface);
}

void Texture::set_pixel(Screen *s, int x, int y, Uint32 color){
    Uint32 *pixels = (Uint32*)this->surface->pixels; /* Nos pixels sont sur 32 bits */
    pixels[y * surface->w + x] = color;
}

void Texture::update(Screen *s){
    SDL_DestroyTexture(this->text);
    this->text = SDL_CreateTextureFromSurface(s->get_rend(), this->surface);
}

void Texture::blit(Screen *s, Texture * t, SDL_Rect * where){
    SDL_SetRenderTarget(s->get_rend(), this->text);
    SDL_RenderCopy(s->get_rend(), t->text, NULL, where);
    SDL_SetRenderTarget(s->get_rend(), NULL);
}

void Texture::clear(Screen *s, bool transparency){
    if (transparency){
        SDL_SetTextureBlendMode(this->text, SDL_BLENDMODE_BLEND);
    }
    SDL_SetRenderDrawColor(s->get_rend(), 0, 0, 0, 0);
    SDL_SetRenderTarget(s->get_rend(), this->text);
    SDL_RenderClear(s->get_rend());
    SDL_SetRenderTarget(s->get_rend(), NULL);
}

// =============================================================================
Button::Button(std::string str, Screen *s) : Texture(str, s){}

bool Button::is_click(int x, int y){
    return x >= cadre->x && x <= cadre->x+cadre->w && y >= cadre->y && y <= cadre->y+cadre->h;
}

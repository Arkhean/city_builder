#ifndef SCREEN_H
#define SCREEN_H

#define MIN_WIDTH 800
#define MIN_HEIGHT 600

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void init_SDL_TTF();
void quit_SDL_TTF();
void initRect(SDL_Rect *rectangle, int x, int y, int w, int h);
class Screen;

class Texture{
    protected :
        SDL_Rect * cadre;
        SDL_Surface * surface;
    public :
        SDL_Texture * text;
        int get_width();
        int get_height();
        Texture(Screen * s, int witdh, int height);
        Texture(std::string str, Screen * s, SDL_Color color={255,255,255,255});
        Texture(Texture const &) = delete;
        Texture& operator=(Texture const &) = delete;
        ~Texture();
        SDL_Rect * get_cadre();
        Uint32 get_pixel(int x, int y);
        void set_pixel(Screen *s, int x, int y, SDL_Color color);
        void set_pixel(Screen *s, int x, int y, Uint32 color);
        void update(Screen *s);
        void clear(Screen *s, bool transparency=false);
        void blit(Screen *s, Texture * t, SDL_Rect * where=NULL);
        SDL_PixelFormat * get_format(){return this->surface->format;}
};

// =============================================================================

class Screen{
    private :
        SDL_Window * ecran;
        SDL_Renderer * rend;
        SDL_Texture * frame;
        SDL_Rect * cadre;
    public :
        int get_width();
        int get_height();
        Screen(int width=MIN_WIDTH, int height=MIN_HEIGHT);
        Screen(Screen const &) = delete;
        Screen& operator=(Screen const &) = delete;
        ~Screen();
        void clear();
        SDL_Renderer * get_rend();
        // if where is null, blit cover the whole screen
        void blit_screen(Texture * t, SDL_Rect * where, SDL_Rect * partie=NULL);
        void update();
        void draw_line(int x1, int y1, int x2, int y2, SDL_Color color);
        void draw_circle(int x, int y, int r, SDL_Color color);
};

// =============================================================================

class Button : public Texture{
    private :

    public :
        Button(std::string str, Screen *s);
        bool is_click(int x, int y);
};



#endif

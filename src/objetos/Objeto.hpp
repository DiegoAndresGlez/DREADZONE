#pragma once
#include "Figuras.hpp"
#include "../utilidad/Estructuras.hpp"
#include "../motor/imagen/sprites.hpp"
#include "../motor/MouseOyente.hpp"
#include <SDL.h>


class Objeto
{
    protected:
        Figura* avatar;
        Sprite* sprite;
        Figura* col_box;
        float hp;
        Coordenadas posicion_mundo;
        Coordenadas posicion_camara;
        bool tiene_fisica;
        SDL_Color color;
        
    public:
        bool en_colision;
        bool render_colbox;
        bool eliminarme{false};

    public:
        virtual ~Objeto(){};
        virtual void update(double dt)=0;
        void render(SDL_Renderer *r);
        void render_ang(SDL_Renderer *r, Coordenadas target);
        Figura* get_avatar()const{return avatar;};
        Figura* get_colbox()const{return col_box;};
        float get_hp()const{return hp;};
        void set_hp(float v){hp=v;};
        Coordenadas get_posicion_mundo()const{return posicion_mundo;};
        Coordenadas get_posicion_camara()const{return posicion_camara;};
        int get_posx()const{return posicion_mundo.x;};
        int get_posy()const{return posicion_mundo.y;};
        void set_posicion_mundo(Coordenadas p);
        void set_posicion_camara(Coordenadas p);
        void set_posx(int x);
        void set_posy(int y);
        SDL_Color get_color()const{return color;};
        void set_color(SDL_Color c){color=c;};
        void set_eliminarme(bool b){eliminarme=b;};
        bool get_eliminarme()const{return eliminarme;};

        Sprite * get_sprite()const{return sprite;};

};
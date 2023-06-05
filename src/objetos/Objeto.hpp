#pragma once
#include "Figuras.hpp"
#include "../utilidad/Estructuras.hpp"
#include "../motor/imagen/sprites.hpp"
#include "../motor/imagen/tiles.hpp"
#include <SDL.h>

class Objeto
{
    protected:
        Figura* avatar;
        Sprite* sprite;
        Tile *tile;
        Figura* col_box;
        Coordenadas posicion_mundo;
        Coordenadas posicion_camara;
        bool tiene_fisica;
        SDL_Color color;
        int hp{100};
        
    public:
        bool en_colision;
        bool en_colision_bala_enemigo;
        bool en_colision_enemigo_jugador;
        bool render_colbox;
        int velocidad_camara{1};
        bool eliminarme{false};
        bool proyectable{true};
        bool estaMuerto{false};

    public:
        virtual ~Objeto(){};
        virtual void update(double dt)=0;
        void render(SDL_Renderer *r);
        void render_ang(SDL_Renderer *r, Coordenadas target);
        Figura* get_avatar()const{return avatar;};
        Figura* get_colbox()const{return col_box;};
        Coordenadas get_posicion_mundo()const{return posicion_mundo;};
        Coordenadas get_posicion_camara()const{return posicion_camara;};
        int get_posx()const{return posicion_mundo.x;};
        int get_posy()const{return posicion_mundo.y;};
        void set_posicion_mundo(Coordenadas p);
        void set_posicion_camara(Coordenadas p);
        void set_posx(int x);
        void set_posy(int y);
        void set_muerto(bool v){estaMuerto=v;};
        bool get_muerto()const{return estaMuerto;};
        int get_hp()const{return hp;};
        void set_hp(float v){hp=v;};
        SDL_Color get_color()const{return color;};
        void set_color(SDL_Color c){color=c;};
        bool get_tiene_fisica()const{return tiene_fisica;};
        void set_tiene_fisica(bool b){tiene_fisica=b;};
        void set_eliminarme(bool b){eliminarme=b;};
        bool get_eliminarme()const{return eliminarme;};

        Sprite * get_sprite()const{return sprite;};
        Tile * get_tile()const{return tile;};

};
#include "ObjetoEstatico.hpp"
#include <iostream>

Plataformas::Plataformas(int x, int y, int w, int h, SDL_Color color)
:ObjetoEstatico{} //llamar constructor padre
{
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    posicion_camara.x=x;
    posicion_camara.y=y;
    avatar = new Rectangulo(x,y,w,h,color);
    avatar->set_rellenocolor(color);
    avatar->set_serellena(false);
    col_box = new Rectangulo(x,y,w+5,h+5,{0,255,0,255});
    tiene_fisica=false;
    en_colision=false;
    sprite = nullptr;
};

Plataformas::Plataformas(TileInfo tiles, bool colision)
{
    avatar=nullptr;
    sprite = nullptr;
    posicion_mundo = tiles.pos;
    col_box = new Rectangulo(posicion_mundo.x-(tiles.width/2),posicion_mundo.y-(tiles.height/2),tiles.width,tiles.height,{0,255,0,255});
    tiene_fisica=colision;
    en_colision=false;
    tile = new Tile(tiles);
    
};

void Plataformas::update(double dt)
{
    if (posicion_mundo.x < -30)
    {
        this->set_posicion_mundo({get_posicion_mundo().x+1440, get_posicion_mundo().y});
    }else if (posicion_mundo.x > 1350)
    {
        this->set_posicion_mundo({get_posicion_mundo().x-1440, get_posicion_mundo().y});
    }
};

Fondo::Fondo(int x, int y, int w, int h, std::string path_sprite) 
:ObjetoEstatico{} //llamar constructor padre
{
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,w,h,color);
    avatar->set_rellenocolor(color);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,w+5,h+5,{0,255,0,255});
    tiene_fisica=false;
    en_colision=false;
    sprite = new Sprite(path_sprite,posicion_mundo,w,h,w,h);
    velocidad_camara = 3;
};

void Fondo::cargar_textura(SDL_Renderer *r)
{
    sprite->cargar_textura(r);
};

void Fondo::update(double dt)
{
    if (posicion_mundo.x >= 2400 )
    {
        this->set_posicion_camara({0, get_posicion_mundo().y});
        std::cout << "CAMBIO DE POSICION" << std::endl;
    }
    else if (posicion_mundo.x <= -1370)
    {
        this->set_posicion_camara({1028, get_posicion_mundo().y});
        std::cout << "CAMBIO DE POSICION" << std::endl;
    }
};

Nave::Nave(int x, int y, int w, int h, std::string path_sprite)
{
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,w,h,color);
    avatar->set_rellenocolor(color);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,w+5,h+5,{0,255,0,255});
    tiene_fisica=false;
    en_colision=false;
    sprite = new Sprite(path_sprite,posicion_mundo,w,h,w,h);
}

void Nave::cargar_textura(SDL_Renderer *r)
{
    sprite->cargar_textura(r);
};

void Nave::update(double dt)
{
    this->set_posicion_camara({posicion_mundo.x, posicion_mundo.y});
};
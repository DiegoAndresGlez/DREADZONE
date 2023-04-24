#include "ObjetoEstatico.hpp"

Plataformas::Plataformas(int x, int y, int w, int h, SDL_Color color)
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
};

void Plataformas::update(double dt)
{

};
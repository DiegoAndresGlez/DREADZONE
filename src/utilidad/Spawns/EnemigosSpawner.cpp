#include "EnemigosSpawner.hpp"
#include "../Tiempo.hpp"
#include "../Func_aux.hpp"
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include<iostream>
#include<cstdlib>

EnemigosSpawner::EnemigosSpawner(std::string path_sprite, float vida, int x, int y, int w, int h, int sw, int sh, Jugador* player, SDL_Color c, Pipeline &p)
{
    this->sprite_path=path_sprite;
    colordebug=c;
    this->vida=vida; // vida
    this->x=x; // pos x
    this->y=y; // pos y
    this->w=w; // ancho sprite
    this->h=h; // alto sprite
    this->sw=sw;// ancho mostrar sprite
    this->sh=sh;// alto mostrar sprite
    this->player=player; // jugador
    objetos_activos=0;
    delay=10; 
    init_tiempo=Tiempo::get_tiempo();
    check=false;
    this->contador_muertes = 0;
    pipeline = &p;
    velocidad=0;
    spawnminimo = 3;
    velocidad_decremento = 60;
};

void EnemigosSpawner::spawn(std::vector<Objeto*>*lista)
{
    Enemigo * nuevo = new Enemigo(sprite_path,vida,x,y,w,h,sw,sh,player,colordebug);
    nuevo->set_ref_player(player);
    pipeline->cargar_texturas(nuevo->get_sprite());
    lista->push_back(nuevo);
    objetos_activos++;
};
void EnemigosSpawner::set_velocidad(int v)
{
    delay=v;
}
void EnemigosSpawner::despawn(std::vector<Objeto*>*lista)
{
    int id = lista->size()-objetos_activos;
    delete lista->at(id);
    objetos_activos--;
    lista->erase(std::next(lista->begin()+id-1));
};
void EnemigosSpawner::update(std::vector<Objeto*>*lista)
{
    double dt =  Tiempo::get_tiempo() - init_tiempo;

    //DEBUGPRINT(dt)
    //DEBUGPRINT(past_tiempo)
    if((int)dt!=0 && ((int)dt)%delay == 0 && check==false)
    {
        
        spawn(lista);
        past_tiempo=dt;
        check=true;
        DEBUGPRINT(std::to_string(dt)+" SPWAN "+std::to_string(objetos_activos))
        DEBUGCOOR(lista->at(lista->size()-1)->get_posicion_mundo());
    }

    if((int)dt!=0 && ((int)dt)%velocidad_decremento == 0 && check==false && delay>spawnminimo)
    {
        delay--;
    }
    
    
    // if((int)dt!=0 && (int)dt%(delay*2) == 0 && !check)
    // {
        
    // }

    
    
    //DEBUGPRINT(past_tiempo)
    //DEBUGPRINT((int)dt)
    if((int)dt>past_tiempo)
    {    
        check=false;
    }

};
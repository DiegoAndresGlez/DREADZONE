#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/Pipeline.hpp"
#include <SDL.h>

class EnemigosSpawner
{
    public:
        EnemigosSpawner(std::string path_sprite, float vida, int x, int y, int w, int h, int sw, int sh, Jugador* player, SDL_Color c, Pipeline &p, int& contador_muerte);

        void spawn(std::vector<Objeto*>*lista);
        void despawn(std::vector<Objeto*>*lista);
        void update(std::vector<Objeto*>*lista);
        void set_velocidad(int v);
    private:
        std::vector<Objeto*> objetos;
        std::string sprite_path;
        SDL_Color colordebug;
        float vida;
        int x; // pos x
        int y; // pos y
        int w; // ancho sprite
        int h; // alto sprite
        int sw;// ancho mostrar sprite
        int sh;// alto mostrar sprite
        int objetos_activos;
        int delay;
        int *contador_muertes;
        Jugador* player;
        double init_tiempo;
        int past_tiempo;
        bool check;
        Pipeline *pipeline;
        int velocidad;
        int spawnminimo;
        int velocidad_decremento;

};
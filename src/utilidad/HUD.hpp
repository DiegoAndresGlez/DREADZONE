#include"RenderTexto.hpp"
#include"Tiempo.hpp"
#include<SDL.h>
#include"../objetos_dinamicos/ObjetoDinamico.hpp"

class HUD
{
    private:
        Jugador* player;
        SDL_Renderer *ren;
        int contador_muertos;
    public:
        HUD(Jugador* player, SDL_Renderer* ren);
        ~HUD();
        double init_tiempo;
        int past_tiempo;
        void update_vida_jugador();
        void update_tiempo();
        void update_enemigos_muertos(int enemigos_muertos);
        void game_over();
};
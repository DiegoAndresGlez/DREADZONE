#include"RenderTexto.hpp"
#include"Tiempo.hpp"
#include<SDL.h>
#include"../objetos_dinamicos/ObjetoDinamico.hpp"

class HUD
{
    private:
        Jugador* player;
        SDL_Renderer *ren;
    public:
        HUD(Jugador* player, SDL_Renderer* ren);
        ~HUD();
        void update_vida_jugador();
        void update_tiempo();
};
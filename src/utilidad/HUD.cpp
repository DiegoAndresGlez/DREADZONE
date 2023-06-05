#include "HUD.hpp"
#include"Tiempo.hpp"

HUD::HUD(Jugador* player, SDL_Renderer* ren)
{
    this->player = player;
    this->ren = ren;
    init_tiempo = Tiempo::get_tiempo();
    this->contador_muertos = 0;
}

void HUD::update_vida_jugador()
{
    if(player->get_hp() < 0){
        RenderTexto::get().render_texto(ren,15,15, "HP: 0",64,30, SDL_Color{0, 255, 255});
    }else{
        RenderTexto::get().render_texto(ren,15,15, "HP: " + std::to_string(player->get_hp()),64,30, SDL_Color{0, 255, 255});
    }
}

void HUD::update_tiempo()
{
    double dt =  Tiempo::get_tiempo() - init_tiempo;
    RenderTexto::get().render_texto(ren,15,80, "Timer: " + std::to_string((int)dt),100,30, SDL_Color{0, 255, 255});
}

void HUD::update_enemigos_muertos(int enemigos_muertos)
{
    RenderTexto::get().render_texto(ren,15,45, "Puntaje: " + std::to_string(enemigos_muertos*10),130,30, SDL_Color{0, 255, 255});
}

void HUD::game_over()
{
    RenderTexto::get().render_texto(ren,300,300, "GAME OVER",390,90, SDL_Color{255, 0, 0});
}

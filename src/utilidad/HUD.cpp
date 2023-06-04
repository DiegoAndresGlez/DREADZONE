#include "HUD.hpp"

HUD::HUD(Jugador* player, SDL_Renderer* ren)
{
    this->player = player;
    this->ren = ren;
}

void HUD::update_vida_jugador()
{
    RenderTexto::get().render_texto(ren,15,15, "HP: " + std::to_string(player->get_hp()),64,30, SDL_Color{0, 255, 255});
}

void HUD::update_tiempo()
{
    
}
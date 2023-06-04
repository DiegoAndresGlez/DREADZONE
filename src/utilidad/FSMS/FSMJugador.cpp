#include "FSMJugador.hpp"
#include "../../motor/MouseOyente.hpp"
#include "../Func_aux.hpp"
#include<SDL.h>
#include<iostream>
#include <sstream>
#include <cmath>

/*
IDLE
*/
EstadoJugadorIDLE::EstadoJugadorIDLE()
{
    strnombre = "IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=1;
};

FSMJugador* EstadoJugadorIDLE::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});

    return NULL;
};
void EstadoJugadorIDLE::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=1;
    timer = Tiempo::get_tiempo();
};
void EstadoJugadorIDLE::salir(Jugador& player)
{
    timer = 0;
};
void EstadoJugadorIDLE::update(Jugador& player,double dt)
{
    if(MouseOyente::get().getBotones()[SDL_BUTTON_LEFT-1] == true){
        player.shoot();
        //printf("x: %d - y: %d\n", MouseOyente::getX(), MouseOyente::getY());
    }

    if(player.en_colision_enemigo_jugador){
        timer += Tiempo::get_tiempo() - timer;
        if((int)timer%delay ==0 && (int)timer!=0 && (int)timer > past_time){
            int dano = 5;
            int hp = player.get_hp();
            player.set_hp(hp - dano);
            printf("VIDA JUGADOR: %d\n", player.get_hp());
            contador++;
            past_time = timer;
            player.en_colision_enemigo_jugador = false;
        }
    }


    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;

};

/*
MOVER
*/
EstadoJugadorMOVER::EstadoJugadorMOVER(Coordenadas dir)
{
    strnombre = "MOVER";
    direccion = dir;
    velocidad = 5;
    frames_actual_ani=0;
    frames_maxim_ani=8;
};

FSMJugador* EstadoJugadorMOVER::input_handle(KeyOyente& input, MouseOyente& mouse)
{

    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,-1});
    

    /*
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});
    */
    //buggy
    
    if(input.nadaPresionado())
        return new EstadoJugadorIDLE();
    

    return NULL;
};
void EstadoJugadorMOVER::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=8;
    timer = Tiempo::get_tiempo();
};
void EstadoJugadorMOVER::salir(Jugador& player){timer = 0;};
void EstadoJugadorMOVER::update(Jugador& player,double dt)
{
    Coordenadas p = player.get_posicion_mundo();

    p.x += (velocidad*direccion.x);
    p.y += (velocidad*direccion.y);

    player.set_posicion_camara(p);

    if(MouseOyente::get().getBotones()[SDL_BUTTON_LEFT-1] == true){
        player.shoot();
        //printf("x: %d - y: %d\n", MouseOyente::getX(), MouseOyente::getY());
    }

    if(player.en_colision_enemigo_jugador){
        timer += Tiempo::get_tiempo() - timer;
        if((int)timer%delay ==0 && (int)timer!=0 && (int)timer > past_time){
            int dano = 5;
            int hp = player.get_hp();
            player.set_hp(hp - dano);
            printf("VIDA JUGADOR: %d\n", player.get_hp());
            contador++;
            past_time = timer;
            player.en_colision_enemigo_jugador = false;
        }
    }


    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};


/*INVULNERABLE IDLE*/
EstadoJugadorINVULNERABLEIDLE::EstadoJugadorINVULNERABLEIDLE()
{
    strnombre = "INVULNERABLE IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=1;
};

void EstadoJugadorINVULNERABLEIDLE::update(Jugador& player,double dt)
{
    timer += Tiempo::get_tiempo() - timer;
    if((int)timer%delay ==0 && (int)timer!=0 && (int)timer > past_time){
        contador++;
        past_time = timer;
    }

    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};

void EstadoJugadorINVULNERABLEIDLE::entrar(Jugador& player){
    frames_actual_ani=0;
    frames_maxim_ani=5;
    timer = Tiempo::get_tiempo();
};

void EstadoJugadorINVULNERABLEIDLE::salir(Jugador& player){timer = 0;};


FSMJugador* EstadoJugadorINVULNERABLEIDLE::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,-1});
    
    if(input.nadaPresionado())
        return new EstadoJugadorINVULNERABLEIDLE();
    return NULL;
};

/*INVULNERABLE MOVER*/
EstadoJugadorINVULNERABLEMOVER::EstadoJugadorINVULNERABLEMOVER(Coordenadas dir)
{
    strnombre = "INVULNERABLE MOVER";
    direccion = dir;
    frames_actual_ani=0;
    frames_maxim_ani=5;
};

void EstadoJugadorINVULNERABLEMOVER::update(Jugador& player,double dt)
{
    timer += Tiempo::get_tiempo() - timer;
    if((int)timer%delay ==0 && (int)timer!=0 && (int)timer > past_time){
        contador++;
        past_time = timer;
    }

    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};

void EstadoJugadorINVULNERABLEMOVER::entrar(Jugador& player){
    frames_actual_ani=0;
    frames_maxim_ani=5;
    timer = Tiempo::get_tiempo();
};

void EstadoJugadorINVULNERABLEMOVER::salir(Jugador& player){timer = 0;};

FSMJugador* EstadoJugadorINVULNERABLEMOVER::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_D) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({-1,-1});
    if(input.estaPresionado(SDL_SCANCODE_A) && input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,-1});
    
    if(input.nadaPresionado())
        return new EstadoJugadorINVULNERABLEIDLE();
    return NULL;
};

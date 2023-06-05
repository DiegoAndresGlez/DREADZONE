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
    if(estaMuertoFSM){
        return new EstadoJugadorMORIR();
    }

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
    if(player.estaMuerto){
        estaMuertoFSM=true;
    }

    if(MouseOyente::get().getBotones()[SDL_BUTTON_LEFT-1] == true){
        player.shoot();
        //printf("x: %d - y: %d\n", MouseOyente::getX(), MouseOyente::getY());
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
    if(estaMuertoFSM){
        return new EstadoJugadorMORIR();
    }

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
    if(player.estaMuerto){
        estaMuertoFSM=true;
    }

    Coordenadas p = player.get_posicion_mundo();

    p.x += (velocidad*direccion.x);
    p.y += (velocidad*direccion.y);

    player.set_posicion_camara(p);

    if(MouseOyente::get().getBotones()[SDL_BUTTON_LEFT-1] == true){
        player.shoot();
        //printf("x: %d - y: %d\n", MouseOyente::getX(), MouseOyente::getY());
    }

    player.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
};

/*MORIR*/
EstadoJugadorMORIR::EstadoJugadorMORIR()
{
    strnombre = "MORIR";
    frames_actual_ani=0;
    frames_maxim_ani=3;
};

FSMJugador* EstadoJugadorMORIR::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    return NULL;
};

void EstadoJugadorMORIR::entrar(Jugador& player)
{
    frames_actual_ani=0;
    frames_maxim_ani=3;
    timer = Tiempo::get_tiempo();
};

void EstadoJugadorMORIR::salir(Jugador& player){timer = 0;};

void EstadoJugadorMORIR::update(Jugador& player, double dt)
{
    if(frames_actual_ani == frames_maxim_ani){
        player.get_sprite()->play_frame(1, 2);
    }else{
        player.get_sprite()->play_frame(1, frames_actual_ani % frames_maxim_ani);

        if(frame_dt > 7){ 
            frame_dt = 0;
            frames_actual_ani++;
            //Bala *bala = new Bala(25, 30, 30, SDL_Color{0,0,0});
        }
        frame_dt++;
    }
};


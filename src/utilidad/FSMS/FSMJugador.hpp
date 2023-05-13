#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include<string>
#include<vector>

class Jugador; //forward declaration
class FSMJugador
{
    protected:
        std::string strnombre;
        int timer{0};
    
    public:
        virtual ~FSMJugador(){};
        virtual FSMJugador* input_handle(KeyOyente& input, MouseOyente& mouse)=0;
        virtual void entrar(Jugador& player)=0;
        virtual void salir(Jugador& player)=0;
        virtual void update(Jugador& player,double dt)=0;
        std::string get_namestate()const{return strnombre;};
};

class EstadoJugadorIDLE : public FSMJugador
{
    public:
        EstadoJugadorIDLE();
        virtual ~EstadoJugadorIDLE(){};
        FSMJugador* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
    
    
};

class EstadoJugadorMOVERDER : public FSMJugador
{
    public:
        EstadoJugadorMOVERDER(Coordenadas dir);
        virtual ~EstadoJugadorMOVERDER(){};
        FSMJugador* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};  
};

class EstadoJugadorIDLEIZQ : public FSMJugador
{
    public:
        EstadoJugadorIDLEIZQ();
        virtual ~EstadoJugadorIDLEIZQ(){};
        FSMJugador* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
    
    
};

class EstadoJugadorMOVERIZQ : public FSMJugador
{
    public:
        EstadoJugadorMOVERIZQ(Coordenadas dir);
        virtual ~EstadoJugadorMOVERIZQ(){};
        FSMJugador* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};  
};

class EstadoJugadorSHOOT : public FSMJugador
{
    public:
        EstadoJugadorSHOOT(Coordenadas dir);
        virtual ~EstadoJugadorSHOOT(){};
        FSMJugador *input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Jugador& player);
        void salir(Jugador& player);
        void update(Jugador& player, double dt);
        //std::vector<Bala*> get_listaBalas(){return balas;};
    private:
        Coordenadas direccion;
        //std::vector<Bala*> balas;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};
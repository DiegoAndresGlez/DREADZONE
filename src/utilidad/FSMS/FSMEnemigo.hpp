#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include<string>
#include<vector>

class Enemigo; //forward declaration
class FSMEnemigo
{
    protected:
        std::string strnombre;
        int timer{0};
    
    public:
        virtual ~FSMEnemigo(){};
        virtual FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse)=0;
        virtual void entrar(Enemigo& enemigo)=0;
        virtual void salir(Enemigo& enemigo)=0;
        virtual void update(Enemigo& enemigo,double dt)=0;
        std::string get_namestate()const{return strnombre;};
};

class EstadoEnemigoIDLE : public FSMEnemigo
{
    public:
        EstadoEnemigoIDLE();
        virtual ~EstadoEnemigoIDLE(){};
        FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Enemigo& enemigo);
        void salir(Enemigo& enemigo);
        void update(Enemigo& enemigo,double dt);
    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};

class EstadoEnemigoMOVER : public FSMEnemigo
{
    public:
        EstadoEnemigoMOVER(Coordenadas dir);
        virtual ~EstadoEnemigoMOVER(){};
        FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Enemigo& enemigo);
        void salir(Enemigo& enemigo);
        void update(Enemigo& enemigo,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};  
};
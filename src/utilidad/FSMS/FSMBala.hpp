#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include "../../motor/camaras/Camaras.hpp"
#include<string>
#include<vector>

class Bala; //forward declaration
class Camara;
class FSMBala
{
    protected:
        std::string strnombre;
        int timer{0};
    
    public:
        virtual ~FSMBala(){};
        virtual FSMBala* input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam)=0;
        virtual void entrar(Bala& bala)=0;
        virtual void salir(Bala& bala)=0;
        virtual void update(Bala& bala,double dt)=0;
        std::string get_namestate()const{return strnombre;};
};

class EstadoBalaIDLE : public FSMBala
{
    public:
        EstadoBalaIDLE();
        virtual ~EstadoBalaIDLE(){};
        FSMBala* input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam);
        void entrar(Bala& bala);
        void salir(Bala& bala);
        void update(Bala& bala,double dt);
    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};

class EstadoBalaMOVER : public FSMBala
{
    public:
        EstadoBalaMOVER(Coordenadas dir);
        virtual ~EstadoBalaMOVER(){};
        FSMBala* input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam);
        void entrar(Bala& bala);
        void salir(Bala& bala);
        void update(Bala& bala,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};  
};
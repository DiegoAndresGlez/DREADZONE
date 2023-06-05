#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
class Nave;
class FSMNave
{
    protected:
        std::string strnombre;
    
    public:
        virtual ~FSMNave(){};
        virtual FSMNave* input_handle(KeyOyente& input, MouseOyente& mouse)=0;
        virtual void entrar(Nave& nave)=0;
        virtual void salir(Nave& nave)=0;
        virtual void update(Nave& nave,double dt)=0;
        std::string get_namestate()const{return strnombre;};
};

class EstadoNavePLAY : public FSMNave
{
    public:
        EstadoNavePLAY();
        virtual ~EstadoNavePLAY(){};
        FSMNave* input_handle(KeyOyente& input, MouseOyente& mouse);
        void entrar(Nave& nave);
        void salir(Nave& nave);
        void update(Nave& nave,double dt);
    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};
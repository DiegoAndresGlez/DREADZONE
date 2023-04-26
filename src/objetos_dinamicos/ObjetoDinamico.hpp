#pragma once
#include "../objetos/Objeto.hpp"
#include "../motor/KeyOyente.hpp"
#include "../motor/MouseOyente.hpp"
#include "../utilidad/FSMS/FSMJugador.hpp"
#include "../utilidad/FSMS/FSMEnemigo.hpp"
#include<SDL.h>
#include<string>
class FSMJugador;//forward declaration
class FSMEnemigo;
class ObjetoDinamico : public Objeto
{
    public:
        virtual ~ObjetoDinamico(){};
        virtual void update(double dt)=0;
        float get_dtgf()const{return dtgravedad;};
        void set_dtgf(float v){dtgravedad=v;};

        //forma general de convertir cualquier puntero si se conoce la clase
        virtual void set_estado(void* estado)=0;
        virtual void* get_estado()=0;

        Coordenadas offsetoverlap;
    protected:
        float dtgravedad{0};
        
};


class Jugador : public ObjetoDinamico
{
    public:
        virtual ~Jugador(){};
        Jugador(float vida, int x, int y,SDL_Color c );
        Jugador(std::string path_sprite,float vida, int x, int y, int w, int h,int sw,int sh, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();
    private:
        FSMJugador* estado_actual;
        Coordenadas piso;
        
};

/*ENEMIGO*/
class Enemigo : public ObjetoDinamico
{
    public:
        virtual ~Enemigo(){};
        Enemigo(float vida, int x, int y,SDL_Color c);
        Enemigo(std::string path_sprite,float vida, int x, int y, int w, int h,int sw,int sh, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};
        
        void set_estado(void* estado);
        void* get_estado();
    private:
        FSMEnemigo* estado_actual;
        Coordenadas piso;
};


/*BALA*/

class Bala : public ObjetoDinamico
{
    public:
        virtual ~Bala(){};
        Bala(int dano, int x, int y, SDL_Color c);
        Bala(std::string path_sprite, int dano, int x, int y, int w, int h, int sw, int sh, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        //std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};
        void set_estado(void* estado); 
        void* get_estado();
    private:
        //FSMBala
        int dmg;
        Coordenadas piso;
};


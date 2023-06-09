#pragma once
#include "../objetos/Objeto.hpp"
#include "../motor/KeyOyente.hpp"
#include "../motor/MouseOyente.hpp"
#include "../motor/camaras/Camaras.hpp"
#include "../utilidad/FSMS/FSMJugador.hpp"
#include "../utilidad/FSMS/FSMEnemigo.hpp"
#include "../utilidad/FSMS/FSMBala.hpp"
#include "../utilidad/FSMS/FSMNave.hpp"
#include<SDL.h>
#include<string>
#include<chrono>
#include<thread>
class FSMJugador;//forward declaration
class FSMEnemigo;
class FSMBala;
class FSMNave;
class Jugador;
class Enemigo;
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

/*ENEMIGO*/
class Enemigo : public ObjetoDinamico
{
    public:
        virtual ~Enemigo(){};
        Enemigo(float vida, int x, int y,SDL_Color c);
        Enemigo(std::string path_sprite,float vida, int x, int y, int w, int h,int sw,int sh, Jugador* player, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};
        
        void set_estado(void* estado);
        void* get_estado();
        
        void set_ref_player(Jugador* player){ref_player = player;};
        Jugador* get_ref_player()const{return ref_player;};

    private:
        FSMEnemigo* estado_actual;
        Jugador* ref_player;
        Coordenadas piso;
};

/*BALA*/
class Bala : public ObjetoDinamico
{
    public:
        virtual ~Bala(){};
        Bala(int dano, int x, int y, SDL_Color c);
        Bala(std::string path_sprite, int dano, int x, int y, int w, int h, int sw, int sh, Coordenadas player, Coordenadas mouse_dir, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse,Camara& camara);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};
        void set_estado(void* estado); 
        void* get_estado();
        Coordenadas get_player_pos()const{return player_pos;};
        Coordenadas get_direccion_bala()const{return direccion_bala;};

    private:
        int dmg;
        int velocidad_x;
        int velocidad_y;
        Coordenadas player_pos;
        Coordenadas direccion_bala;
        FSMBala* estado_actual;
        Coordenadas piso;
};

/*JUGADOR*/
class Jugador : public ObjetoDinamico
{
    public:
        virtual ~Jugador(){};
        Jugador(float vida, int x, int y,SDL_Color c );
        Jugador(std::string path_sprite,float vida, int x, int y, int w, int h,int sw,int sh, SDL_Color c );
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();

        std::vector<Bala*> getListaBalas()const{return lista_balas;};
        void shoot(); //disparar
        bool canShoot(); //checar si puede disparar, si no ha pasado el tiempo de fire_rate
        void eliminarBalas();
    private:
        FSMJugador* estado_actual;
        Coordenadas piso;

        Bala* temp_bala;
        std::vector<Bala*> lista_balas;
        int fire_rate{3}; //disparos por segundo
        std::chrono::steady_clock::time_point tiempoUltimoDisparo;
        
};


/*NAVE*/
class Nave : public ObjetoDinamico
{
    public:
        virtual ~Nave(){};
        Nave(std::string path_sprite, float vida, int x, int y, int w, int h,int sw,int sh, SDL_Color c);
        void update(double dt);
        void input_handle(KeyOyente& input,MouseOyente& mouse);
        std::string get_strEstado();
        Coordenadas get_piso()const{return piso;};
        void set_piso(Coordenadas p){piso = p;};

        void set_estado(void* estado);
        void* get_estado();

    private:
        FSMNave* estado_actual;
        Coordenadas piso;
};

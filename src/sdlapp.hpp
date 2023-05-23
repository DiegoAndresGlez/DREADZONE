#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "motor/Pipeline.hpp"
#include "objetos_dinamicos/ObjetoDinamico.hpp"
#include "objetos_estaticos/ObjetoEstatico.hpp"
#include "motor/camaras/ManejadorCamara.hpp"
#include "motor/imagen/atlas.hpp"

class SDLApp
{
    private:
        SDLApp();   
        bool on_init();
        void on_evento(SDL_Event *evento);
        void on_fisicaupdate(double dt); 
        void on_frameupdate(double dt); 
        void on_limpiar();

        bool esta_corriendo;
        int WIDTH;
        int HEIGHT;

        SDL_Window* vnt;
        SDL_Surface* vntsurf;
        SDL_Renderer* render;

        //singleton
        static SDLApp* instancia;

        //02_lineas_figuras
        Pipeline *ensamble;
    
        //a03_Maquinas_estados.
        double maxFPS;
        double msfrecuencia;
        int fps;

        //05_Colisiones
        Jugador* player;
        Enemigo* enemigo;
        std::vector<ObjetoEstatico*> plataformas;

        //06_Camaras
        Camara* camara_principal;
        std::vector<Objeto*> objetos;
        std::vector<Objeto*> objetos_ang;
        std::vector<Objeto*> enemigos_ang;
        std::vector<Objeto*> lista_balas;
        //08 tiles
        Atlas *mapa;

        //09_Fondo
        Fondo *fondo;
    
    public:
        SDL_Color bg_color;
        static int on_correr();
        static void set_bgcolor(Uint8 rojo,Uint8 verde,Uint8 azul);
        static SDLApp& get();
        static bool estaCorriendo() {return get().esta_corriendo;};
};
#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "motor/Pipeline.hpp"
#include "objetos_dinamicos/ObjetoDinamico.hpp"
#include "objetos_estaticos/ObjetoEstatico.hpp"
#include "motor/camaras/ManejadorCamara.hpp"
#include "motor/imagen/atlas.hpp"
#include "utilidad/HUD.hpp"
#include "utilidad/Spawns/EnemigosSpawner.hpp"

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

        double timer{0};
        double past_time{0};
        int contador{0};
        int delay{1};

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
        Enemigo* enemigo2;
        Enemigo* enemigo3;

        ObjetoEstatico* nave;
        EnemigosSpawner* enespawner;
        std::vector<ObjetoEstatico*> plataformas;

        //06_Camaras
        Camara* camara_principal;
        std::vector<Objeto*> objetos;
        std::vector<Objeto*> objetos_ang;
        std::vector<Objeto*> enemigos_ang;
        std::vector<Objeto*> enemigos_muertos;
        
        //08 tiles
        Atlas *mapa;
        
        //09_Fondo
        Fondo *fondo;

        HUD *hud;
    
    public:
        SDL_Color bg_color;
        static int on_correr();
        static void set_bgcolor(Uint8 rojo,Uint8 verde,Uint8 azul);
        static SDLApp& get();
        static bool estaCorriendo() {return get().esta_corriendo;};
        void update_player_hp();
        void colision_enemigos_player(std::vector<Objeto*> enemigos_ang, Jugador* player);
        void colision_enemigos_a_enemigos(std::vector<Objeto*> enemigos_ang);
        void colision_bala_a_enemigos(std::vector<Objeto*> enemigos, Jugador* player);
        void colision_plataformas_player(std::vector<ObjetoEstatico*> plataformas, Jugador* player);
        void update_enemigos(double dt);
        void eliminarEnemigos();
        void eliminarBalas();
};
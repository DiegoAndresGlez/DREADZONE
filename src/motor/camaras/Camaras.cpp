#include "Camaras.hpp"
#include "../../utilidad/Func_aux.hpp"
#include <iostream>

Camara::Camara(int x, int y, int w, int h, SDL_Renderer &view)
{
    // se considera que la camara empieza en 0,0 y es toda la pantalla
    // si se quiere centrar hay que desplazar w y h en todos los cálculos.
    width =w;
    height=h;
    pos_mundo = {x,y};
    pos_centro = {x+w/2,y+h/2};

    cruz.push_back({x,y+h/2});
    cruz.push_back({x+w,y+h/2});
    cruz.push_back({x+w/2,y});
    cruz.push_back({x+w/2,y+h});

    viewport = &view;
    objensamble = new Pipeline(view);
    velocidad =10.f;
    estado_actual = new EstadoCamaraTransicion();
};

Camara::~Camara()
{
    SDL_DestroyRenderer(viewport);
    delete objensamble;
    delete estado_actual;
    delete objeto_seguir;
};

void Camara::render_cross()
{
    objensamble->lineas(cruz,{0,255,0,180});
};

void Camara::lock_objeto(Objeto &obj)
{
    //Alumnos implementarla
    objeto_seguir = &obj;
    lock =1;
    
};

void Camara::unluck_objeto()
{
    //Alumnos implementarla
    objeto_seguir = nullptr;
    lock=0;
};

void Camara::proyectar(std::vector<Objeto*> objetos)
{
    //Alumnos implementarla 
    for(auto &o:objetos)
    {
        if (o->proyectable)
        {    
            Coordenadas posM = o->get_posicion_mundo();
            posM.x -=(int)(pos_mundo.x / o->velocidad_camara);
            posM.y -=(int)(pos_mundo.y / o->velocidad_camara);
            o->set_posicion_camara(posM);
        }
        
        //DEBUGCOOR(posM)
    }
    //DEBUGPRINT("_____")
    
};

void Camara::renderizar(std::vector<Objeto*>objetos)
{
    for(auto& o:objetos)
    {
        o->render(viewport);
    }
};

void Camara::renderizar_ang(std::vector<Objeto*>objetos, Coordenadas target)
{
    for(auto& o:objetos)
    {
        o->render_ang(viewport,target);
    }
};

void Camara::set_posicion_mundo(Coordenadas np)
{
    pos_mundo = np;
};
void Camara::set_posicion_centro(Coordenadas np)
{
    pos_centro = np;
};
void Camara::input_handle(KeyOyente &input, MouseOyente &mouse)
{
    if(!estado_actual)
        return; //estado nulo al inicio
    
    FSMCamara* estado = estado_actual->input_handle(*this,input,mouse);
    if(estado)
    {
        estado_actual->on_salir(*this);
        delete estado_actual;
        estado_actual = estado;
        estado_actual->on_entrar(*this);
    }
};

void Camara::update()
{
    if(estado_actual)
        estado_actual->on_update(*this);
};

void Camara::set_estado(void* nuevo)
{
    estado_actual->on_salir(*this);
    delete estado_actual;
    estado_actual = (FSMCamara*)nuevo;
    estado_actual->on_entrar(*this);
};
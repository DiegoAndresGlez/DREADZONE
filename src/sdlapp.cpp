#include "sdlapp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
#include <SDL_ttf.h>
#include "utilidad/RenderTexto.hpp"
#include "motor/fisica/MotorFisico.hpp"
#include <cmath>

//#define RECTANGULOS
//#define TRIANGULOS
//#define CIRCULOS

SDLApp* SDLApp::instancia = 0;

SDLApp::SDLApp()
{
    vnt = nullptr;
    vntsurf = nullptr;
    render = nullptr;
    ensamble= nullptr;
    bg_color.r = 255; //rojo
    bg_color.g = 255; //verde
    bg_color.b = 255; //azul
    bg_color.a = 255; //alpha

    esta_corriendo = true;
    WIDTH=1024;
    HEIGHT=720;
    maxFPS=60;
    fps=0;

    
};

//Como solo queremos una instancia del esta clase, entonces se hace una clase singleton
SDLApp& SDLApp::get()
{
    if(!instancia)
        instancia = new SDLApp();
    return *instancia;
};

bool SDLApp::on_init()
{
    //revisar que SDL inicio bien
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){return false;};
    //crear la ventana
    get().vnt = SDL_CreateWindow(
        "Juego",                // Titulo de la ventana
        SDL_WINDOWPOS_UNDEFINED,// posicion X de la pantalla
        SDL_WINDOWPOS_UNDEFINED,// posicion Y de la pantalla
        get().WIDTH,            // ancho de la ventana
        get().HEIGHT,           // alto de la ventana
        SDL_WINDOW_OPENGL);     // que use OPENGL
    
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    //revisar que se creo bien la ventana
    if(get().vnt == NULL)
    {
        printf("No se creo la ventana por: %s",SDL_GetError());
        return false;
    }
    //la forma de procesar en GPU
    SDL_SetHint(SDL_HINT_RENDER_BATCHING,"opengl");
    //creamos el 'canvas'
    get().render = SDL_CreateRenderer(
        get().vnt,                  // la ventana
        -1,                         // driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  // flags driver
    //revisamos si se creo correctamente
    if(get().render == NULL)
    {
        printf("No se creo el renderer por: %s",SDL_GetError());
        return false; 
    }
    // si se creo correcto lo agregamos al Pipeline
    get().ensamble = new Pipeline(*get().render);

    //03
    
    //07
    player = new Jugador("assets/sprites/heroe/char1.png",
                //      hp , x , y, sW,sH , vW,vH ,color
                        100,500,50,64,64,100,100,{255,0,255,255});

    enemigo = new Enemigo("assets/sprites/enemigos/insecto.png",
                //      hp , x , y, sW,sH , vW,vH ,color
                        100, 600, 50, 32, 32, 100, 100, { 255,0,0,255 });
    //new Jugador(100,500,50,{255,0,255,255});
    get().ensamble->cargar_texturas(player->get_sprite());
    get().ensamble->cargar_texturas(enemigo->get_sprite());

    
    plataformas.push_back(new Plataformas(550,550,300,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(300,350,100,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(800,350,100,20,{0,0,0,255}));

    plataformas.push_back(new Plataformas(550,200,300,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(300,0,100,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(800,0,100,20,{0,0,0,255}));

    plataformas.push_back(new Plataformas(550,-350,300,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(300,-550,100,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(800,-550,100,20,{0,0,0,255}));

    //06_Camaras

    get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,*get().render);

    for(int i=0;i<plataformas.size();i++)
    {
        //agregar todos los objetos en una lista para la camara
        objetos.push_back(plataformas[i]);
    }

    //objetos.push_back(player);
    objetos_ang.push_back(player);
    enemigos_ang.push_back(enemigo);
    //objetos_ang.push_back()
    
    printf("Se crearon los test exitosamente\n");

    //agregamos el color del background del frame
    SDL_SetRenderDrawColor(
        get().render,       // canvas
        get().bg_color.r,   // rojo
        get().bg_color.g,   // verde
        get().bg_color.b,   // azul
        SDL_ALPHA_TRANSPARENT);// como usar el alpha

    return true;
};

void SDLApp::on_evento(SDL_Event* evento)
{
    if(evento->type==SDL_QUIT)
    {
        get().esta_corriendo = false;
    }
    //eventos del mouse
    MouseOyente::get().evento_movimiento(evento);
    MouseOyente::get().evento_presionado(evento);
    MouseOyente::get().evento_scroll(evento);
    // que esta presionado
    KeyOyente::get().keyPresionado(evento);
    
};

void SDLApp::on_fisicaupdate(double dt)
{
    
    //Camara Lock UnLock
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
    {
        camara_principal->lock_objeto(*player);
    }
    else if(KeyOyente::get().estaPresionado(SDL_SCANCODE_U) && !camara_principal->en_transicion)
    {
        camara_principal->unluck_objeto();
    }

    //render cuadro colisión player
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_C))
    {
        player->render_colbox = (player->render_colbox)?false:true;
        enemigo->render_colbox = (player->render_colbox)?false:true;
    }
    

    for(auto &p:plataformas)
    {  
        p->update(dt);
    }
    
    player->input_handle(KeyOyente::get(),MouseOyente::get());
    
    player->update(dt);
    enemigo->update(dt);


    //MotorFisico2D::get().gravedad({player});
    //MotorFisico2D::get().aabb_colision(*player,plataformas);
    MotorFisico2D::get().sat_colision(*player,plataformas);
    
    
    /*CAMARA al final para actualizar la proyeción de los objetos*/
    camara_principal->input_handle(KeyOyente::get(),MouseOyente::get());
    camara_principal->update();
    camara_principal->proyectar(objetos);
    //printf("Update Fisica\n");

    
    
};

void SDLApp::on_frameupdate(double dt)
{
    // limpiar frame
    SDL_RenderClear(get().render);

    //posicion del mouse
    int mx = MouseOyente::get().getX();
    int my = MouseOyente::get().getY();
    std::string pm = "mouse("+std::to_string(mx)+","+std::to_string(my)+")";
    Coordenadas cp = camara_principal->get_posicion_centro();
    Coordenadas mcp = camara_principal->get_posicion_mundo();
    std::string cm = "camara("+std::to_string(cp.x)+","+std::to_string(cp.y)+")";
    std::string cmm = "camara("+std::to_string(mcp.x)+","+std::to_string(mcp.y)+")";

    RenderTexto::get().render_texto(get().render,815,630,pm,100,30,SDL_Color{0,0,0,255});
    RenderTexto::get().render_texto(get().render,815,580,cmm,100,30,SDL_Color{0,0,0,255});
    RenderTexto::get().render_texto(get().render,815,530,cm,100,30,SDL_Color{0,0,0,255});
    //fps
    RenderTexto::get().render_texto(get().render,get().WIDTH-200,30,
        std::to_string((int)(dt/get().msfrecuencia))+" fps",
        100,30,SDL_Color{0,135,62});

    //Renderizar todo a través de la camara
    camara_principal->renderizar(objetos);
    camara_principal->renderizar_ang(objetos_ang, {MouseOyente::get().getX(), MouseOyente::get().getY()});
    camara_principal->renderizar_ang(enemigos_ang, {player->get_posx(), player->get_posy()});
    camara_principal->render_cross();
    
    RenderTexto::get().render_texto(get().render,50,630,player->get_strEstado(),120,30,SDL_Color{0,0,0,255});

    //Actualizar
    SDL_RenderPresent(get().render);

    //resetear color del frame
    SDL_SetRenderDrawColor(
        get().render,
        get().bg_color.r,
        get().bg_color.g,
        get().bg_color.b,
        SDL_ALPHA_TRANSPARENT);
};

void SDLApp::on_limpiar()
{
    SDL_DestroyRenderer(get().render);
    SDL_FreeSurface(get().vntsurf);
    SDL_DestroyWindow(get().vnt);

    for(auto &p:plataformas)
    {
        delete p;
    }
    plataformas.clear();
    delete ensamble;
    delete player;
    SDL_Quit();
};

int SDLApp::on_correr()
{
    //revisar que todo se inicializo bien
    if(get().on_init()==false){return -1;}

    SDL_Event eventos;
    double dt=0;
    double frecuencia = 1/get().maxFPS; // 1 frame a 60fps
    get().msfrecuencia = frecuencia*1000;

    while(get().estaCorriendo())
    {
        //double start = SDL_GetTicks();
        double inicio = Tiempo::get_tiempo();

        //printf("%lf <> %d\n",Tiempo::get_tiempo(),SDL_GetTicks());
        //captura eventos
        while(SDL_PollEvent(&eventos))
        {
            get().on_evento(&eventos);
        }

        //actualizamos si inicia o hay una diferencia de tiempo
        
        get().on_fisicaupdate(dt);
        get().on_frameupdate(dt);

        //calculamos el tiempo del frame
        dt = (Tiempo::get_tiempo() - inicio)/frecuencia*1000;
        
        inicio=dt; //el nuevo frame inicia en este tiempo
        //printf("<%d>[%lf][%d]\n",get().fps,dt,(int)Tiempo::get_tiempo());
        if(dt<get().msfrecuencia)
        {
            SDL_Delay(floor(get().msfrecuencia-dt));
        }
        //get().fps++;
    }
    //liberamos memoria
    get().on_limpiar();
    return 0;
};




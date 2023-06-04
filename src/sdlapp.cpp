#include "sdlapp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
#include <SDL_ttf.h>
#include "utilidad/RenderTexto.hpp"
#include "motor/fisica/MotorFisico.hpp"
#include <cmath>
#include <iostream>

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

    // get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,*get().render);
    // fondo
    //fondo = new Fondo((int)(get().WIDTH/2), (int)(get().HEIGHT/2),2400*2,480*2,"assets/sprites/mundo/atlas/fondoprueba2.jpg");
    //fondo->cargar_textura(get().render);
    //objetos.push_back(fondo);
    // objetos.push_back(new Fondo(0,0,get().WIDTH,get().HEIGHT,{255,0,0,255}));
    //08 tiles
    mapa = new Atlas("assets/sprites/mundo/ids/mars_ids.txt");
    mapa->generar_mapa(get().render,2,11);
    //05
    player = new Jugador("assets/sprites/heroe/soldado.png",
                //      hp , x , y, sW,sH , vW,vH ,color
                        100,1500,1500,32,32,86,86,{255,0,255,255});

    // enemigo = new Enemigo("assets/sprites/enemigos/insecto.png",
    //                     100,1500,1100,32,32,120,120,player,{255,0,0,255});
    // enemigo->set_ref_player(player);
    // enemigo2 = new Enemigo("assets/sprites/enemigos/insecto.png",
    //                     100,2500,2400,32,32,120,120,player,{255,0,0,255});
    // enemigo2->set_ref_player(player);

    // enemigo3 = new Enemigo("assets/sprites/enemigos/insecto.png",
    //                     100,1000,2400,32,32,120,120,player,{255,0,0,255});
    // enemigo3->set_ref_player(player);

    hud = new HUD(player, get().render);

    //new Jugador(100,500,50,{255,0,255,255});
    get().ensamble->cargar_texturas(player->get_sprite());
    // get().ensamble->cargar_texturas(enemigo->get_sprite());
    // get().ensamble->cargar_texturas(enemigo2->get_sprite());
    // get().ensamble->cargar_texturas(enemigo3->get_sprite());
    // get().ensamble->cargar_texturas(nave->get_sprite());
    //get().ensamble->cargar_texturas(new Sprite("assets/sprites/mundo/atlas/fondoprueba2.jpg",{0,0},get().WIDTH,get().HEIGHT,get().WIDTH,get().HEIGHT));
    printf("Se creo el player\n");
    
    
    plataformas = mapa->get_objetos_fisicos();
    //06_Camaras

    get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,*get().render);
    ManejadorCamaras::get().set_camara(*get().camara_principal);
    camara_principal->lock_objeto(*player);

    enespawner = new EnemigosSpawner("assets/sprites/enemigos/insecto.png",
                        100,1500,1100,32,32,120,120,player,{255,0,0,255}, *get().ensamble);
    enespawner->set_velocidad(5);

 
    
    for(int i=0;i<plataformas.size();i++)
    {
        //agregar todos los objetos en una lista para la camara
        objetos.push_back(plataformas[i]);
    }
    // plataformas.push_back(nave);
    objetos_ang.push_back(player);
    
    
    printf("\nSe crearon los objetos exitosamente\n");
    printf("vida player: %d\n", player->get_hp());

    timer = Tiempo::get_tiempo();

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
    
    //camara_principal->lock_objeto(*player);
    
    //Camara Lock UnLock
    
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
    {
        camara_principal->lock_objeto(*player);
    }
    else if(KeyOyente::get().estaPresionado(SDL_SCANCODE_U) && !camara_principal->en_transicion)
    {
        camara_principal->unluck_objeto();
    }
    

    if (KeyOyente::get().estaPresionado(SDL_SCANCODE_SPACE))
    {
        std::cout << player->get_posicion_mundo().y << std::endl;
    }

    //render cuadro colisión player
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_C))
    {
        player->render_colbox = (player->render_colbox)?false:true;
        enemigo->render_colbox = (enemigo->render_colbox)?false:true;
    }
    

    for(auto &p:plataformas)
    {  
        p->update(dt);
        //p->render_colbox = true;
    }
    
    player->input_handle(KeyOyente::get(),MouseOyente::get());
    player->update(dt);
    enespawner->update(&enemigos_ang);

    update_enemigos(dt);

    for(auto &b:player->getListaBalas()){
        get().ensamble->cargar_texturas(b->get_sprite());
        b->input_handle(KeyOyente::get(),MouseOyente::get(),*camara_principal);
        b->update(dt);
        objetos.push_back(b); //agregamos las balas a la lista de objetos para que puedan ser renderizados
    }
    
    colision_plataformas_player(plataformas, player);

    //IMPLEMENTAR: colision por segundo y lastimar player
    colision_enemigos_player(enemigos_ang, player); 

    //ya hay colision de enemigo con enemigo
    colision_enemigos_a_enemigos(enemigos_ang);

    //IMPLEMENTAR: lastimar enemigo
    colision_bala_a_enemigos(enemigos_ang, player);

    update_player_hp();

    // MotorFisico2D::get().gravedad({player});
    // MotorFisico2D::get().aabb_colision(*player,plataformas);
    // MotorFisico2D::get().sat_colision(*player,plataformas);
    
    /*CAMARA al final para actualizar la proyeción de los objetos*/
    // camara_principal->input_handle(KeyOyente::get(),MouseOyente::get());
    // camara_principal->update();
    // camara_principal->proyectar(objetos);

    ManejadorCamaras::get().input_handle(KeyOyente::get(),MouseOyente::get());
    ManejadorCamaras::get().update(objetos); //tambien hace proyectar objetos
    camara_principal->proyectar(objetos_ang); //si se comenta la camara nunca podra lockear a jugador
    camara_principal->proyectar(enemigos_ang); //si se comenta los enemigos nunca saldran de camara
    camara_principal->proyectar(enemigos_muertos);
    //printf("Update Fisica\n");
};

void SDLApp::on_frameupdate(double dt)
{
    // limpiar frame
    SDL_RenderClear(get().render);
    //Renderizar todo a través de la camara
    //camara_principal->renderizar(objetos);
    
    //ManejadorCamaras::get().renderizar(lista_balas);
    for(auto &e : enemigos_ang){
        if(e->estaMuerto){
            enemigos_muertos.push_back(e);
            for(auto i = enemigos_ang.begin(); i != enemigos_ang.end(); i++){
                if(*i == e){
                    enemigos_ang.erase(i);
                    break;
                }
            }
        }
    }
    
    ManejadorCamaras::get().renderizar(objetos);
    ManejadorCamaras::get().renderizar(enemigos_muertos);
    ManejadorCamaras::get().renderizar_ang(objetos_ang, {MouseOyente::get().getX(), MouseOyente::get().getY()});
    ManejadorCamaras::get().renderizar_ang(enemigos_ang, {player->get_posx(), player->get_posy()});
    camara_principal->render_cross();

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
    RenderTexto::get().render_texto(get().render,get().WIDTH-115,15,
        std::to_string((int)(dt/get().msfrecuencia))+" fps",
        64,30,SDL_Color{0,135,62});
    
    RenderTexto::get().render_texto(get().render,50,630,player->get_strEstado(),120,30,SDL_Color{0,0,0,255});

    hud->update_vida_jugador();

    //Eliminar objetos
    /*
    for(int i = 0; i < player->getListaBalas().size(); i++){
        if(player->getListaBalas()[i]->get_eliminarme() == true){
            delete player->getListaBalas()[i];
            player->getListaBalas().erase(player->getListaBalas().begin()+i);
            i--;
        }
    }
    */
   
    //Elimina las balas tanto de la lista de objetos como de la lista de balas del player
    eliminarBalas();
    eliminarEnemigos();

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
    delete enespawner;
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

void SDLApp::update_player_hp()
{
    timer += Tiempo::get_tiempo() - timer;
    if((int)timer%delay ==0 && (int)timer!=0 && (int)timer > past_time){
        if(player->en_colision_enemigo_jugador)
        {
            int hp = player->get_hp();
            hp -= 10;
            player->set_hp(hp);
            printf("VIDA PLAYER: %d\n");
            player->en_colision_enemigo_jugador = false;
        }
        past_time = timer;
        contador++;
    }
}

void SDLApp::colision_enemigos_player(std::vector<Objeto*> enemigos_ang, Jugador* player)
{
    for(auto &e:enemigos_ang){
        if(!e->render_colbox && e->get_colbox())
            e->render_colbox=true;

        if(e->get_colbox())
        {
            if(e->estaMuerto == false){
                MotorFisico2D::get().diag_overlap(*player,*e);
                bool colision = MotorFisico2D::get().aabb_colision(*e->get_colbox(),*player->get_colbox());
                player->en_colision |= colision;
                player->en_colision_enemigo_jugador |= colision;
            }
        }
    }
}

void SDLApp::colision_enemigos_a_enemigos(std::vector<Objeto*> enemigos_ang)
{
    for(int i = 0; i < enemigos_ang.size(); i++){
        int x = enemigos_ang[i]->get_posicion_mundo().x;
        int y = enemigos_ang[i]->get_posicion_mundo().y;
        for(int j = i + 1; j < enemigos_ang.size(); j++){
            int x2 = enemigos_ang[j]->get_posicion_mundo().x;
            int y2 = enemigos_ang[j]->get_posicion_mundo().y;
            if(enemigos_ang[i]->estaMuerto == false && enemigos_ang[j]->estaMuerto == false){
                MotorFisico2D::get().diag_overlap(*enemigos_ang[i], *enemigos_ang[j]);
            } 
        }
    }
}

void SDLApp::colision_bala_a_enemigos(std::vector<Objeto*> enemigos, Jugador* player)
{
    for(auto &b : player->getListaBalas()){
        if(!b->render_colbox && b->get_colbox())
            b->render_colbox=true;

        if(b->get_colbox())
        {
            for(auto &e : enemigos_ang){
                bool colision = MotorFisico2D::get().aabb_colision(*b->get_colbox(),*e->get_colbox());
                b->en_colision |= colision;
                e->en_colision_bala_enemigo |= colision;
            }
        }
    }
}

void SDLApp::colision_plataformas_player(std::vector<ObjetoEstatico*> plataformas, Jugador* player)
{
    for(auto &p:plataformas)
    {
        /*
        if(p->get_tiene_fisica())
        printf("tiene fisica\n");
        printf("colision\n");
        if(!p->render_colbox && p->get_colbox())
        p->render_colbox=true;
        */

        if(p->get_tiene_fisica())
        {
            MotorFisico2D::get().diag_overlap(*player,*p);
            bool pc = MotorFisico2D::get().aabb_colision(*player->get_colbox(),*p->get_colbox());
            player->en_colision |= pc;
        }
    }
}

void SDLApp::eliminarEnemigos()
{
    for(int i = 0; i < enemigos_ang.size(); i++){
        if(enemigos_ang[i]->estaMuerto == true){
            //printf("enemigo eliminado\n");
            delete enemigos_ang[i];
            enemigos_ang.erase(enemigos_ang.begin()+i);
            i--;
        }
    }

    for(int i = 0; i < enemigos_muertos.size(); i++){
        if(enemigos_muertos[i]->get_eliminarme() == true){
            //printf("enemigo eliminado\n");
            delete enemigos_muertos[i];
            enemigos_muertos.erase(enemigos_muertos.begin()+i);
            i--;
        }
    }

}

void SDLApp::eliminarBalas()
{
    player->eliminarBalas();
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i]->get_eliminarme() == true){
            //printf("bala eliminada\n");
            objetos.erase(objetos.begin()+i);
            i--;
        }
    }

}

void SDLApp::update_enemigos(double dt)
{
    for(auto &e:enemigos_ang)
    {
        e->update(dt);
        Enemigo* eDinamico = dynamic_cast<Enemigo*>(e);
        eDinamico->input_handle(KeyOyente::get(),MouseOyente::get());
    }

    for(auto &e:enemigos_muertos)
    {
        e->update(dt);
        Enemigo* eDinamico = dynamic_cast<Enemigo*>(e);
        eDinamico->input_handle(KeyOyente::get(),MouseOyente::get());
    }
}
#include"FSMEnemigo.hpp"

EstadoEnemigoIDLE::EstadoEnemigoIDLE()
{
    strnombre = "IDLE";
    frames_actual_ani = 0;
    frames_maxim_ani = 1;
}

FSMEnemigo* EstadoEnemigoIDLE::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    return nullptr;
}

void EstadoEnemigoIDLE::entrar(Enemigo& enemigo)
{
    frames_actual_ani = 0;
    frames_maxim_ani = 1;
}

void EstadoEnemigoIDLE::salir(Enemigo& enemigo)
{

}

void EstadoEnemigoIDLE::update(Enemigo& enemigo,double dt)
{
    enemigo.get_sprite()->play_frame(0, frames_actual_ani % frames_maxim_ani);

    if(frame_dt > 7){ //dura cada 7 frames
        frame_dt = 0;
        frames_actual_ani++;
        //Bala *bala = new Bala(25, 30, 30, SDL_Color{0,0,0});
    }
    frame_dt++;
}

/*MOVER*/
EstadoEnemigoMOVER::EstadoEnemigoMOVER(Coordenadas dir)
{
    strnombre = "MOVER";
    direccion = dir;
    velocidad = 2;
    frames_actual_ani = 0;
    frames_maxim_ani = 5;
}

FSMEnemigo* EstadoEnemigoMOVER::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    return nullptr;
}

void EstadoEnemigoMOVER::entrar(Enemigo& enemigo)
{
    frames_actual_ani = 0;
    frames_maxim_ani = 4;
}

void EstadoEnemigoMOVER::salir(Enemigo& enemigo)
{
    frames_actual_ani = 0;
    frames_maxim_ani = 4;
}

void EstadoEnemigoMOVER::update(Enemigo& enemigo,double dt)
{
    
    direccion = enemigo.get_ref_player()->get_posicion_mundo();
    
    Coordenadas e = enemigo.get_posicion_mundo();

    /*
    int dx = direccion.x - e.x;
    int dy = direccion.y - e.y;
    float angle = atan2(dy, dx);

    e.x += velocidad * cos(angle);
    e.y += velocidad * sin(angle);
    */
    if(enemigo.en_colision){
        printf("en colision con enemigo\n");
    }
    
    if(direccion.x - e.x > 40)
    {
        direccion.x = 1;
    }
    else if(direccion.x - e.x < 40)
    {
        direccion.x = -1;
    }
    else
    {
        direccion.x = 0;
    }

    if(direccion.y - e.y > 40)
    {
        direccion.y = 1;
    }
    else if(direccion.y - e.y < 40)
    {
        direccion.y = -1;
    }
    else
    {
        direccion.y = 0;
    }

    e.x += velocidad * direccion.x;
    e.y += velocidad * direccion.y;

    //printf("x: %d - y: %d\n", e.x, e.y);

    enemigo.set_posicion_camara(e);


    enemigo.get_sprite()->play_frame(0, frames_actual_ani % frames_maxim_ani);

    if(frame_dt > 7){ //dura cada 7 frames
        frame_dt = 0;
        frames_actual_ani++;
        //Bala *bala = new Bala(25, 30, 30, SDL_Color{0,0,0});
    }
    frame_dt++;
}

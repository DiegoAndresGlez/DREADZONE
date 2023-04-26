#include"FSMEnemigo.hpp"

EstadoEnemigoIDLE::EstadoEnemigoIDLE()
{
    strnombre = "IDLE";
    frames_actual_ani = 0;
    frames_maxim_ani = 5;
}

FSMEnemigo* EstadoEnemigoIDLE::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    /*
    if(input.is_key_down(SDL_SCANCODE_W) || input.is_key_down(SDL_SCANCODE_A) || input.is_key_down(SDL_SCANCODE_S) || input.is_key_down(SDL_SCANCODE_D))
    {
        return new EstadoEnemigoMOVER(Coordenadas(0,0));
    }
    */
    return nullptr;
}

void EstadoEnemigoIDLE::entrar(Enemigo& enemigo)
{
    frames_actual_ani = 0;
    frames_maxim_ani = 5;
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

/*
EstadoEnemigoMOVER::EstadoEnemigoMOVER(Coordenadas dir)
{
    strnombre = "MOVER";
    direccion = dir;
    velocidad = 2;
    frames_actual_ani = 0;
    frames_maxim_ani = 4;
}

FSMEnemigo* EstadoEnemigoMOVER::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    if(!input.is_key_down(SDL_SCANCODE_W) && !input.is_key_down(SDL_SCANCODE_A) && !input.is_key_down(SDL_SCANCODE_S) && !input.is_key_down(SDL_SCANCODE_D))
    {
        return new EstadoEnemigoIDLE();
    }
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
    frame_dt++;
    if(frame_dt>=10)
    {
        frame_dt=0;
        frames_actual_ani++;
        if(frames_actual_ani>=frames_maxim_ani)
            frames_actual_ani=0;
    }
    enemigo.avatar->set_recorte(75*frames_actual_ani,75,75,75);
    enemigo.avatar->set_posicion(enemigo.avatar->get_posicion()+direccion*velocidad);
}

FSMEnemigo* FSMEnemigo::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    return estado_actual->input_handle(input,mouse);
}

void FSMEnemigo::update(Enemigo& enemigo,double dt)
{
    estado_actual->update(enemigo,dt);
}

void FSMEnemigo::set_estado(FSMEnemigo* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = estado;
    estado_actual->entrar(*this);
}
*/


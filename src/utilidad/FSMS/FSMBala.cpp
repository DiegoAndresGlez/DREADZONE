#include"FSMBala.hpp"

EstadoBalaIDLE::EstadoBalaIDLE()
{
    strnombre="IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=1;
}

FSMBala* EstadoBalaIDLE::input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam)
{
    return nullptr;
}

void EstadoBalaIDLE::entrar(Bala& bala)
{
    frames_actual_ani=0;
    frames_maxim_ani=1;
}

void EstadoBalaIDLE::salir(Bala& bala)
{

}

void EstadoBalaIDLE::update(Bala& bala,double dt)
{
    bala.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}
/**/
EstadoBalaMOVER::EstadoBalaMOVER(Coordenadas dir)
{
    strnombre="MOVER";
    direccion=dir;
    velocidad=2;
    frames_actual_ani=0;
    frames_maxim_ani=1;
}

FSMBala* EstadoBalaMOVER::input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam)
{
    return nullptr;
}

void EstadoBalaMOVER::entrar(Bala& bala)
{
    frames_actual_ani=0;
    frames_maxim_ani=1;
}

void EstadoBalaMOVER::salir(Bala& bala)
{

}

void EstadoBalaMOVER::update(Bala& bala,double dt)
{
    bala.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}


//se puede agregar sprite de explosion de bala en colision
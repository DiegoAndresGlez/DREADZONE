#include "FSMNave.hpp"

EstadoNavePLAY::EstadoNavePLAY()
{
    frames_actual_ani = 0;
    frames_maxim_ani = 6;
}

FSMNave* EstadoNavePLAY::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    return nullptr;
}

void EstadoNavePLAY::entrar(Nave& nave)
{
    frames_actual_ani=0;
    frames_maxim_ani=6;
}

void EstadoNavePLAY::update(Nave& nave, double dt)
{
    nave.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>15)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}

void EstadoNavePLAY::salir(Nave& nave){}

#include"FSMBala.hpp"

EstadoBalaIDLE::EstadoBalaIDLE()
{
    strnombre="IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=1;
}

FSMBala* EstadoBalaIDLE::input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam)
{
    return new EstadoBalaMOVER({0,0});
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
    velocidad=5;
    frames_actual_ani=0;
    frames_maxim_ani=3;
}

FSMBala* EstadoBalaMOVER::input_handle(KeyOyente& input, MouseOyente& mouse, Camara& cam)
{
    return nullptr;
}

void EstadoBalaMOVER::entrar(Bala& bala)
{
    frames_actual_ani=0;
    frames_maxim_ani=3;
}

void EstadoBalaMOVER::salir(Bala& bala)
{

}

void EstadoBalaMOVER::update(Bala& bala,double dt)
{
    double angulo = atan2(bala.get_direccion_bala().x - bala.get_player_pos().x, bala.get_direccion_bala().y - bala.get_player_pos().y);
    int dir_x = velocidad * sin(angulo);
    int dir_y = velocidad * cos(angulo);
    Coordenadas b = bala.get_posicion_mundo();
    
    b.x+=(velocidad*dir_x);
    b.y+=(velocidad*dir_y);  

    if(bala.en_colision){
        bala.set_eliminarme(true);
        printf("BALA EN COLISION\n");
    }
    bala.set_posicion_camara(b);


    bala.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}


//se puede agregar sprite de explosion de bala en colision
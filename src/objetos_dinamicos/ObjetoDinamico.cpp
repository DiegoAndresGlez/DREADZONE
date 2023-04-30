#include "ObjetoDinamico.hpp"
#include "../objetos/Figuras.hpp"


Jugador::Jugador(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general
};

Jugador::Jugador(std::string path_sprite,float vida, int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general

    sprite = new Sprite(path_sprite, posicion_mundo, w, h, sw, sh);
};

std::string Jugador::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Jugador::get_estado()
{
    return estado_actual;
};

void Jugador::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMJugador*)estado;
    estado_actual->entrar(*this);
};

void Jugador::update(double dt)
{

    if(!estado_actual) //nulo
        return;

    if(en_colision)
        avatar->set_rellenocolor({255,0,0,255});
    else
        avatar->set_rellenocolor(color);

    estado_actual->update(*this,dt);
    
    //reset
    en_colision=false;


};

void Jugador::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMJugador* estado = estado_actual->input_handle(input,mouse);
    if(estado)
    {
        set_estado(estado);
    }
};

/*ENEMIGO*/
Enemigo::Enemigo(float vida, int x, int y, SDL_Color c){
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoIDLE();
    piso = {500,500}; // definir el piso en general
}

Enemigo::Enemigo(std::string path_sprite, float vida, int x, int y, int w, int h, int sw, int sh, SDL_Color c)
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoIDLE();
    piso = {500,500}; // definir el piso en general

    sprite = new Sprite(path_sprite, posicion_mundo, w, h, sw, sh);
}

std::string Enemigo::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Enemigo::get_estado()
{
    return estado_actual;
};

void Enemigo::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMEnemigo*)estado;
    estado_actual->entrar(*this);
};

void Enemigo::update(double dt)
{
    if(!estado_actual) //nulo
        return;

    if(en_colision)
        avatar->set_rellenocolor({255,0,0,255});
    else
        avatar->set_rellenocolor(color);

    estado_actual->update(*this,dt);
    
    //reset
    en_colision=false;
}

void Enemigo::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMEnemigo* estado = estado_actual->input_handle(input,mouse);
    if(estado)
    {
        set_estado(estado);
    }
}

/*BALA*/
Bala::Bala(int dano, int x, int y, SDL_Color c){
    hp = 0;
    dmg = dano;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    //estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general
}

Bala::Bala(std::string path_sprite, int dano, int x, int y, int w, int h, int sw, int sh, SDL_Color c)
{
    hp = 0;
    dmg = dano;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,40,65,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,40+10,65+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    
    estado_actual = new EstadoBalaIDLE();
    piso = {500,500}; // definir el piso en general

    sprite = new Sprite(path_sprite, posicion_mundo, w, h, sw, sh);
    printf("nueva bala creada\n");
}

void Bala::update(double dt){
    if(!estado_actual) //nulo
        return;
    //printf("pos: %d", get_avatar()->get_posicion().x);
    
    if(en_colision)
        avatar->set_rellenocolor({255,0,0,255});
    else
        avatar->set_rellenocolor(color);
    
    this->posicion_mundo.x += 10;

    estado_actual->update(*this,dt);
    
    //reset
    en_colision=false;
}

void* Bala::get_estado()
{
    return nullptr;
};

void Bala::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMBala*)estado;
    estado_actual->entrar(*this);
};

void Bala::input_handle(KeyOyente& input,MouseOyente& mouse,Camara& cam)
{
    printf("cam pos: %d, bala pos: %d\n", cam.get_posicion_centro().x, posicion_mundo.x);
    if(posicion_mundo.x > cam.get_posicion_centro().x + cam.get_posicion_centro().x)
    {
        eliminarme = true;
    }
    if(posicion_mundo.x < cam.get_posicion_centro().x - cam.get_posicion_centro().x)
    {
        eliminarme = true;
    }
    if(posicion_mundo.y > cam.get_posicion_centro().y + cam.get_posicion_centro().y)
    {
        eliminarme = true;
    }
    if(posicion_mundo.y < cam.get_posicion_centro().y - cam.get_posicion_centro().y)
    {
        eliminarme = true;
    }
    if(!estado_actual){
        
        return;
    } //nulo
        
    //obtener camara coordenadas, si se pasa de la camara, se destruye
    //
    
    if(cam.get_posicion_centro().x > posicion_mundo.x + 1000)
    {
        printf("Se elimina bala\n");
        delete this;
    }
    
    FSMBala* estado = estado_actual->input_handle(input,mouse,cam);
    if(estado){
        set_estado(estado);
    }
};



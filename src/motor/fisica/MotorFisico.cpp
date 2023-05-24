#include "MotorFisico.hpp"
#include "../../utilidad/Estructuras.hpp"
#include "../../utilidad/Func_aux.hpp"
#include<iostream>
#include<cmath>
#include<algorithm>



MotorFisico2D* MotorFisico2D::instancia = 0;

MotorFisico2D& MotorFisico2D::get()
{
    if(!instancia) 
        instancia = new MotorFisico2D();
    return *instancia;
};

void MotorFisico2D::aabb_colision(ObjetoDinamico& p, std::vector<ObjetoEstatico*>obj)
{
    for(auto &o: obj)
    {
        if(o->get_tiene_fisica())
            p.en_colision|=get().aabb(p,*o);
    }
    
};

bool MotorFisico2D::aabb(Objeto &A, Objeto &B)
{
    //    A.-----.D
    //     |     |
    //    B.-----.C

    std::vector<Coordenadas> vA = A.get_colbox()->get_vertices();
    std::vector<Coordenadas> vB = B.get_colbox()->get_vertices();

    return  (vA[0].x < vB[2].x && vA[2].x > vB[0].x) &&
            (vA[0].y < vB[2].y && vA[2].y > vB[0].y);
};

void MotorFisico2D::sat_colision(ObjetoDinamico& p, std::vector<ObjetoEstatico*>obj)
{
    for(auto& o:obj)
    {
        if(o->get_tiene_fisica())
            p.en_colision |= get().sat(p,*o);
    }
};

bool MotorFisico2D::sat(Objeto &A, Objeto& B)
{
    //para no iterar tanto copiar y flipearlos
    Objeto *objA = &A;
    Objeto *objB = &B;
    
    //dos comparaciones a la vez
    for(int fig=0;fig<2;fig++)
    {
        if(fig==1)
        {
            //flip para no iterar nuevamente
            objA = &B;
            objB = &A;
        }

        //proyectar el axis en figura 1
        std::vector<Coordenadas> vertA = objA->get_colbox()->get_vertices();
        for(int i=0;i<vertA.size();i++)
        {
            int j = (i+1)%vertA.size(); //el siguiente punto
            //como son ortogonales -y,x da la proyection, 
            float axis_x = -(vertA[j].y-vertA[i].y);
            float axis_y = vertA[j].x - vertA[i].x;
            //normalizar
            float magnitud = std::sqrt(axis_x*axis_x + axis_y*axis_y);
            axis_x /=magnitud;
            axis_y /=magnitud;

            //proyectamos todos los puntos en el axis y calculamos los limites
            float a_min = INFINITY, a_max = -INFINITY;
            for(int a=0; a<vertA.size();a++)
            {
                //producto punto nos da la escala del reflejo
                float q = vertA[a].x*axis_x+vertA[a].y*axis_y;
                a_min = std::min(a_min,q);
                a_max = std::max(a_max,q);
            }

            //lo mismo para la segunda figura
            float b_min = INFINITY, b_max = -INFINITY;
            std::vector<Coordenadas> vertB = objB->get_colbox()->get_vertices();
            for(int b=0; b<vertB.size();b++)
            {
                //producto punto nos da la escala del reflejo
                float m = vertB[b].x*axis_x+vertB[b].y*axis_y;
                b_min = std::min(b_min,m);
                b_max = std::max(b_max,m);
            }

            //AABB si no sobrelapan en algun axis regresar falso
            if(!(b_max>=a_min && a_max >=b_min))
            {
                return false;
            }

        }
    }
    // si llega aquí significa que un axis hay sobrelapo
    return true;

};


void MotorFisico2D::sortandsweep_colision(std::vector<ObjetoDinamico*> objs)
{
    
};

void MotorFisico2D::gravedad(std::vector<ObjetoDinamico*> objs)
{
    for(auto& o: objs)
    {
        if (o->get_posicion_mundo().y < 340)
        {
            int cy = o->get_posy();
            o->set_dtgf(o->get_dtgf()+get().gforce);
            int y = cy+o->get_dtgf();
            o->set_posy(y);
        } else {
            o->set_dtgf(0);
        }
    }
};

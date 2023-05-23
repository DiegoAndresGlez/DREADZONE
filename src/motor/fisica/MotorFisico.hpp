#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../objetos_estaticos/ObjetoEstatico.hpp"
#include "../../objetos/Objeto.hpp"
#include<vector>

class MotorFisico2D
{
    public:
        static MotorFisico2D& get();
        static void aabb_colision(ObjetoDinamico& p, std::vector<ObjetoEstatico*> obj); 
        static void sat_colision(ObjetoDinamico&p, std::vector<ObjetoEstatico*> obj);
        static void sortandsweep_colision(std::vector<ObjetoDinamico*> objs);

        static void gravedad(std::vector<ObjetoDinamico*> objs);
    
    private:
        bool sat(Objeto &A, Objeto& B);
        bool aabb(Objeto &A, Objeto &B);

    private:
        MotorFisico2D(){};
        static MotorFisico2D* instancia;
        float gforce{0.09};
        float dtgravedad{0};


        
};

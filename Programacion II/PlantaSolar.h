#pragma once
#include "EntidadBase.h"
#include "IProductor.h"
using namespace std;

// PRINCIPIO DE SUSTITUCIÓN DE LISKOV (LSP):
// PlantaSolar PUEDE sustituir a IEntidad en cualquier parte del código
// sin que el programa falle. Es un subtipo real.

class PlantaSolar : public EntidadBase, public IProductor {
private:
    double capacidadMaxima;
    double eficiencia;
public:
    PlantaSolar(string n, double cap);
    double producirEnergia() override;
    string getDetalleEstado() const override;
};


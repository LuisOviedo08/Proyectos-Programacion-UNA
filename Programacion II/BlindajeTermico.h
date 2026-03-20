#pragma once

#include "EntidadDecoradora.h"

using namespace std;

class BlindajeTermico : public EntidadDecoradora
{

public:

    BlindajeTermico(string nombre, shared_ptr<IConsumidor> entidadDecorada);

    double consumirEnergia() override;

    string getDetalleEstado() const override;

};
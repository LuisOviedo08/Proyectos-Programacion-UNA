#pragma once

#include "EntidadDecoradora.h"

using namespace std;

class SensorConsumoInteligente : public EntidadDecoradora
{

public:

    SensorConsumoInteligente(string nombre, shared_ptr<IConsumidor> entidadDecorada);

    double consumirEnergia() override;

    string getDetalleEstado() const override;

};
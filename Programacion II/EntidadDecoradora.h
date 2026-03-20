#pragma once

#include <memory>
#include "EntidadBase.h"
#include "IConsumidor.h"

using namespace std;

class EntidadDecoradora : public EntidadBase, public IConsumidor
{
protected:

    shared_ptr<IConsumidor> entidad;

public:

    EntidadDecoradora(string nombre, shared_ptr<IConsumidor> entidadDecorada);

    double consumirEnergia() override;

    string getDetalleEstado() const override;
};
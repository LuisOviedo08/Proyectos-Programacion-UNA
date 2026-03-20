#pragma once
#include "EntidadBase.h"
#include "IProductor.h"
#include "IConsumidor.h"

class ComplejoIndustrial : public EntidadBase, public IProductor, public IConsumidor {
private:
    double produccionPropia;
    double consumoMaquinaria;

public:
    ComplejoIndustrial(std::string n, double prod, double cons);
    double producirEnergia() override;
    double consumirEnergia() override;
    std::string getDetalleEstado() const override;
};

#pragma once

#include <memory>
#include <string>
#include "IProductor.h"

using namespace std;

class ReduccionEmisiones : public IProductor
{
private:

    shared_ptr<IProductor> productor;
    bool banderaVerde;

public:

    ReduccionEmisiones(shared_ptr<IProductor> prod);

    double producirEnergia() override;

    string getCertificacion() const;
};
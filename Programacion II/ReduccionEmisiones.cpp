#include "ReduccionEmisiones.h"

using namespace std;

ReduccionEmisiones::ReduccionEmisiones(shared_ptr<IProductor> prod)
{
    productor = prod;
    banderaVerde = false;
}

double ReduccionEmisiones::producirEnergia()
{
    double energia = productor->producirEnergia();

    // Simulación de reducción de emisiones
    double impactoReducido = energia * 0.8;

    if (impactoReducido < 100)
    {
        banderaVerde = true;
    }

    return energia;
}

string ReduccionEmisiones::getCertificacion() const
{
    if (banderaVerde)
        return "Certificado Verde";
    else
        return "Produccion con emisiones moderadas";
}
#include "BlindajeTermico.h"

using namespace std;

BlindajeTermico::BlindajeTermico(string nombre, shared_ptr<IConsumidor> entidadDecorada)
    : EntidadDecoradora(nombre, entidadDecorada)
{
}

double BlindajeTermico::consumirEnergia()
{
    double consumo = entidad->consumirEnergia();

    return consumo * 0.90;
}

string BlindajeTermico::getDetalleEstado() const
{
    return "Blindaje térmico activo";
}
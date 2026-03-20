#include "EntidadDecoradora.h"

using namespace std;

EntidadDecoradora::EntidadDecoradora(string nombre, shared_ptr<IConsumidor> entidadDecorada)
    : EntidadBase(nombre)
{
    entidad = entidadDecorada;
}

double EntidadDecoradora::consumirEnergia()
{
    return entidad->consumirEnergia();
}

string EntidadDecoradora::getDetalleEstado() const
{
    return "Decorador aplicado";
}
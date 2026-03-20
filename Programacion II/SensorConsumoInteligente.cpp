#include "SensorConsumoInteligente.h"

using namespace std;

SensorConsumoInteligente::SensorConsumoInteligente(string nombre, shared_ptr<IConsumidor> entidadDecorada)
    : EntidadDecoradora(nombre, entidadDecorada)
{
}

double SensorConsumoInteligente::consumirEnergia()
{
    double consumoOriginal = entidad->consumirEnergia();

    return consumoOriginal * 0.85;
}

string SensorConsumoInteligente::getDetalleEstado() const
{
    return "Sensor Inteligente activo (15% ahorro)";
}
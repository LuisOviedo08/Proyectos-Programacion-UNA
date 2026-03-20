#include "PlantaSolar.h"

PlantaSolar::PlantaSolar(string n, double cap)
    : EntidadBase(n), capacidadMaxima(cap), eficiencia(0.85) {
}

double PlantaSolar::producirEnergia() {
    return activo ? (capacidadMaxima * eficiencia) : 0.0;
}

std::string PlantaSolar::getDetalleEstado() const {
    return "Tipo: [Productor] | Eficiencia: " + to_string((int)(eficiencia * 100)) + "%";
}

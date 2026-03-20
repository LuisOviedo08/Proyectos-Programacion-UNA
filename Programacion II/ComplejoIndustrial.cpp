#include "ComplejoIndustrial.h"

ComplejoIndustrial::ComplejoIndustrial(std::string n, double prod, double cons)
    : EntidadBase(n), produccionPropia(prod), consumoMaquinaria(cons) {
}

double ComplejoIndustrial::producirEnergia() {
    return activo ? produccionPropia : 0.0;
}

double ComplejoIndustrial::consumirEnergia() {
    return activo ? consumoMaquinaria : 0.0;
}

std::string ComplejoIndustrial::getDetalleEstado() const {
    bool autosuficiente = produccionPropia >= consumoMaquinaria;
    return "Tipo: [Híbrido]   | Autosuficiente: " + std::string(autosuficiente ? "SI" : "NO");
}

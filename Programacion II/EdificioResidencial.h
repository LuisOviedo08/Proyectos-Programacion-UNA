#pragma once
#include "EntidadBase.h"
#include "IConsumidor.h"

using namespace std;
// PRINCIPIO DE SUSTITUCIÓN DE LISKOV (LSP):
// PlantaSolar PUEDE sustituir a IEntidad en cualquier parte del código
// sin que el programa falle. Es un subtipo real.

class EdificioResidencial : public EntidadBase, public IConsumidor {
private:
    double consumoBase;
    int habitantes;

public:
    EdificioResidencial(string n, double base, int hab);
    double consumirEnergia() override;
  string getDetalleEstado() const override;
  void serializarTexto(ostream& os) const override; //corrige el tipo de flujo a ostream
  void serializarBinario(ofstream& os) const override; //corrige el tipo de flujo a ofstream
};

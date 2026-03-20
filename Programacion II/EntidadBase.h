#pragma once
#include "IEntidad.h"
using namespace std;

// PRINCIPIO DE PARNAS (Ocultamiento):
// Los atributos 'nombre' y 'activo' son protected. 
// El mundo exterior no sabe CÓMO se guardan, solo accede vía métodos públicos.

class EntidadBase : public IEntidad {
protected:
    string nombre;
    bool activo;

public:
    EntidadBase(string n);
    string getNombre() const override;
    virtual void alternarEstado();
    bool isActivo() const;
};


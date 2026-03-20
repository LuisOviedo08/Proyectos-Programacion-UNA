#pragma once
#include <string>
#include<fstream> //Absolutamente necesario para OSTREAM Y OFTREAM
using namespace std;

// PRINCIPIO DE SEGREGACIÓN DE INTERFAZ (ISP):
// Creamos contratos pequeños (IEntidad, IProductor) en lugar de uno gigante.
// SOLID (I): Las clases no deben ser forzadas a implementar métodos que no usan.

class IEntidad {
public:
    virtual ~IEntidad() = default;
    virtual string getNombre() const = 0;
    virtual string getDetalleEstado() const = 0;

    //ÉRSISTENCIA: 
    //1- Flujos de texto (Reportes)
	virtual void serializarTexto(ostream& os) const = 0;



    //2- Flujos binarios (guardar datos planos)
	virtual void serializarBinario(ofstream& os) const = 0; //of de output con formato binario



};
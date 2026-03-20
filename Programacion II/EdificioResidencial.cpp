#include "EdificioResidencial.h"

using namespace std;

EdificioResidencial::EdificioResidencial(string n, double base, int hab)
    : EntidadBase(n), consumoBase(base), habitantes(hab) {
}

double EdificioResidencial::consumirEnergia() {
    if (!activo) return 0.0;
    return consumoBase + (habitantes * 0.5);
}

string EdificioResidencial::getDetalleEstado() const {
    return "Tipo: [Consumidor] | Habitantes: " + to_string(habitantes);
}

void EdificioResidencial::serializarTexto(ostream& os) const {
    os << "RESIDENCIAL, " << nombre << ", Consumo Base: " << consumoBase << ", Numero de Habitantes:" << habitantes << endl;
}

void EdificioResidencial::serializarBinario(ofstream& os) const {
    //1. Escribimos un identificador para saber que es lo que estamos construyendo
	int tipo = 1; // 1 para EdificioResidencial
	os.write(reinterpret_cast<const char*>(tipo), sizeof(tipo));
 
	//2. Escribimos los datos de texto (Nombre del edificio)
	//(Longitud del nombre + cantidad de caracteres)
	size_t tamNombre = nombre.size();
	os.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
    os.write(nombre.c_str(), tamNombre);
 
	//3. Escribir los datos numericos que no son texto (consumoBase y habitantes)
	os.write(reinterpret_cast<const char*>(&consumoBase), sizeof(consumoBase));
	os.write(reinterpret_cast<const char*>(&habitantes), sizeof(habitantes));

}
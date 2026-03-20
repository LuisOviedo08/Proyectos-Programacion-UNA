#include "Distrito.h"
#include "IProductor.h"
#include "IConsumidor.h"
#include "CentralEmergencias.h" // Aquí SÍ incluimos el .h porque necesitamos usar sus métodos
#include "ExcepcionesCiudad.h"
#include <iostream>
using namespace std;

Distrito::Distrito(string n) : nombre(n), centralAsignada(nullptr) {}

void Distrito::setCentral(shared_ptr<CentralEmergencias> c) {
    this->centralAsignada = c;
}

// Si el nombre esta vacio o el puntero es nulo, lanzamos ErrorConfiguracionInvalida.
// RAII: Al usar shared_ptr, si la excepcion ocurre aqui, no hay fuga de memoria;

void Distrito::agregarEdificio(shared_ptr<IEntidad> edificio) {
    if (!edificio) {
        throw ErrorConfiguracionInvalida(
            "No se puede agregar un edificio nulo al distrito '" + nombre + "'.",
            "puntero");
    }
    if (edificio->getNombre().empty()) {
        throw ErrorConfiguracionInvalida(
            "El nombre del edificio no puede estar vacio en el distrito '" + nombre + "'.",
            "nombre");
    }
    edificios.push_back(edificio);
}

void Distrito::alertarEmergencia(string causa) const {

    if (centralAsignada) {
        // DEPENDENCIA MUTUA EN ACCIÓN: El distrito llama a un método de Central
        centralAsignada->recibirAlerta("Emergencia en " + nombre + ": " + causa);
    }
}

double Distrito::obtenerProduccionTotal() const {
    double total = 0;
    for (auto& e : edificios) {
        auto p = dynamic_cast<IProductor*>(e.get());
        if (p) total += p->producirEnergia();
    }
    return total;
}

double Distrito::obtenerConsumoTotal() const {
    double total = 0;
    for (auto& e : edificios) {
        auto c = dynamic_cast<IConsumidor*>(e.get());
        if (c) total += c->consumirEnergia();
    }
    return total;
}

string Distrito::getNombre() const { return nombre; }

void Distrito::mostrarReporteDistrito() const {
    cout << "  Distrito: " << nombre << " (" << edificios.size() << " edificios)\n";
    for (auto& e : edificios) {
        cout << "    - " << e->getNombre() << " [" << e->getDetalleEstado() << "]\n";
    }
}


// Este metodo es el ORIGEN de ErrorRecursosInsuficientes.
// No la captura aqui; deja que suba hasta GestorCiudad::procesarTurno().

void Distrito::verificarBalance() const {
    double prod = obtenerProduccionTotal();
    double cons = obtenerConsumoTotal();

    if (prod == 0 && cons == 0) return; // Sin datos, no se puede evaludar

    // Condicion critica: consumo supera la produccion por mas del 50%

    if (cons > prod * 1.5) {
        // Alertamos a la central antes de propagar la excepcion
        alertarEmergencia("Deficit energetico critico (>" +
            to_string((int)((cons / prod - 1) * 100)) + "%)");
        // LANZAMOS la excepcion: sube por la pila hasta el Motor
        throw ErrorRecursosInsuficientes(nombre, prod, cons);
    }
}

void Distrito::guardarReporteTexto(string nombreArchivo) const {
    ofstream archivo(nombreArchivo); //Esto por defecto esta modo texto
	//2. Verificamos que el archivo se creo correctamente
	if (!archivo) throw runtime_error("No se pudo crear el reporte");

    //3. Si el archivo se creo, comenzamos la escritura de datos
	archivo << "---- REPORTE DE DISTRITO:  ----\n";
	archivo << "Nombre: " << nombre << "\n";
    for(auto& e: edificios){
		e->serializarTexto(archivo); //Cada edificio se serializa a texto
	}
	//4. El archivo se cierra automáticamente al salir del bloque (RAII)
	archivo.close();
}

void Distrito::guardarReporteBinario(string nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::binary); //Abrimos en modo binario
    //2. Verificamos que el archivo se creo correctamente
    if (!archivo) throw runtime_error("Error al crear el reporte Binario");
    //3. Si el archivo se creo, comenzamos la escritura de datos
	size_t cantidad = edificios.size();
    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad)); //Escribimos la cantidad de edificios
	for (auto& e : edificios) {
		e->serializarBinario(archivo); //Cada edificio se serializa a binario
	}

    //4. El archivo se cierra automáticamente al salir del bloque (RAII)
    archivo.close();
}

void Distrito::cargarDesdeTexto(string nombreArchivo)]{
	//1. Abrir el archivo y definir un espacio para almacenar cada linea
    ifstream archivo(nombreArchivo);
	string linea;

	//2. Verificamos que el archivo realmente exista
	if (archivo.is_open()) throw runtime_error("No se pudo abrir el archivo de reporte");)
    
	//Limpiamos los edificios actuales antes de cargar nuevos datos
	this->edificios.clear();
    while (getline(archivo, linea)) {
		//ignoramos lineas vacias o de encabezado
        if (linea.find("RESIDENCIAL") == string::npos && linea.find("INDUSTRIAL") == string::npos) continue;
		stringstream ss(linea);
        string tipo, nombreEdifico, habString, consumoString;

    //Separamos por comas: TIPO, NOMBRE, CONSUMO , HABITANTES
        getline(ss, tipo, ", ");
        getline(ss, nombreEdifico, ", ");
        getline(ss, consumoString, ", ";
        getline(ss, habString, ", ");
        
		//Por El momento solo tenemos EdificioResidencial, entonces solo leemos edificios residenciales
        if (tipo == "1") {
			auto respusesta = make_shared<EdificioResidencial>(nombreEdifico, stod(consumoString), stoi(habString));
			this->agregarEdificio(respusesta);
        }
        
    }
}
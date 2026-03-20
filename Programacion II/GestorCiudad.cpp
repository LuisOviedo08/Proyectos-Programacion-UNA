#include "GestorCiudad.h"
#include "ExcepcionesCiudad.h"
#include <iostream>
#include <cstdlib>  // Lo usamos para rand() y srand() que simulan eventos aleatorios (desastres externos)
#include <ctime>    // Lo usamos para obtener una semilla basada en el tiempo actual para srand()
using namespace std;

GestorCiudad::GestorCiudad(shared_ptr<CentralEmergencias> central)
    : centralUrbana(central), turnoActual(0) {
    srand(static_cast<unsigned>(time(nullptr)));
}

void GestorCiudad::agregarDistrito(shared_ptr<Distrito> d) {
    distritos.push_back(d);
    // PRINCIPIO DE INVERSION DE CONTROL: El motor vincula al distrito con la central
    d->setCentral(centralUrbana);
}


// procesarTurno() actua como el coordinador de la simulacion.
// Captura las excepciones que suben desde los distritos y reacciona a ellas
void GestorCiudad::procesarTurno() {
    turnoActual++;
    double ciudadProd = 0;
    double ciudadCons = 0;

    cout << "\n========== TURNO SIMULADO: " << turnoActual << " ==========\n";


    // Simula un fallo tecnico impredecible en el motor.
    int dado = rand() % 100;
    if (dado < 20) { //Aqui podemos ajustar la probabilidad de desastre externo
        throw DesastreExterno(dado);
    }

    for (auto& dist : distritos) {
        dist->mostrarReporteDistrito();
        ciudadProd += dist->obtenerProduccionTotal();
        ciudadCons += dist->obtenerConsumoTotal();

        //Se verifica el balance y llama a gestionar la crisis en caso de existir
        try {
            dist->verificarBalance();
        }
        catch (const ErrorRecursosInsuficientes& e) {

            cout << "\n  >> " << e.tipoError() << " capturado en el Motor.\n";
            cout << "  >> Deficit en '" << e.getDistrito()
                << "': " << e.getDeficit() << " kW faltantes.\n";
            cout << "  >> Accion: Gestionando crisis energetica...\n";
            dist->gestionarCrisis();

            throw;
        }
    }

    cout << "--------------------------------------------\n";
    cout << "REPORTE CIUDAD GLOBAL:\n";
    cout << "  Energia Generada:  " << ciudadProd << " kW\n";
    cout << "  Energia Demandada: " << ciudadCons << " kW\n";
    cout << "  Balance:           " << (ciudadProd - ciudadCons) << " kW\n";
    cout << "============================================\n";
}

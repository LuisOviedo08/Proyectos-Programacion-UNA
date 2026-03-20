// CiudadInteligente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "GestorCiudad.h"
#include "PlantaSolar.h"
#include "EdificioResidencial.h"
#include "ComplejoIndustrial.h"
#include "CiudadException.h"
#include "EstrategiaAhorro.h"
#include "DeficitRecursoException.h"
#include "SensorConsumoInteligente.h"
#include "BlindajeTermico.h"
#include "ReduccionEmisiones.h"
#include "ExcepcionesCiudad.h"

int main() {

    cout << "=== SISTEMA DE CIUDAD INTELIGENTE - TEST DE EXCEPCIONES ===\n";

    // -----------------------------------------------------------------------
    // PRUEBA 1: Validacion de configuracion incorrecta
    // -----------------------------------------------------------------------
    cout << "\n********************************************\n";
    cout << "  PRUEBA 1: ErrorConfiguracionInvalida\n";
    cout << "********************************************\n\n";

    auto centralPrueba = make_shared<CentralEmergencias>("Central-Prueba");
    GestorCiudad motorPrueba(centralPrueba);
    auto distPrueba = make_shared<Distrito>("Zona de Prueba");
    motorPrueba.agregarDistrito(distPrueba);

    try {
        cout << "[P1] Probando crear un edificio con nombre vacio...\n";
        auto edificioInvalido = make_shared<EdificioResidencial>("", 100, 50);
        distPrueba->agregarEdificio(edificioInvalido);
        cout << "   (esta linea no deberia ejecutarse)\n";
    }
    catch (const ExcepcionUrbana& ex) {
        cout << "\n  [!] Tipo de error: " << ex.tipoError() << "\n";
        cout << "  Descripcion: " << ex.what() << "\n";
        cout << "  >> El edificio no fue agregado y la memoria fue liberada.\n";
    }

    try {
        cout << "\n[P2] Intentando registrar un edificio nulo (nullptr)...\n";
        distPrueba->agregarEdificio(nullptr);
    }
    catch (const ExcepcionUrbana& ex) {
        cout << "\n  [!] Tipo de error: " << ex.tipoError() << "\n";
        cout << "  Descripcion: " << ex.what() << "\n";
        cout << "  >> Se rechazo el puntero nulo. No hay perdida de memoria.\n";
    }

    cout << "\n--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl << endl;


    // -----------------------------------------------------------------------
    // PRUEBA 2: Falta de recursos energeticos
    // -----------------------------------------------------------------------

    cout << "\n********************************************\n";
    cout << "  PRUEBA 2: ErrorRecursosInsuficientes\n";
    cout << "********************************************\n\n";

    auto central2 = make_shared<CentralEmergencias>("Central-Alpha");
    GestorCiudad motor2(central2);
    auto dist2 = make_shared<Distrito>("Zona Critica");

    // Se crea un desbalance energetico para provocar la excepcion
    dist2->agregarEdificio(make_shared<PlantaSolar>("Solar-Mini", 100));
    dist2->agregarEdificio(make_shared<EdificioResidencial>("Mega Complejo", 700, 200));
    motor2.agregarDistrito(dist2);

    cout << "Configuracion actual: Produccion=100 kW, Consumo=800 kW (deficit mayor al 50%)\n";

    try {
        motor2.procesarTurno();
    }
    catch (const ExcepcionUrbana& ex) {
        cout << "\n[MAIN] Excepcion interceptada en main\n";
        cout << "  Tipo   : " << ex.tipoError() << "\n";
        cout << "  Detalle: " << ex.what() << "\n";
        if (auto* err = dynamic_cast<const ErrorRecursosInsuficientes*>(&ex)) {
            cout << "  Deficit calculado: " << err->getDeficit() << " kW.\n";
        }
        cout << "  >> El sistema registra el problema y sigue funcionando.\n";
    }


    cout << "\n--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl << endl;

    // -----------------------------------------------------------------------
    // PRUEBA 3: Evento de desastre externo (forzado para prueba)
    // -----------------------------------------------------------------------
    cout << "\n********************************************\n";
    cout << "  PRUEBA 3: DesastreExterno\n";
    cout << "********************************************\n";

    cout << "\n [NOTA] ESTA EXCEPCION SE LANZA MANUALMENTE SOLO PARA VALIDAR EL MANEJO" << endl << endl;

    try {
        throw DesastreExterno(42);
    }
    catch (const ExcepcionUrbana& ex) {
        cout << "[!] Tipo de error: " << ex.tipoError() << "\n";
        cout << "  Detalle: " << ex.what() << "\n";
        if (auto* des = dynamic_cast<const DesastreExterno*>(&ex)) {
            cout << "  Codigo asociado: " << des->getCodigo() << "\n";
        }
        cout << "  >> Se activa el protocolo de emergencia del sistema.\n";
    }


    cout << "\n--------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------" << endl << endl;

    // -----------------------------------------------------------------------
    // PRUEBA 4: Ejecucion normal sin errores
    // -----------------------------------------------------------------------
    cout << "\n********************************************\n";
    cout << "  PRUEBA 4: Turno Normal (Sin Excepciones)\n";
    cout << "********************************************\n";

    auto central4 = make_shared<CentralEmergencias>("Central-Beta");
    GestorCiudad motor4(central4);
    auto dist4 = make_shared<Distrito>("Zona Verde");

    // Produccion suficiente y consumo moderado -> sistema estable
    dist4->agregarEdificio(make_shared<PlantaSolar>("Solar-Max", 500));
    dist4->agregarEdificio(make_shared<EdificioResidencial>("Residencial Norte", 100, 50));
    motor4.agregarDistrito(dist4);

    cout << "Configuracion: Produccion=500 kW, Consumo aproximado=125 kW (balance favorable)\n";

    try {
        motor4.procesarTurno();
        cout << "[OK] El turno finalizo correctamente sin lanzar excepciones.\n";
    }
    catch (const ExcepcionUrbana& ex) {
        cout << "[NOTA] Se produjo un " << ex.tipoError() << " aleatorio: " << ex.what() << "\n";
    }

    cout << "\n=== Fin de las pruebas ===\n";
    return 0;
}

//Prueba GitHub:
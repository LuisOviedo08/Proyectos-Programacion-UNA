#pragma once
#include <stdexcept>
#include <string>

using namespace std;

//Se colocan todas las excepciones personalizadas en este .h para no crear muchos archivos separados.
class ExcepcionUrbana : public runtime_error {
public:
    explicit ExcepcionUrbana(const string& mensaje)
        : runtime_error(mensaje) {
    }

    // Metodo virtual que permite mostrar mensajes polimorficos
    virtual string tipoError() const {
        return "[EXCEPCION URBANA]";
    }
};

// --- ERROR: RECURSOS INSUFICIENTES POR UN 50% ---

class ErrorRecursosInsuficientes : public ExcepcionUrbana {
private:
    string nombreDistrito;
    double produccion;
    double consumo;

public:
    ErrorRecursosInsuficientes(const string& distrito,
        double prod, double cons)
        : ExcepcionUrbana(
            "Deficit critico en '" + distrito + "': Produccion=" +
            to_string(prod) + " kW, Consumo=" +
            to_string(cons) + " kW (margen > 50%)"),
        nombreDistrito(distrito), produccion(prod), consumo(cons) {
    }

    string tipoError() const override {
        return "[ERROR RECURSOS INSUFICIENTES]";
    }
    double getDeficit() const { return consumo - produccion; }
    string getDistrito() const { return nombreDistrito; }
};

// --- ERROR: CONFIGURACION INVALIDA ---
//No se permiten nombres vacios, valores negativos o nulos

class ErrorConfiguracionInvalida : public ExcepcionUrbana {
private:
    string campo;

public:
    ErrorConfiguracionInvalida(const string& detalle,
        const string& campoInvalido = "")
        : ExcepcionUrbana("Configuracion invalida: " + detalle),
        campo(campoInvalido) {
    }

    string tipoError() const override {
        return "[ERROR CONFIGURACION INVALIDA]";
    }
    string getCampo() const { return campo; }
};

// DESASTRE EXTERNO:
// Fallo tecnico aleatorio e impredecible, se inicia con un 20% de probabilidad pero se puede modificar

class DesastreExterno : public ExcepcionUrbana {
private:
    int codigoFallo;

public:
    explicit DesastreExterno(int codigo)
        : ExcepcionUrbana(
            "Fallo tecnico impredecible en el motor (Codigo: " +
            to_string(codigo) + "). Sistema comprometido."),
        codigoFallo(codigo) {
    }

    string tipoError() const override {
        return "[DESASTRE EXTERNO]";
    }
    int getCodigo() const { return codigoFallo; }
};

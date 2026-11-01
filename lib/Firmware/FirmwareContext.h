#ifndef FIRMWARE_CONTEXT_H
#define FIRMWARE_CONTEXT_H

#include <Arduino.h>

#include <PhSensor.h>
#include <CondutSensor.h>
#include <TemperatureSensor.h>
#include <LevelWaterSensor.h>

#include <WifiManager.h>
#include <MqttManager.h>

// ======================
// Objetos
// ======================

extern PhSensor sensorPH;
extern CondutSensor sensorCondutividade;
extern SensorTemperatura sensorTemperatura;
extern SensorNivelAgua sensorNivelAgua;

extern WifiManager wifiManager;
extern MqttManager mqttManager;

// ======================
// Configurações
// ======================

extern const unsigned long TEMPO_TURNO;
extern const unsigned long INTERVALO_LEITURA;
extern const uint8_t CICLOS_AQUECIMENTO;

// ======================
// Controle
// ======================

extern bool turnoPH;

extern bool aquecimentoConcluido;
extern uint8_t ciclosConcluidos;

extern unsigned long inicioTurno;
extern unsigned long ultimaLeitura;

extern float ultimoPH;
extern float ultimaCondutividade;

extern float ultimaTemperatura;
extern bool ultimoNivelAgua;
extern bool dadosProntos;

#endif
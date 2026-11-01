#include <Arduino.h>

#include "Pins.h"
#include "Config.h"

#include <PhSensor.h>
#include <CondutSensor.h>
#include <TemperatureSensor.h>
#include <LevelWaterSensor.h>

#include <WifiManager.h>
#include <MqttManager.h>

#include <Firmware.h>

// Sensores
PhSensor sensorPH(PH);
CondutSensor sensorCondutividade(CONDUCTIVITY);
SensorTemperatura sensorTemperatura(TEMPERATURE);
SensorNivelAgua sensorNivelAgua(WATER);

// Wi-Fi
WifiManager wifiManager;

// MQTT
MqttManager mqttManager(wifiManager.getClient());

// Configurações
extern const unsigned long TEMPO_TURNO = 5000;
extern const unsigned long INTERVALO_LEITURA = 100;
extern const uint8_t CICLOS_AQUECIMENTO = 2;

// Controle
bool turnoPH = true;

bool aquecimentoConcluido = false;
uint8_t ciclosConcluidos = 0;

unsigned long inicioTurno = 0;
unsigned long ultimaLeitura = 0;

float ultimoPH = NAN;
float ultimaCondutividade = NAN;
float ultimaTemperatura = NAN;
bool ultimoNivelAgua = false;

bool dadosProntos = false;

void setup()
{
    Serial.begin(115200);

    // Wi-Fi
    wifiManager.begin();
    wifiManager.connect(WIFI_SSID, WIFI_PASSWORD);

    // MQTT
    mqttManager.begin();
    mqttManager.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);

    // Sensores
    sensorPH.begin();
    sensorCondutividade.begin();
    sensorTemperatura.begin();
    sensorNivelAgua.begin();

    sensorTemperatura.solicitarLeitura();
    sensorPH.iniciarLeituras();

    inicioTurno = millis();

    Serial.println("Iniciando aquecimento...");
}

void loop()
{
    manterConexoes();

    coletarLeituras();

    alternarTurnos();

    publicarDados();
}
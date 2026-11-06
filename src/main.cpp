#include <Arduino.h>

#include "Pins.h"
#include "Config.h" // <-- Suas variáveis const char* estão aqui dentro!

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

String dynamicClientId = "";

void setup()
{
    Serial.begin(115200);

    // Wi-Fi
    wifiManager.begin();
    // Atualizado para usar os novos nomes do Config.h
    wifiManager.connect(CONF_SSID, CONF_PASSWORD);

    // MQTT
    mqttManager.begin();
    
    // ESCALABILIDADE: Gerando o Client ID único a partir do MAC da Arduino Uno R4
    uint8_t mac[6];
    WiFi.macAddress(mac);
    
    dynamicClientId = "Arduino-";
    for (int i = 0; i < 6; i++) {
        if (mac[i] < 0x10) dynamicClientId += "0";
        dynamicClientId += String(mac[i], HEX);
    }
    dynamicClientId.toUpperCase();

    // Atualizado para usar os novos nomes do Config.h e o ID dinâmico global
    mqttManager.connect(dynamicClientId.c_str(), CONF_MQTT_USER, CONF_MQTT_PASS);

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
    manterConexoes(dynamicClientId.c_str());

    coletarLeituras();

    alternarTurnos();

    // Lembre-se de usar a variável `topico_pub` dentro do seu gerenciador/função de publicação!
    publicarDados();
}

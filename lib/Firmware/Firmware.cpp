#include "Firmware.h"
#include "FirmwareContext.h"

#include "Config.h"

#include <Arduino.h>

void manterConexoes() {

    wifiManager.reconnect();

    if (wifiManager.isConnected())
    {
        mqttManager.reconnect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
        mqttManager.loop();
    }
}

void coletarLeituras() {

    unsigned long agora = millis();

    if (agora - ultimaLeitura >= INTERVALO_LEITURA)
    {
        ultimaLeitura = agora;

        if (turnoPH)
            sensorPH.coletarAmostra();
        else
            sensorCondutividade.coletarAmostra();
    }
}

void alternarTurnos() {

    unsigned long agora = millis();

    if (agora - inicioTurno < TEMPO_TURNO)
        return;

    inicioTurno = agora;

    if (turnoPH)
    {
        ultimoPH = sensorPH.calcularMediaADC();

        Serial.print("ADC pH: ");
        Serial.println(ultimoPH);

        sensorCondutividade.iniciarLeituras();
    }
    else
    {
        ultimaCondutividade = sensorCondutividade.calcularMediaADC();

        Serial.print("ADC Condutividade: ");
        Serial.println(ultimaCondutividade);

        ultimaTemperatura = sensorTemperatura.lerGraus();
        ultimoNivelAgua = sensorNivelAgua.temAgua();

        sensorTemperatura.solicitarLeitura();

        if (!aquecimentoConcluido)
        {
            ciclosConcluidos++;

            Serial.print("Aquecimento ");
            Serial.print(ciclosConcluidos);
            Serial.print("/");
            Serial.println(CICLOS_AQUECIMENTO);

            if (ciclosConcluidos >= CICLOS_AQUECIMENTO)
            {
                aquecimentoConcluido = true;
                Serial.println("Sistema pronto.");
            }
        }
        else {
            dadosProntos = true;
        }

        sensorPH.iniciarLeituras();
    }

    turnoPH = !turnoPH;
}

void publicarDados()
{
    if (!dadosProntos)
        return;

    Serial.println("========== MQTT ==========");

    Serial.print("pH ADC: ");
    Serial.println(ultimoPH);

    Serial.print("Condutividade ADC: ");
    Serial.println(ultimaCondutividade);

    Serial.print("Temperatura: ");
    Serial.println(ultimaTemperatura);

    Serial.print("Água: ");
    Serial.println(ultimoNivelAgua ? "SIM" : "NAO");

    // Monta o JSON
    String payload = "{";
    payload += "\"adc_ph\":" + String(ultimoPH, 0);
    payload += ",\"adc_condut\":" + String(ultimaCondutividade, 0);
    payload += ",\"temperature\":" + String(ultimaTemperatura, 2);
    payload += ",\"water_level\":" + String(ultimoNivelAgua ? 1 : 0);
    payload += "}";

    // Exibe o JSON
    Serial.println(payload);

    // Publica no MQTT
    mqttManager.publish(payload.c_str());

    Serial.println("==========================");

    dadosProntos = false;
}
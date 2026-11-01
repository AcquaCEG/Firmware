# 🇺🇸 English

# AcquaCEG Firmware

Firmware responsible for acquiring water quality data, processing sensor readings and publishing them through MQTT as part of the AcquaCEG ecosystem.

Built with **PlatformIO** for the **Arduino Uno R4 WiFi**, this firmware acts as the Edge Device of the AcquaCEG architecture.

---

## Features

- Water pH monitoring
- Electrical conductivity monitoring
- Water temperature monitoring
- Minimum water level detection
- Wi-Fi connectivity
- MQTT communication
- Reading stabilization during startup
- Alternating analog sensor acquisition to reduce electrical interference
- Modular project structure

---

## Hardware

### Board

- Arduino Uno R4 WiFi

### Sensors

- PH-4502C
- TDS Meter v1.0
- DS18B20 Temperature Sensor
- XKC-Y25-PNP Water Level Sensor

---

## Technologies

- C++
- PlatformIO
- Arduino Framework
- WiFiS3
- PubSubClient
- OneWire
- DallasTemperature
- LiquidCrystal_I2C

---

## Project Structure

```text
firmware/
│
├── include/
├── lib/
├── src/
├── platformio.ini
└── README.md
```

---

## System Architecture

```text
Sensors
    │
    ▼
Arduino Uno R4 WiFi
    │
    ▼
AcquaCEG Firmware
    │
    ▼
MQTT Broker
    │
    ▼
FastAPI Backend
    │
    ▼
PostgreSQL
    │
    ▼
Dashboard / Mobile App
```

---

## MQTT

Current publish topic:

```text
acquaceg/devices/arduino-01/sensors/raw
```

Example payload:

```json
{
    "adc_ph": 793,
    "adc_condut": 45,
    "temperature": 2575,
    "water_level": 1
}
```

The backend is responsible for converting raw ADC values into engineering units.

---

## Reading Strategy

To minimize electrical interference between analog sensors, the firmware alternates sensor acquisition cycles.

The current workflow is:

1. Initialize hardware
2. Connect to Wi-Fi
3. Connect to MQTT
4. Wait for sensor stabilization
5. Read pH
6. Publish data
7. Read conductivity
8. Publish data
9. Repeat continuously

The first readings after switching sensors are discarded to improve measurement stability.

---

## Future Improvements

- OTA Firmware Updates
- Watchdog Timer
- Offline data buffering
- MQTT over TLS
- Heartbeat messages
- Automatic sensor calibration
- Moving average / Median filtering
- Device diagnostics
- Remote configuration
- Google Cloud integration

---

## About AcquaCEG

AcquaCEG is an IoT platform under development focused on continuous water quality monitoring.

The project combines Embedded Systems, MQTT, REST APIs, Cloud Computing and Industrial Automation concepts to provide a scalable monitoring solution for laboratories, industrial environments and healthcare applications.

---

# 🇧🇷 Português

# Firmware AcquaCEG

Firmware responsável pela aquisição dos dados dos sensores, processamento inicial das leituras e publicação via MQTT como parte do ecossistema AcquaCEG.

Desenvolvido utilizando **PlatformIO** para a **Arduino Uno R4 WiFi**, este firmware representa o dispositivo de borda (Edge Device) da arquitetura do AcquaCEG.

---

## Funcionalidades

- Monitoramento de pH
- Monitoramento de condutividade elétrica
- Monitoramento de temperatura
- Detecção de nível mínimo de água
- Conexão Wi-Fi
- Comunicação via MQTT
- Estabilização das leituras na inicialização
- Alternância das leituras analógicas para reduzir interferências elétricas
- Estrutura modular do projeto

---

## Hardware

### Placa

- Arduino Uno R4 WiFi

### Sensores

- PH-4502C
- TDS Meter v1.0
- DS18B20
- XKC-Y25-PNP

---

## Tecnologias

- C++
- PlatformIO
- Arduino Framework
- WiFiS3
- PubSubClient
- OneWire
- DallasTemperature
- LiquidCrystal_I2C

---

## Estrutura do Projeto

```text
firmware/
│
├── include/
├── lib/
├── src/
├── platformio.ini
└── README.md
```

---

## Arquitetura do Sistema

```text
Sensores
    │
    ▼
Arduino Uno R4 WiFi
    │
    ▼
Firmware AcquaCEG
    │
    ▼
Broker MQTT
    │
    ▼
Backend FastAPI
    │
    ▼
PostgreSQL
    │
    ▼
Dashboard / Aplicativo Mobile
```

---

## MQTT

Tópico atual de publicação:

```text
acquaceg/devices/arduino-01/sensors/raw
```

Exemplo de mensagem:

```json
{
    "adc_ph": 793,
    "adc_condut": 45,
    "temperature": 2575,
    "water_level": 1
}
```

A conversão dos valores brutos para pH e condutividade é realizada pelo Backend.

---

## Estratégia de Leitura

Para reduzir interferências entre os sensores analógicos, o firmware alterna os ciclos de aquisição.

Fluxo atual:

1. Inicialização do hardware
2. Conexão ao Wi-Fi
3. Conexão ao Broker MQTT
4. Estabilização dos sensores
5. Leitura do pH
6. Publicação dos dados
7. Leitura da condutividade
8. Publicação dos dados
9. Repetição contínua

As primeiras leituras após a troca de sensor são descartadas para melhorar a estabilidade das medições.

---

## Melhorias Futuras

- Atualização OTA
- Watchdog Timer
- Buffer para funcionamento offline
- MQTT seguro (TLS)
- Heartbeat periódico
- Calibração automática
- Filtros digitais
- Diagnóstico do dispositivo
- Configuração remota
- Integração com Google Cloud

---

## Sobre o AcquaCEG

O AcquaCEG é uma plataforma IoT em desenvolvimento voltada ao monitoramento contínuo da qualidade da água.

O projeto integra Sistemas Embarcados, MQTT, APIs REST, Computação em Nuvem e Automação Industrial para oferecer uma solução escalável de monitoramento destinada a laboratórios, ambientes industriais e aplicações na área da saúde.

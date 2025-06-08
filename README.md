# 🌐 SkyAid: drones para resgate e entrega em áreas isoladas

## 👨‍💻 Integrantes

- Pedro Abrantes Andrade | RM558186
- Ricardo Tavares de Oliveira Filho | RM556092
- Victor Alves Carmona | RM555726

## 📌 Descrição do Projeto
Nosso projeto busca viabilizar um monitoramento inteligente e ágil para situações de extrema urgência, conectando dados em tempo real e otimizando a resposta em cenários críticos.
Desenvolvemos, na plataforma **Wokwi**, uma simulação de um sistema baseado em ESP32, que é acoplado aos drones e capta dados de temperatura, umidade, presença de movimento, nível de bateria e localização (latitude e longitude).

Para isso utilizamos os seguintes componentes:

- **DHT22**: Coleta temperatura e umidade do ambiente.
- **Potenciômetro**: Simula o nível da bateria do sistema.
- **Sensor PIR**: Detecta movimento.
- **GPS**: Como não há um componente GPS disponível no Wokwi, simulamos o envio de uma string estática com valores de latitude e longitude.

Os dados coletados são enviados para o **ThingSpeak** via HTTP GET, onde são processados e visualizados em tempo real em um dashboard com gráficos e displays numéricos.

---

### ✅ Teste a simulação:
🔗 [Simulação no Wokwi - HTTP/ThingSpeak](https://wokwi.com/projects/433024360436111361)

### 🧾 Campos no ThingSpeak:
- **Field 1** – Temperatura (°C)
- **Field 2** – Umidade (%)
- **Field 3** – Bateria (%)
- **Field 4** – Movimento PIR (0 ou 1)
- **Field 5** - Latitude
- **Field 6** - Longitude
  
### Visualize os dados no **ThingSpeak**:
- [ThingSpeak já configurado](https://thingspeak.mathworks.com/channels/2983958).

  Caso queira criar um canal próprio para manipular os dados enviados, execute os passos abaixo:
- Crie um canal em [ThingSpeak](https://thingspeak.mathworks.com)
- Copie a **Write API Key** (em API Keys).
- Copie o **Channel Id**
- Edite o código para incluir sua chave e número do canal nas variáveis:
```cpp
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "SUA_API_KEY";
unsigned long channelID = SEU_CHANNELID;
```

---

## 📝 Funcionalidades
✅ Coleta de dados em tempo real  
✅ Envio de dados via HTTP GET para o ThingSpeak  
✅ Visualização de dados em gráficos e displays no ThingSpeak  
✅ Simulação de coordenadas geográficas  

---


## Para saber mais: PIR

No nosso projeto simulamos o detector de presença através de um botão simulando PIR. 
PIR vem do inglês Passive Infrared Sensor (Sensor de Infravermelho Passivo).
Ele detecta variações de calor no ambiente, ou seja, quando algo (como uma pessoa ou animal) se move e emite radiação infravermelha diferente da temperatura de fundo, o sensor detecta essa mudança.
É muito usado em alarmes, luzes automáticas e sistemas de segurança. Quando o botão não está acionado, ele marca o valor 0 indicando que não há detecção de presença. Quando acionado ele marca o valor 1 indicando detecção de movimento.

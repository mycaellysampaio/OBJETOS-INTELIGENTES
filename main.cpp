// === VARIÁVEIS DE ESTADO ===
bool sensorAtual = false;
bool sensorAnterior = false;

// === PINOS ===
const int PIN_SENSOR = 8;
const int PIN_ATUADOR = 12;
const int LED_VERMELHO = 5;
const int LED_AMARELO = 6;
const int LED_VERDE = 7;

void setup() {
  // === CONFIGURAÇÃO DOS PINOS ===
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_ATUADOR, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void loop() {
  // === LEITURA DO SENSOR ===
  sensorAtual = digitalRead(PIN_SENSOR);

  // === INDICAÇÃO DE ESTADO DO SOLO ===
  if (sensorAtual == HIGH) {
    // Solo seco
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    // Solo úmido
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  // === TRANSIÇÃO PARA ESTADO SECO ===
  if (sensorAtual && !sensorAnterior) {
    delay(5000); // Pequena espera antes de agir

    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH); // Aviso: irrigação prestes a iniciar

    while (digitalRead(PIN_SENSOR) == HIGH) {
      // Ativa a irrigação
      digitalWrite(PIN_ATUADOR, HIGH);
      delay(500); // Tempo ligado
      digitalWrite(PIN_ATUADOR, LOW);
      delay(10000); // Intervalo entre ciclos de irrigação
    }

    digitalWrite(LED_AMARELO, LOW); // Fim da irrigação
  }

  // Atualiza o histórico da leitura
  sensorAnterior = sensorAtual;
}
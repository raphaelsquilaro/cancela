#include <ESP32Servo.h>

Servo meuServo;

// Definição dos pinos
#define SERVO_PIN 22
#define TRIG_PIN 14
#define ECHO_PIN 27
#define LED_PIN 16

// Configurações
#define DISTANCIA_ABERTURA 100  // Distância em cm

void setup() {
  Serial.begin(9600);

  // Configuração do servo
  meuServo.attach(SERVO_PIN);
  meuServo.write(0);  // Começa fechado

  // Configuração dos pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("Sistema iniciado!");
}

void loop() {

  // --------------------------------
  // Envia o pulso ultrassônico
  // --------------------------------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // --------------------------------
  // Mede o tempo do eco
  // Timeout de 30 ms
  // --------------------------------
  long duracao = pulseIn(ECHO_PIN, HIGH, 30000);

  // --------------------------------
  // Verifica se recebeu um eco
  // --------------------------------
  if (duracao == 0) {
    Serial.println("Nenhum objeto detectado.");

    meuServo.write(0);
    digitalWrite(LED_PIN, LOW);

    delay(100);
    return;
  }

  // --------------------------------
  // Calcula a distância
  // --------------------------------
  float distancia = (duracao * 0.0343) / 2;

  // --------------------------------
  // Mostra a distância
  // --------------------------------
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // --------------------------------
  // Verifica a distância
  // --------------------------------
  if (distancia <= DISTANCIA_ABERTURA) {

    // Abre o servo
    meuServo.write(90);

    // Liga o LED
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Objeto detectado!");
    Serial.println("Abrindo Servo");
    Serial.println("LED ligado");

  } else {

    // Fecha o servo
    meuServo.write(0);

    // Desliga o LED
    digitalWrite(LED_PIN, LOW);

    Serial.println("Nenhum objeto proximo.");
    Serial.println("Fechando Servo");
    Serial.println("LED desligado");
  }

  // Pequeno intervalo antes da próxima leitura
  delay(100);
}

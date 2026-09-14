# 🤖 Sistema de Abertura Automática com ESP32

Projeto desenvolvido com **ESP32**, **sensor ultrassônico** e **servo motor** para realizar uma abertura automática quando um objeto é detectado a uma distância de até **1 metro**.

O sistema também utiliza um **LED indicador**, que permanece ligado enquanto um objeto está dentro da distância configurada.

## 📋 Descrição

O sensor ultrassônico mede continuamente a distância entre o ESP32 e um objeto.

- Se o objeto estiver a **até 100 cm**, o servo é colocado em **90°** e o LED é ligado.
- Se o objeto estiver a **mais de 100 cm**, o servo retorna para **0°** e o LED é desligado.
- Caso o sensor não receba um sinal de retorno, o sistema considera que não há um objeto detectado e mantém o servo fechado.

O projeto pode ser utilizado como base para:

- 🗑️ Lixeira automática
- 🚪 Porta automática
- 📦 Tampa automática
- 🤖 Projetos de automação
- 🎓 Projetos escolares e acadêmicos

---

## 🧰 Componentes necessários

| Componente | Quantidade |
|---|---:|
| ESP32 | 1 |
| Sensor ultrassônico HC-SR04 | 1 |
| Servo motor | 1 |
| LED | 1 |
| Resistor para LED | 1 |
| Jumpers | Conforme necessário |
| Protoboard | 1 |

> **Atenção:** o HC-SR04 tradicional normalmente trabalha com alimentação de 5 V e o sinal **ECHO pode chegar a 5 V**, enquanto o ESP32 utiliza GPIOs de 3,3 V. Para um projeto real, utilize um **divisor de tensão ou conversor de nível lógico no ECHO** para proteger o GPIO do ESP32.

---

## 🔌 Ligações

### ESP32 → Sensor ultrassônico

| HC-SR04 | ESP32 |
|---|---|
| VCC | 5 V |
| GND | GND |
| TRIG | GPIO 14 |
| ECHO | GPIO 27* |

\* Recomenda-se utilizar adaptação de nível de tensão no sinal ECHO.

### ESP32 → Servo

| Servo | ESP32 |
|---|---|
| Sinal | GPIO 22 |
| VCC | Fonte adequada para o servo |
| GND | GND |

> Servos podem consumir bastante corrente. Para servos maiores, é recomendado utilizar uma fonte externa adequada e conectar o **GND da fonte ao GND do ESP32**.

### ESP32 → LED

| Componente | ESP32 |
|---|---|
| Anodo (+) | GPIO 16 através de resistor |
| Catodo (-) | GND |

---

## 📐 Funcionamento

O sistema segue o seguinte fluxo:

```text
             INÍCIO
                │
                ▼
        Mede a distância
                │
                ▼
      Recebe o eco do sensor?
          │             │
         NÃO           SIM
          │             │
          ▼             ▼
     Servo = 0°    Calcula distância
     LED = OFF           │
                         ▼
                Distância ≤ 100 cm?
                   │           │
                  SIM         NÃO
                   │           │
                   ▼           ▼
              Servo = 90°  Servo = 0°
              LED = ON     LED = OFF
                   │           │
                   └─────┬─────┘
                         │
                         ▼
                 Nova medição
```

---

## 💻 Requisitos de software

Para compilar o projeto, é necessário:

- **Arduino IDE**
- Suporte para **ESP32** instalado na Arduino IDE
- Biblioteca **ESP32Servo**

### Instalação da biblioteca

Na Arduino IDE:

**Sketch → Include Library → Manage Libraries**

Pesquise por:

```text
ESP32Servo
```

e instale a biblioteca.

---

## ⚙️ Configurações

A distância para abertura pode ser alterada nesta linha:

```cpp
#define DISTANCIA_ABERTURA 100
```

Por exemplo, para abrir quando o objeto estiver a até 50 cm:

```cpp
#define DISTANCIA_ABERTURA 50
```

O ângulo do servo também pode ser alterado:

```cpp
meuServo.write(90);
```

Para fechar:

```cpp
meuServo.write(0);
```

---

## 🧠 Como a distância é calculada?

O sensor ultrassônico envia uma onda sonora e mede o tempo necessário para o eco retornar.

O código utiliza:

```cpp
float distancia = (duracao * 0.0343) / 2;
```

O valor **0,0343** representa aproximadamente a velocidade do som em centímetros por microssegundo.

A divisão por **2** é necessária porque o som percorre o caminho de ida e volta:

```text
ESP32 ───────► OBJETO
       ida

ESP32 ◄─────── OBJETO
       volta
```

---

## 🛡️ Tratamento de erro

O código utiliza um timeout no `pulseIn()`:

```cpp
long duracao = pulseIn(ECHO_PIN, HIGH, 30000);
```

O valor `30000` representa um limite de **30.000 microssegundos (30 ms)** para aguardar o retorno do sensor.

Se nenhum eco for recebido:

```cpp
if (duracao == 0) {
    meuServo.write(0);
    digitalWrite(LED_PIN, LOW);
}
```

O sistema mantém o servo fechado e o LED desligado.

---

## 📟 Monitor Serial

O projeto utiliza o monitor serial para informar o estado do sistema.

Exemplo:

```text
Sistema iniciado!
Distancia: 42.35 cm
Objeto detectado!
Abrindo Servo
LED ligado
```

Quando o objeto está distante:

```text
Distancia: 135.72 cm
Nenhum objeto proximo.
Fechando Servo
LED desligado
```

---

## 📁 Estrutura do projeto

Uma estrutura simples para o projeto pode ser:

```text
esp32-abertura-automatica/
│
├── README.md
└── abertura_automatica.ino
```

---

## 🚀 Como executar

1. Monte o circuito conforme as ligações.
2. Instale a biblioteca `ESP32Servo`.
3. Conecte o ESP32 ao computador.
4. Abra o arquivo `.ino` na Arduino IDE.
5. Selecione a placa ESP32 correta.
6. Selecione a porta USB correspondente.
7. Faça o upload do código.
8. Abra o **Monitor Serial** em `9600 baud`.
9. Aproxime um objeto do sensor.
10. Observe o servo e o LED responderem à distância.

---

## 🔧 Melhorias futuras

Algumas melhorias que podem ser adicionadas ao projeto:

- [ ] Fazer o LED piscar quando um objeto for detectado.
- [ ] Adicionar um display LCD/OLED para mostrar a distância.
- [ ] Utilizar um buzzer como indicador sonoro.
- [ ] Adicionar controle de velocidade do servo.
- [ ] Utilizar **histerese** para evitar movimentos repetitivos do servo próximos ao limite de 100 cm.
- [ ] Adicionar botão para abertura manual.
- [ ] Criar controle via Wi-Fi usando o ESP32.
- [ ] Adicionar diferentes níveis de distância para diferentes comportamentos.

---

## 📜 Licença

Este projeto pode ser utilizado para fins **educacionais e de aprendizado**.

Sinta-se à vontade para modificar o código, adaptar o circuito e criar novas funcionalidades.

---

## 👨‍💻 Tecnologias utilizadas

- **C++ / Arduino**
- **ESP32**
- **ESP32Servo**
- **HC-SR04**
- **Servo motor**
- **LED**

---

## ⭐ Objetivo

O objetivo deste projeto é demonstrar, de forma prática, como utilizar um **ESP32 para realizar automação baseada em distância**, integrando sensores, atuadores e indicadores visuais.

# 🚀 Projeto: Comunicação Serial com RP2040

## 📌 Sumário

- [📖 Descrição](#-descrição)
- [⚙️ Funcionalidades Implementadas](#️-funcionalidades-implementadas)
- [🔧 Componentes Utilizados](#-componentes-utilizados)
- [🎯 Objetivos](#-objetivos)
- [🛠 Requisitos do Projeto](#-requisitos-do-projeto)
- [▶️ Instruções de Uso](#️-instruções-de-uso)
- [🧪 Testes Realizados](#-testes-realizados)
- [📜 Licença](#-licença)

---

## 📖 Descrição

Este projeto explora a **comunicação serial** no microcontrolador **RP2040** e a integração de diversos periféricos na placa **BitDogLab**. As funcionalidades incluem o controle de **LEDs RGB e WS2812**, exibição de caracteres no **display SSD1306** e interação com botões físicos, utilizando **UART e I2C**.

---

## ⚙️ Funcionalidades Implementadas

### 📟 **Interação com o Display SSD1306**
- Entrada de caracteres via **Serial Monitor** do VS Code.
- Exibição do caractere digitado no **display SSD1306**.

### 🔢 **Exibição de Números na Matriz WS2812**
- Quando um número entre **0 e 9** for digitado, um símbolo correspondente será exibido na matriz **5x5 WS2812**.

### 🎨 **Controle de LEDs RGB**
- **Botão A:** Alterna o estado do **LED Verde**.
- **Botão B:** Alterna o estado do **LED Azul**.
- Mensagem informativa exibida no **display SSD1306** e no **Serial Monitor**.

### 🛠 **Outros Recursos**
- Modificação da biblioteca `font.h` para inclusão de caracteres minúsculos.
- Uso de **interrupções (IRQ)** para detecção de botões.
- Implementação de **debouncing via software**.

---

## 🔧 Componentes Utilizados

- **Raspberry Pi Pico W (RP2040)** – Microcontrolador principal.
- **Matriz 5x5 WS2812** – LEDs endereçáveis conectados à **GPIO 7**.
- **LED RGB** – Conectado às **GPIOs 11, 12 e 13**.
- **Botão A** – Conectado à **GPIO 5**.
- **Botão B** – Conectado à **GPIO 6**.
- **Display SSD1306** – Comunicação via **I2C (GPIO 14 e 15)**.

---

## 🎯 Objetivos

✔️ Compreender e aplicar **UART e I2C** em microcontroladores.
✔️ Manipular e controlar **LEDs comuns e WS2812**.
✔️ Implementar **debounce** e interrupções para botões físicos.
✔️ Enviar e exibir informações através da **UART**.
✔️ Desenvolver um código **organizado e bem documentado**.

---

## 🛠 Requisitos do Projeto

1️⃣ **Interrupções:** Todos os eventos dos botões devem ser capturados via **IRQ**.
2️⃣ **Debounce:** Implementação obrigatória para evitar falsos acionamentos.
3️⃣ **Controle de LEDs:** Uso de LEDs comuns e WS2812.
4️⃣ **Uso do Display SSD1306:** Exibição de caracteres maiúsculos e minúsculos.
5️⃣ **Comunicação via UART:** Envio de informações ao **Serial Monitor**.
6️⃣ **Código bem estruturado e comentado**.

---

## ▶️ Instruções de Uso

### 📥 1. Clonar o Repositório
```bash
git clone https://github.com/Kenjibercysec/EmbarcaTech_A6U4.git
```

### 💻 2. Configurar o Ambiente de Desenvolvimento
- Instale o **VS Code** e o **Pico SDK**.
- Navegue até a pasta `build` e execute:
```bash
cmake -G Ninja ..
ninja
```

### 🔄 3. Carregar o Código no Raspberry Pi Pico W
- Conecte a placa **Raspberry Pi Pico W** ao computador.
- Compile e envie o código através do **VS Code**.

### 🎮 4. Interagir com o Sistema
- Digite caracteres no **Serial Monitor** para vê-los no **display SSD1306**.
- Pressione **Botão A** para alternar o **LED Verde**.
- Pressione **Botão B** para alternar o **LED Azul**.
- Digite números (0-9) para visualizar os símbolos na **matriz WS2812**.

---

## 🧪 Testes Realizados

✅ Testes no **simulador Wokwi** para validação inicial.
✅ Testes físicos na **placa Raspberry Pi Pico W**.
✅ Validação do debounce e funcionamento correto das **interrupções**.

---

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).


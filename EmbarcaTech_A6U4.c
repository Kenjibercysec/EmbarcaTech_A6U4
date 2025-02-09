#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "Serial_Com.pio.h"
#include "inc/font.h"
#include "inc/ssd1306.h"

//-------------------------------------------

// Variáveis globais
int static volatile indice = 0; //indice do vetor de leds
uint count = 0; //contador de tempo
uint actual_time = 0; //tempo atual
uint valor_led; //valor do led
uint sm;
PIO pio = pio0;
bool GREEN_LED_OFF = false; //variável para countrole do led verde
bool BLUE_LED_OFF = false;  //variável para countrole do led azul
bool RED_LED_OFF = false; //variável para countrole do led vermelho
double r = 0.3, g = 0.3, b = 0.3;  
int prev_number = -1; //variável para controle do número anterior
ssd1306_t ssd; //display

//-------------------------------------------


// Pinos e porta I2C
#define LED_PIN_GREEN 11 //led verde
#define LED_PIN_BLUE 12 //led azul
#define LED_PIN_RED 13 //led vermelho
#define NUM_PIXELS 25 //número de leds na matriz
#define LED_PIN 7 //pino de saída da matriz de led
#define BOTAO_A 5 //pino saida botao a
#define BOTAO_B 6 //pino saida botao b
#define I2C_PORT i2c1 //porta I2C
#define I2C_SDA 14 //pino SDA
#define I2C_SCL 15 //pino SCL
#define display_address 0x3C //endereço do display


// Matriz de leds  
uint matrix_rgb(float r, float g, float b){
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (R << 16) | (G << 24) | (B << 8);
}

//-------------------------------------------

// Função para converter as posições da matriz para vetorial
  int getIndex(int x, int y){
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda
    if (y % 2 == 0){
      return 24 - (y * 5 + x); 
    }else{
      return 24 - (y * 5 + (4 - x)); 
    }
  }

  
  // FUNCAO PARA DESENHAR A MATRIZ
  void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(desenho[i] * r, desenho[i] * g, desenho[i] * b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}
  


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "EmbarcaTech_A6U4.pio.h"
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
  

void callback_button(uint gpiom , uint32_t events){
    uint time = to_ms_since_boot(get_absolute_time());
 if (time - actual_time > 250) { // Condição para evitar múltiplos pressionamentos (debounce)
        actual_time = time;       // Atualiza o tempo
        if (gpio == BOTAO_A) {  // Verifica se o botão A foi pressionado
            GREEN_LED_OFF = !GREEN_LED_OFF; // Inverte o estado do LED verde
            gpio_put(LED_PIN_GREEN, GREEN_LED_OFF);  // Acende o LED verde
                    if (GREEN_LED_OFF == false){
                        
                        printf("LED verde desligado\n");
                    } else {
                        printf("LED verde ligado\n");
                    }
 } else if (gpio == BOTAO_B) { // Verifica se o botão B foi pressionado
            BLUE_LED_OFF = !BLUE_LED_OFF; // Inverte o estado do LED azul
         gpio_put(LED_PIN_BLUE, BLUE_LED_OFF);  // Acende o LED verde
                 if (BLUE_LED_OFF == false){
                            printf("LED azul desligado\n");
                 } else {
                            printf("LED azul ligado\n");
             }
}


//-------------------------------------------

// Atualização do display
ssd1306_fill(&ssd, 0); //limpa o display

gpio_get(LED_PIN_GREEN) ? ssd1306_draw_string(&ssd, "Green LED: ON", 10, 10) :
                        ssd1306_draw_string(&ssd, "Green LED: OFF", 10, 10);
gpio_get(LED_PIN_BLUE) ? ssd1306_draw_string(&ssd, "Blue LED: ON", 10, 30) :
                        ssd1306_draw_string(&ssd, "Blue LED: OFF", 10, 30);
ssd1306_send_data(&ssd);

//-------------------------------------------

stdio_init_all(); 
gpio_init(LED_PIN);
gpio_init(LED_PIN_RED);
gpio_init(LED_PIN_GREEN);
gpio_init(LED_PIN_BLUE);
gpio_init(BOTAO_A);
gpio_init(BOTAO_B);
gpio_set_dir(LED_PIN, GPIO_OUT);
gpio_set_dir(LED_PIN_RED, GPIO_OUT);
gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
gpio_set_dir(BOTAO_A, GPIO_IN);
gpio_set_dir(BOTAO_B, GPIO_IN);
gpio_pull_up(BOTAO_A);
gpio_pull_up(BOTAO_B);
gpio_put(GREEN_LED_OFF, false);
gpio_put(BLUE_LED_OFF, false);
gpio_put(RED_LED_OFF, false);

    //-------------------------------------------

    // Inicialização do display
i2c_init(I2C_PORT, 400 * 1000);
gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
gpio_pull_up(I2C_SDA); 
gpio_pull_up(I2C_SCL); 
ssd.i2c_port = I2C_PORT;
ssd.address = display_address;
ssd.width = 128;
ssd.height = 64;
ssd.external_vcc = false;
ssd1306_init(&ssd, 128, 64, false, display_address, I2C_PORT);
ssd1306_config(&ssd);   


//-------------------------------------------

// Verificação do clock
printf("iniciando a transmissão PIO");
if (frequenciaClock){
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}else if(!frequenciaClock){
    printf("erro ao configurar a frequencia do clock");
}


//-------------------------------------------

// Configuração dos botões com interrupções
gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &callback_button);
gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &callback_button);

// Inicialização da matriz de LEDs
uint offset = pio_add_program(pio, &pio_matrix_program);
sm = pio_claim_unused_sm(pio, true);
pio_matrix_program_init(pio, sm, offset, LED_PIN);

// Apaga os LEDs ao iniciar o programa
desenho_pio(apagar_leds, valor_led, pio, sm, r, g, b);

// Loop principal para leitura de caracteres
while (true) {
    int c = getchar_timeout_us(0); // Verifica se há caractere disponível sem bloquear

    if (c != PICO_ERROR_TIMEOUT) { // Se um caractere foi recebido
        printf("Caractere recebido: %c\n", (char)c);
        int numero = c - '0';

        ssd1306_fill(&ssd, false);  // Limpa o display
        ssd1306_draw_char(&ssd, (char)c, 20, 30); // Desenha o caractere no display
        ssd1306_send_data(&ssd);    // Atualiza o display

        if (numero != numero_anterior) { // Se o número é diferente do anterior
            numero_anterior = numero;    // Atualiza o número anterior

            if (numero >= 0 && numero <= 9) { // Se o número está entre 0 e 9
                desenho_pio(numeros[numero], valor_led, pio, sm, r, g, b); // Desenha o número na matriz de LEDs
            } else {
                desenho_pio(apagar_leds, valor_led, pio, sm, r, g, b); // Apaga os LEDs
                printf("Caractere inválido!\n"); // Informa caractere inválido
            }
        }
    }
}

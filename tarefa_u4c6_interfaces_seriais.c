#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bibliotecas/matriz_led.h"
#include "bibliotecas/numeros_matriz_leds.h"
#include "bibliotecas/ssd1306.h"
#include "bibliotecas/font.h"

#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11

#define MATRIZ_LED 7
#define BUTTON_A 5
#define BUTTON_B 6

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

#define INTENSIDADE 0.01

ssd1306_t ssd; // Inicializa a estrutura do display
static volatile uint32_t last_time = 0;


void inicializacaoGPIOs(){
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);

    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN,GPIO_OUT);
    gpio_set_dir(LED_BLUE,GPIO_OUT);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B,GPIO_IN);

    gpio_put(LED_RED,0);
    gpio_put(LED_GREEN,0);
    gpio_put(LED_BLUE,0);

    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    inicializacaoMatrizLed(MATRIZ_LED);

    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

void desenhaCaractereNoDisplay(char c){
    ssd1306_fill(&ssd,false);
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_char(&ssd, c, 60, 30); // Desenha uma string    
    ssd1306_draw_string(&ssd, "ALUNO: ANDRE", 15, 48); // Desenha uma string    
    ssd1306_send_data(&ssd);
}

void desenhaFraseNoDisplay(char *frase){
    ssd1306_fill(&ssd,false);
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, frase, 20, 30); // Desenha uma string    
    ssd1306_draw_string(&ssd, "ALUNO: ANDRE", 15, 48); // Desenha uma string    
    ssd1306_send_data(&ssd);
}

void tratamentoDeInterrupcaoNoBotao(uint gpio,uint32_t event){
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if ((current_time - last_time) > 200000) {
        last_time = current_time; 
        if(gpio==BUTTON_A){
            
            printf("Apertou Botao A\n");
            gpio_put(LED_GREEN,!gpio_get(LED_GREEN));
            if(gpio_get(LED_GREEN)){
                desenhaFraseNoDisplay("Verde ON");
            }else{
                desenhaFraseNoDisplay("Verde OFF");
            }
        }
        if(gpio==BUTTON_B){
            
            printf("Apertou Botao B\n");
            gpio_put(LED_BLUE,!gpio_get(LED_BLUE));
            if(gpio_get(LED_BLUE)){
                desenhaFraseNoDisplay("Azul ON");
            }else{
                desenhaFraseNoDisplay("Azul OFF");
            }
        }
    }
    
}


void desenhaNaMatrizDeLED(char numero){
    resetLeds();
    if(numero == '0'){ligaLEDsNaCor(numero0,13,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '1'){ligaLEDsNaCor(numero1,5,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '2'){ligaLEDsNaCor(numero2,11,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '3'){ligaLEDsNaCor(numero3,11,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '4'){ligaLEDsNaCor(numero4,9,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '5'){ligaLEDsNaCor(numero5,11,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '6'){ligaLEDsNaCor(numero6,12,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '7'){ligaLEDsNaCor(numero7,7,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '8'){ligaLEDsNaCor(numero8,13,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
    if(numero == '9'){ligaLEDsNaCor(numero9,12,getCorRGB(INTENSIDADE,INTENSIDADE,INTENSIDADE));}
}

int main()
{
    stdio_init_all();
    inicializacaoGPIOs();
    
    gpio_set_irq_enabled_with_callback(BUTTON_A,GPIO_IRQ_EDGE_FALL,true,tratamentoDeInterrupcaoNoBotao);
    gpio_set_irq_enabled_with_callback(BUTTON_B,GPIO_IRQ_EDGE_FALL,true,tratamentoDeInterrupcaoNoBotao);

    desenhaCaractereNoDisplay(' ');
    while (true) {
        if(stdio_usb_connected()){
            char c;
            if(scanf("%c",&c)){
                desenhaCaractereNoDisplay(c);
                if((c>='0')&&(c<='9')){
                    desenhaNaMatrizDeLED(c);
                }else{
                    desligaTodosLEDs();
                }
            }
        }
    }
}

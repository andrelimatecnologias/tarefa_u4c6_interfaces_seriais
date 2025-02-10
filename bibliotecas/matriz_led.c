
#include "matriz_led.h"
#include<stdio.h>
#include"pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "matriz_led.pio.h"



uint32_t getCorRGB(double r, double g, double b)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}


void pintaFrameCompleto(){
    
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, cores[mapeamento[i]]);
    }
    
}



void ligaLEDsNaCor(uint8_t *leds, int quant, uint32_t cor){
  for(int i=0;i<quant;i++){
    cores[leds[i]] = cor;
  }
  pintaFrameCompleto();
}


void ligaLEDsNasCores(int *leds, int quant, uint32_t *cores_esc){
  for(int i=0;i<quant;i++){
    cores[leds[i]]=cores_esc[i];
  }
  pintaFrameCompleto();
}


void ligaTodosLEDsNaCor(uint32_t cor){
    for(int i=0;i<NUM_PIXELS;i++){
        cores[i] = cor;
    }
    pintaFrameCompleto();
}

void ligaTodosLEDsNasCores(uint32_t *cores_esc){
    for(int i=0;i<NUM_PIXELS;i++){
      cores[i]=cores_esc[i];
    }
    pintaFrameCompleto();
}

void desligaTodosLEDs(){
    resetLeds();
    pintaFrameCompleto();
}

void resetLeds(){
  for(int i=0;i<NUM_PIXELS;i++){
    cores[i]=0;
  }
}


void inicializacaoMatrizLed(int gpio_matriz){
  stdio_init_all();
  
  GPIO_MATRIZ_LED = gpio_matriz;
  pio = pio0; 
  //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
  set_sys_clock_khz(128000, false);
  //configurações da PIO
  uint offset = pio_add_program(pio, &matriz_led_program);
  sm = pio_claim_unused_sm(pio, true);
  matriz_led_program_init(pio, sm, offset, GPIO_MATRIZ_LED);
  //pio_matrix_program_init();  
}

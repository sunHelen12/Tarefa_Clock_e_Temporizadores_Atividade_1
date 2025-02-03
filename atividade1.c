#include <stdio.h> //biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include "pico/stdlib.h" //biblioteca padrão para alocação de memória, controle de processos, etc.
#include "hardware/timer.h" //biblioteca da Raspberry Pi Pico para funções básicas (GPIO, UART, delays, etc.)

//definindo os GPIOs para os LEDs
#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

//callback do temporizador periódico
bool repeating_timer_callback(struct repeating_timer *t) {
    static uint estado = 0;

    //apagando todos os LEDs antes de mudar o estado
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 0); 
    gpio_put(LED_PIN_GREEN, 0);

    //alternar entre os estados do semáforo
    if(estado == 0){
        gpio_put(LED_PIN_RED, 1); //liga vermelho
        printf("Semáforo: Vermelho\n");
    } else if (estado == 1){
        gpio_put(LED_PIN_YELLOW, 1); //liga amarelo
        printf("Semáforo: Amarelo\n");
    } else if(estado == 2){
        gpio_put(LED_PIN_GREEN, 1); //liga verde
        printf("Semáforo: Verde\n");
    }

    estado = (estado + 1) % 3; //garante um ciclo de 0 a 3
    return true;
}


int main(){
   //incializando LEDs
    stdio_init_all(); 
}

#include <stdio.h> //biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include "pico/stdlib.h" //biblioteca padrão para alocação de memória, controle de processos, etc.
#include "hardware/timer.h" //biblioteca da Raspberry Pi Pico para funções básicas (GPIO, UART, delays, etc.)

//definindo os GPIOs para os LEDs
#define LED_PIN_RED 13
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 11

// rotina callback do temporizador periódico
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

//rotina de teste para verificar se os pinos dos LEDs estão configurados corretamente
void test_gpio_setup() {
    printf("Testando configuração dos GPIOs...\n");

    gpio_put(LED_PIN_RED, 1);
    sleep_ms(500);
    gpio_put(LED_PIN_RED, 0);

    gpio_put(LED_PIN_YELLOW, 1);
    sleep_ms(500);
    gpio_put(LED_PIN_YELLOW, 0);

    gpio_put(LED_PIN_GREEN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN_GREEN, 0);

    printf("Teste dos GPIOs concluído.\n");
}

//rotina principal
int main(){
   //incializa comunicação serial
    stdio_init_all(); 

    //inicializar os pinos GPIO
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_YELLOW);
    gpio_init(LED_PIN_GREEN);

    //configura como saída
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    //chamando rotinas de teste
    test_gpio_setup();
    sleep_ms(50);
            
    //cria  e inicializa o temporizador com 3000ms = 3 segundos
    struct repeating_timer timer;
    
    //essa condicional serve como teste, caso a inicialização do temporizador apresente erro
    //ela irá imprimir uma mensagem de erro e encerrará o programa
    if (!add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer)) {
        printf("Erro ao iniciar o temporizador!\n");
        return 1;
    }

    //loop principal
    while(true){
        printf("Se passou 1 Segundo...\n");
        sleep_ms(1000); //mensagem a cada 1 segundo
       
    }

    return 0;
}

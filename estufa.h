/**
*   @author Pedro Serer.
*/

#ifndef ESTUFA_H_INCLUDED
#define ESTUFA_H_INCLUDED

#ifndef LiquidCrystal_h
    #include <LiquidCrystal.h>
    LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#endif

#ifndef dht_h
    #include <dht.h>
    
    dht DHT1;
    dht DHT2;
#endif

/*###########################  PORTAS ANALÓGICAS E DIGITAIS ###########################*/

#define PINO_TEMP_AMBIENTE     A0
#define PINO_TEMP_LOCAL        A1
#define POTENCIOMETRO          A2
#define PINO_LED               10

/*###########################  CONSTANTES PARA O DISPLAY ###########################*/

const char* msg[] = {
  "Temp. Ambiente:",
  "Temp. Local:"
};

const byte bolinha[8] = {
  B01100,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000,
};

/*###########################  FUNCOES PARA O DISPLAY ###########################*/

int numero_atual = 0, posicao = 0;
float temperatura = 0;
float lim_anterior;
float limite_temperatura;
char* mensagem_atual;
bool atuador = true;
bool passou = false;


/**
*   Método que alterna entre as mensagens do vetor 'msg'
*
*   @param void
*/

void mensagemAtual() 
{
    if (posicao > 1) posicao = 0;

    mensagem_atual = (char*) msg[posicao];
    lcd.print(mensagem_atual);

    posicao += 1;
}

/**
*   Método que mostra o limite de temperatura
*   
*   @param void
*/

void mostraTemperatura () 
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Novo limite:");
    lcd.setCursor(0, 1);
    lcd.print(limite_temperatura);
    lcd.print(" ");
    lcd.write(byte(1));
    lcd.print("C");

    delay(280);
    passou = true;
}

/**
*   Função que faz scroll no Display:
*
*   @param char* | Ponteiro para o lado do scroll
*   @return void
*/

void rolar (char* lado) 
{
    for (int i = 0; i < 16; i++) {
        if (lado == "esquerda") lcd.scrollDisplayLeft();
        if (lado == "direita") lcd.scrollDisplayRight();

        limite_temperatura = map(analogRead(POTENCIOMETRO), 0, 1023, 0, 60);

        if (lim_anterior == limite_temperatura && passou) {
            passou = false;
            return;
        }

        if (lim_anterior != limite_temperatura) {
            lim_anterior = limite_temperatura;
            mostraTemperatura();
            continue;
        }

        delay(440);
    }
}

#endif

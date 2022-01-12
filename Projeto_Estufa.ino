#include "estufa.h"

void setup ()
{
    lcd.begin(16, 2);

    lcd.createChar(1, bolinha);
    pinMode(PINO_TEMP_LOCAL, INPUT);
    pinMode(PINO_TEMP_AMBIENTE, INPUT);
    pinMode(PINO_LED, OUTPUT);

    lim_anterior = map(analogRead(POTENCIOMETRO), 0, 1023, 0, 60);
}

void loop ()
{
    DHT1.read11(PINO_TEMP_LOCAL);
    DHT2.read11(PINO_TEMP_AMBIENTE);
    lcd.clear();

    if (posicao == 1) {
        temperatura = DHT1.temperature;
        temperatura >= 60 ? atuador = false : atuador = true;
    } else {
        temperatura = DHT2.temperature;
    }

    digitalWrite(PINO_LED, atuador);
    Serial.println(temperatura);
    lcd.setCursor(0, 0);
    mensagemAtual();

    lcd.setCursor(0, 1);
    lcd.print(temperatura);

    if (temperatura > -10) {
        lcd.setCursor(6, 1);
    } else {
        lcd.setCursor(7, 1);
    }

    lcd.write(byte(1));
    lcd.print("C");
    rolar("direita");

    delay(400);
}

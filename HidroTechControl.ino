#define condutividade  A0
#define nivelAlto      3
#define nivelBaixo     4
#define bombaPrincipal 5 //relé
#define bombaDescarte  6 //relé

void controlaBombas(bool flag);

void setup() {
    pinMode(nivelAlto,      INPUT);
    pinMode(nivelBaixo,     INPUT);
    pinMode(bombaPrincipal, INPUT);
    pinMode(bombaDescarte,  INPUT);
}

void loop() {
    bool valorNivelBaixo = digitalRead(nivelBaixo);
    //controle das bombas por meio dos relés com base no sensor de condutividade
    if (analogRead(condutividade) >= 512) {
        controleBombas(1, false); //desativa a bomba principal
        controleBombas(2, true); //aciona o descarte de água com base no sensor de nível baixo
    } else {
        if (!valorNivelBaixo){
            //ativa a solenóide
            controleBombas(1, false);
            controleBombas(2, false);
        }
        //else ativa uma solenóide para encher o tanque principal
        else if (digitalRead(nivelAlto)) {
            //desativar a solenóide
            controlebombas(1, true);
        }
    }
}

void controleNivel(bool nivel) {
    
}

void controlaBombas(bool flag, int bomba) {
    switch(bomba) {
        case 1:
            digitalWrite(bombaPrincipal, flag);
            break;
        case 2:
            digitalWrite(bombaDescarte,  flag);
            break;            
    }
}

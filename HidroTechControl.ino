#define condutividade  A0
#define nivelAlto      8
#define nivelBaixo     9
#define bombaPrincipal 7 //relé
#define bombaDescarte  4 //relédescarte

bool switchBomba = false;
bool flag = false;

long previousMillis = 0;        
long timeOutColeta = 20000; 


void controlaBombas(bool flag);

void setup() {
    Serial.begin(9600);
    pinMode(nivelAlto,      INPUT);
    pinMode(nivelBaixo,     INPUT);
    pinMode(condutividade, INPUT);
    pinMode(bombaPrincipal, OUTPUT);
    pinMode(bombaDescarte,  OUTPUT);
    digitalWrite(bombaPrincipal,LOW);
    digitalWrite(bombaDescarte,LOW);
}

void loop() {
    unsigned long currentMillis = millis();
    bool valorNivelBaixo = digitalRead(nivelBaixo);
    
    int valorCondutividade = map(analogRead(condutividade), 1023, 0, 0, 1023);
    //controle das bombas por meio dos relés com base no sensor de condutividade
    Serial.println(valorCondutividade);
    if (valorCondutividade >= 512) {
        //ficou choca
        digitalWrite(bombaDescarte,  true); //desativa a bomba principal
    } else {
        digitalWrite(bombaDescarte,  false);
        if (currentMillis - previousMillis >= timeOutColeta) { //Verifica se o tempo desgotou
            previousMillis = currentMillis;  
            switchBomba = !switchBomba; 
            digitalWrite(bombaPrincipal, switchBomba); 
        }
//        if (!valorNivelBaixo){
//            //ativa a solenóide
//            controleBombas(1, false);
//            controleBombas(2, false);
//        }
//        //else ativa uma solenóide para encher o tanque principal
//        else if (digitalRead(nivelAlto)) {
//            //desativar a solenóide
//            controlebombas(1, true);
//        }
    }
    //

}

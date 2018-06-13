#define condutividade      0
#define nivelAlto          9
#define nivelAltoDescarte  10
#define nivelBaixo         8
#define bombaPrincipal     7 //relé
#define bombaDescarte      4 //relédescarte

bool switchBomba     =     false;
bool flag            =     false;

long previousMillis  =     0;        
long timeOutColeta   =     5000; 


void controlaBombas(bool flag);

void setup() {
    Serial.begin(9600);
    pinMode(nivelAlto,          INPUT);
    pinMode(nivelBaixo,         INPUT);
    //pinMode(condutividade,      INPUT);
    pinMode(bombaPrincipal,     OUTPUT);
    pinMode(bombaDescarte,      OUTPUT);
    digitalWrite(bombaPrincipal,LOW);
    digitalWrite(bombaDescarte, LOW);
}

void loop() {
    unsigned long currentMillis = millis();
    bool valorNivelBaixo = digitalRead(nivelBaixo);

    int valorCondutividade = analogRead(condutividade);//map(analogRead(condutividade), 1023, 0, 0, 1023);
    
    Serial.print("condutividade: ");
    Serial.println(valorCondutividade);
       
    if (valorCondutividade <= 150) {
        //ficou choca
        while(analogRead(condutividade)<=150){
          digitalWrite(bombaDescarte,  true); //desativa a bomba principal
          digitalWrite(bombaPrincipal,false);

          Serial.print("analog: ");
          Serial.println(analogRead(condutividade));
        }
    } else {            
            if (!valorNivelBaixo){
                  digitalWrite(bombaPrincipal, false);
                  digitalWrite(bombaDescarte, false);   
                   Serial.println("desligou as duas");           
            } else {            
                  if (currentMillis - previousMillis >= timeOutColeta ) { //Verifica se o tempo desgotou
                      previousMillis = currentMillis;             
                      switchBomba = !switchBomba; 
                      digitalWrite(bombaPrincipal, switchBomba);  
                      digitalWrite(bombaDescarte,  false);  
                      Serial.print("estado bomba");
                      Serial.println(switchBomba);
                  }
              }
    }
      Serial.println("------------------------------------------------");

    

}

 #include <Arduino.h>  // biblioteca padrão para arduino.
 #include <Servo.h>   // biblioteca para o controle dor servos.
 #include <NewPing.h>  // biblioteca para o sensor ultrasonico

#define trigger  12 // Definição do pino digital 11 para o sinal de trigger
#define echo 2 // Definição do pino digital 3 para o sinal echo
#define MAX_DISTANCE 8 // Distância máxima para o sensor (em cm)
NewPing sonar(trigger,echo, MAX_DISTANCE);

//variaveis globais
        int status=0;
        int sta_sensor=0;
        int st_carrinho=0;
        const int config_posicao[3]={0,0,0}; // 
        const int sensor=9;  // sensor indutivo.
        const int botao=7;  // botão liga e desliga.
        const int iman=8; //  variavel booleana para on/off do íman.
        const int statos_carrinho=2;
        const int esteira=10;
        int pos_0=0;
        int pos_1=0;
        int pos_2=0;
        int x=0;

        // instancia um objeto para o servo

        Servo  meus_servos[3]; // array para 3 micro servos motores.

        //int pos=0; // variavel para navegação da posição dos servos.



// funções do projeto
  

void setup() {
    // configurações 
 

    //servos entradas 

    //servo 1
    meus_servos[0].attach(5);
    meus_servos[0].write(175); 
             
    
 
    delay(1000);
 

    //servo 2
    meus_servos[1].attach(6);  
    meus_servos[1].write(80);          
    

    delay(1000);

  

    //servo 3

    meus_servos[2].attach(11);
    meus_servos[2].write(92); 
             
    
    delay(1000);

    // configurações de entradas

    pinMode(sensor,INPUT_PULLUP);     // sensor indutivo
    pinMode(botao,INPUT_PULLUP);     // botão de acionamento
    pinMode(statos_carrinho,INPUT_PULLUP);  // carrinho concluiu a entrega
    
    // configurações de saidas

    pinMode(iman,OUTPUT);  // 
    pinMode(esteira,OUTPUT); // 

    //configuração monitor serial

    Serial.begin(9600);
       
    //SETA AS SAIDAS DO ARDUINO EM NIVEL ALTO
 digitalWrite(esteira,HIGH);    
 digitalWrite(iman,HIGH);

}

void loop() {



/*Serial.println("\n\n");
Serial.println("statos_carrinho: ");
Serial.println(meus_servos[0].read());*/
//Leitura de informações do sensor em cm
//Leitura de informações do sensor em cm
//Leitura de informações do sensor em cm

  

  


// liga o sistema

    if(digitalRead(botao)!=1)
        {  
            status=1;
           


                
        }



    
    while (status==1)
    {
       
    
    
        digitalWrite(esteira,LOW);    // liga a esteira
        delay(250);

        unsigned int uS = sonar.ping(); // Mede a distância em microssegundos
        int cm = sonar.convert_cm(uS); // Converte o tempo em distância (cm)

        //if(digitalRead(sensor)!=1) exemplo com botão

        if(cm > 2 and cm < 7)
        {
            digitalWrite(esteira,HIGH);   // desliga a esteira
            delay(500);
            digitalWrite(iman,LOW);      //  liga o iman

           
            //mover o braço ate a peça

                pos_0=175;
                pos_1=70;
                pos_2=92;
           
           
            for(x=0;x<=180;x++){


            if(pos_1<=115)
            {
                 
                meus_servos[1].write(pos_1);     // servo 2
                
                     delay(15);
                     pos_1+=1;

                     
                
            }

            if(pos_0>=180)
            {
                 
                meus_servos[0].write(pos_0);     // servo 1
                
                     delay(15);
                     pos_0-=1;
                
            }

            }


            delay(3500);


            //mover o braço com a peça

            //primeira etapa

           
            for(x=0;x<=180;x++){



            if(pos_1>=40)
            {
                 
                meus_servos[1].write(pos_1);     // servo 2
                
                     delay(15);
                     pos_1-=1;
                
            }

            if(pos_0<=175)
            {
                 
                meus_servos[0].write(pos_0);     // servo 1
                
                     delay(15);
                     pos_0+=1;
                
            }        

            }



             delay(3000);


            // segunda etapa


            for(pos_2=pos_2;pos_2>=5;pos_2-=1)
            {
                 
                meus_servos[2].write(pos_2);     // servo 3
                
                     delay(15);
                
            }

             delay(1500);


            // descarregando a peça



            for(x=0;x<=180;x++){
            
            if(pos_0>=150)
            {
                 
                meus_servos[0].write(pos_0);     // servo 1
                
                     delay(15);
                     pos_0-=1;
                
            }



            if(pos_1<=140)
            {
                 
                meus_servos[1].write(pos_1);     // servo 2
                
                     delay(15);
                     pos_1+=1;
                
            }            
           
            }
            

            digitalWrite(iman,HIGH);          // desliga o iman

            delay(3000);


            // segunda etapa

          for(x=0;x<=180;x++){

          if(pos_0<=110)
            {
                 
                meus_servos[0].write(pos_0);     // servo 1
                
                     delay(15);
                     pos_0+=1;
                
            }


            if(pos_1>=70)
            {
                 
                meus_servos[1].write(pos_1);     // servo 2
                
                     delay(15);
                     pos_1-=1;
                
            }



            if(pos_0<=175)
            {
                 
                meus_servos[0].write(pos_0);     // servo 1
                
                     delay(15);
                     pos_0+=1;
                
            }

          }


            delay(2500);


            
            for(pos_2=pos_2;pos_2<=90;pos_2+=1)
            {
                 
                meus_servos[2].write(pos_2);     //servo 3
                
                     delay(15);
                
            }    

            st_carrinho=1;
            status=0;
           
            delay(1000);
            
        }

    }

    









}
// Ex1

void main() {
     DDRB |= (1<<7); //PB7 output
     DDRB &= ~(1<<3);
     while(1){
           if(PINB & (1<<3)) //test pin PB3
              PORTB |= (1<<7); //PB7 set HIGH (LED ON)
           else
              PORTB &= ~(1<<7);
      }
}


// Ex 2

bit starePB2; //it needs only a single bit

void main() {
     DDRB |= (1<<6); //PB7 output
     DDRB &= ~(1<<3);// input

        do {
            if(PINB & (1<<3)) //test pin PB2
              {
                if(starePB2 == 0) //the variable will keep its value
                {
                   starePB2 = 1; //earlier value of PB2
                   PORTB ^= (1<<6);//changes the LED status
                }
              }else
                   starePB2 = 0;
        }while(1);
}


// Ex 3

bit starePB2;
int n;

void main() {

        DDRD |= 0b11111111; //Pini de ie.ire
        DDRB &= ~(1<<2); //PB2 � Intrare

        do {
            if(PINB & (1<<2)) //testare pin PB2
            { 
              if(starePB2 == 0) //variabila va .ine minte starea
                { 
                  starePB2 = 1; //anterioara a pin-ului PB2
                  n++; //se incrementeaza variabila n
                }
            }
            else
                 starePB2 = 0;

            PORTD = n;
        }while(1);

}

// Ex 1

void ex1() {
    // Set the lower 4 bits of port A as output and all bits of port C as output
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;

    do {
        // Display digit 1 on 7-segment display
        PORTA = 0b00001000;
        PORTC = 0b00111111;
        Delay_ms(4);

        // Display digit 2 on 7-segment display
        PORTA = 0b00000100;
        PORTC = 0b00000110;
        Delay_ms(4);

        // Display digit 3 on 7-segment display
        PORTA = 0b00000010;
        PORTC = ~0b10100100;
        Delay_ms(4);

        // Display digit 4 on 7-segment display
        PORTA = 0b00000001;
        PORTC = ~0b10110000;
        Delay_ms(4);
    } while(1);
}

// Ex 2

// Variable declaration
int value=0;

// Function to display a digit on a 4-digit 7-segment display
void display(char p, char c)
{
    PORTA &= 0b11110000;
    PORTC &= 0b00000000;

    switch(c){
        // ... (code for 7-segment display control)
    }
    switch(p){
        // ... (code for 7-segment display control)
    }
    Delay_ms(4);
}

// Function to display a 4-digit number
void ex2(int value){
    display(1,value%10);
    display(2,(value/10)%10);
    display(3,(value/100)%10);
    display(4,(value/1000)%10);
}

void ex2_main() {
    // Set the lower 4 bits of port A as output and all bits of port C as output
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;

    // Set an initial value
    value = 2023;

    while(1) {
        // Continuously display the 4-digit value
        ex2(value);
    }
}

// Ex 3

// Variable declaration
bit starePB2;
int value=0;

// Function to display a digit on a 4-digit 7-segment display
void display(char p, char c)
{
    PORTA &= 0b11110000;
    PORTC &= 0b00000000;

    switch(c){
        // ... (code for 7-segment display control)
    }
    switch(p){
        // ... (code for 7-segment display control)
    }
    Delay_ms(4);
}

// Function to display a 4-digit number
void ex3(int value){
    display(1,value%10);
    display(2,(value/10)%10);
    display(3,(value/100)%10);
    display(4,(value/1000)%10);
}

// Function to handle button logic for incrementing the value
int button_2_logic(int value){
    if(PINB & (1<<2)) // Check pin PB2
    { 
        if(starePB2 == 0) // Remember the previous state of pin PB2
        { 
            starePB2 = 1; // Set the previous state of pin PB2
            value++;
        }
    }
    else
        starePB2 = 0;
    
    return value;
}

void ex3_main() {
    // Set the lower 4 bits of port A as output, all bits of port C as output, and pin PB2 as input
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;
    DDRB &= ~(1<<2);

    // Set an initial value
    value = 2023;

    while(1) {
        // Handle button logic and continuously display the 4-digit value
        value = button_2_logic(value);
        ex3(value);
    }
}

// Main program
void main() {
    // Call the desired example function here
    ex3_main();
}

// Ex 1
int s=0, ms=0, m=0;

void display(char p, char c)
{
    // Clear display selection and segment lines
    PORTA &= 0b11110000;
    PORTC &= 0b00000000;

    // Display the corresponding digit on the 7-segment display
    switch(c){
        case 0: PORTC |= 0b00111111; break; // Digit 0
        case 1: PORTC |= 0b00000110; break; // Digit 1
        case 2: PORTC |= 0b01011011; break; // Digit 2
        case 3: PORTC |= 0b01001111; break; // Digit 3
        case 4: PORTC |= 0b01100110; break; // Digit 4
        case 5: PORTC |= 0b01101101; break; // Digit 5
        case 6: PORTC |= 0b01111101; break; // Digit 6
        case 7: PORTC |= 0b00000111; break; // Digit 7
        case 8: PORTC |= 0b01111111; break; // Digit 8
        case 9: PORTC |= 0b01100111; break; // Digit 9
        case 10: PORTC |= 0b10000000; break; // Decimal Point
    }

    // Select the digit
    switch(p){
        //selects display segment
        case 1: PORTA |= 0b00000001; break; //segment 1 
        case 2: PORTA |= 0b00000010; break; //segment 2
        case 3: PORTA |= 0b00000100; break; //segment 3
        case 4: PORTA |= 0b00001000; break; //segment 4
    }
}

void init_timer()
{
    // Initialize Timer0 with a prescaler of 64 and normal mode
    TCCR0 = 0b00000011;
    TCNT0 = 0; // Initialize the counter to 0
}

void lcd_display()
{
    // Display seconds and minutes on the 7-segment display
    display(4, s % 10);
    display(3, (s / 10) % 10);
    display(2, m % 10);
    PORTC |= 0b10000000; // activates MSB of Port C -> decimal point
    display(1, (m / 10) % 10);
}

void timer_one()
{
    // Increment milliseconds, seconds, and minutes based on Timer0
    if(TCNT0 >= 125) // When a millisecond is completed
    {
        TCNT0 = 0; // Reset the timer
        ms++;
        if(ms == 1000) // When a second is completed
        {
            ms = 0; //ms back to 0
            s++; //seconds ++
        }
        if(s == 60) // When a minute is completed
        {
            s = 0; //seconds back to 0
            m++;   //minutes ++
        }
    }
}
//fuckyou <3
void main() {
    // Set PA0-PA3 as outputs and PC0-PC7 as outputs
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;

    // Initialize Timer0
    init_timer();

    // Main loop
    do {
        timer_one();
        lcd_display();
    } while(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex 2
// Only the TCCR register is changed:
// TCCR2 = 0b00000100;
// and the name of the other register: from 0 to 2 -> TCNT2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex 3

bit starePB2, starePB3, freeze_time, reset;
int n, s=0, ms=0, m=0;

void buttons()
{
    // Check if PB2 is pressed to toggle freeze_time
    if(PINB & (1<<2))
    {
        if(starePB2 == 0)
        {
            starePB2 = 1;
            freeze_time ^= 1;
        }
    }
    else
        starePB2 = 0;

    // Check if PB3 is pressed to reset the timer
    if(PINB & (1<<3))
    {
        if(starePB3 == 0)
        {
            starePB3 = 1;
            TCNT0 = 0;
            s = 0;
            ms = 0;
            m = 0;
        }
    }
    else
        starePB3 = 0;
}

void display(char p, char c)
{
    // Clear display selection and segment lines
    PORTA &= 0b11110000;
    PORTC &= 0b00000000;

    // Display the corresponding digit on the 7-segment display
    switch(c){
        case 0: PORTC |= 0b00111111; break; // Digit 0
        case 1: PORTC |= 0b00000110; break;
        case 2: PORTC |= 0b01011011; break;
        case 3: PORTC |= 0b01001111; break;
        case 4: PORTC |= 0b01100110; break;
        case 5: PORTC |= 0b01101101; break;
        case 6: PORTC |= 0b01111101; break;
        case 7: PORTC |= 0b00000111; break;
        case 8: PORTC |= 0b01111111; break;
        case 9: PORTC |= 0b01100111; break;
    }

    // Select the digit
    switch(p){
        case 1: PORTA |= 0b00000001; break;
        case 2: PORTA |= 0b00000010; break;
        case 3: PORTA |= 0b00000100; break;
        case 4: PORTA |= 0b00001000; break;
    }
}

void init_timer()
{
    // Initialize Timer2 with a prescaler of 64 and normal mode
    TCCR2 = 0b00000100;
    TCNT2 = 0; // Initialize the counter to 0
}

void lcd_display()
{
    // Display milliseconds and seconds on the 7-segment display
    display(4, (ms / 10) % 10);
    display(3, (ms / 100) % 10);
    display(2, s % 10);
    PORTC |= 0b10000000;
    display(1, (s / 10) % 10);
}

void timer_one()
{
    // Increment milliseconds, seconds, and minutes based on Timer2
    if(TCNT2 >= 125) // When a millisecond is completed
    {
        TCNT2 = 0; // Reset the timer
        ms++;
        if(ms == 1000) // When a second is completed
        {
            ms = 0;
            s++;
        }
        if(s == 60) // When a minute is completed
        {
            s = 0;
            m++;
        }
    }
}

void main() {
    // Set PA0-PA3 as outputs and PC0-PC7 as outputs
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;

    // Initialize Timer2
    init_timer();

    // Main loop
    do {
        buttons();
        if (freeze_time == 0) //continuously display the output of the timer one
                                // on the display
        {
            timer_one();
        }
        lcd_display(); //display function
    } while(1);
}

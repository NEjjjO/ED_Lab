// Initialization of variables for digit and time units (seconds, milliseconds, minutes)
int digit = 0;
int s = 0, ms = 0, m = 0;

// Function to display a digit on a 7-segment display
void display(char p, char c)
{
    // Turn off digit and segment lines
    PORTA &= 0b11110000; // Disable digit selection lines
    PORTC &= 0b00000000; // Disable segment lines

    // Switch-case for encoding each digit on the 7-segment display
    switch (c)
    {
    case 0: PORTC |= 0b00111111; break; // Display digit 0
    case 1: PORTC |= 0b00000110; break; // Display digit 1
    case 2: PORTC |= 0b01011011; break; // Display digit 2
    case 3: PORTC |= 0b01001111; break; // Display digit 3
    case 4: PORTC |= 0b01100110; break; // Display digit 4
    case 5: PORTC |= 0b01101101; break; // Display digit 5
    case 6: PORTC |= 0b01111101; break; // Display digit 6
    case 7: PORTC |= 0b00000111; break; // Display digit 7
    case 8: PORTC |= 0b01111111; break; // Display digit 8
    case 9: PORTC |= 0b01100111; break; // Display digit 9
    }

    // Switch-case for selecting the digit on the display
    switch (p)
    {
    case 1: PORTA |= 0b00000001; break; // Select digit 1
    case 2: PORTA |= 0b00000010; break; // Select digit 2
    case 3: PORTA |= 0b00000100; break; // Select digit 3
    case 4: PORTA |= 0b00001000; break; // Select digit 4
    }
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    SREG = 1 << 7;      // Enable global interrupts
    TCCR0 = 0b00001011; // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;          // Initialize timer counter
    OCR0 = 125;         // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Timer0 Interrupt Service Routine
void Timer0_OC_ISR() iv IVT_ADDR_TIMER0_COMP
{
    digit++; // Increment digit counter

    // Switch-case for displaying different digits on the 7-segment display
    switch (digit)
    {
    case 1: display(1, s % 10); break;             // Display units of seconds
    case 2: display(2, (s / 10) % 10); break;      // Display tens of seconds
    case 3: display(3, m % 10);
            PORTC |= 0b10000000; // Turn on a decimal point
            break;                    // Display units of minutes
    case 4: display(4, (m / 10) % 10); digit = 0; break; // Display tens of minutes
    }

    if (ms == 999)
    {
        s++; // Increment seconds
        ms = 0; // Reset milliseconds

        if (s == 60)
        {
            s = 0; // Reset seconds
            m++;   // Increment minutes
        }
    }
    else
        ms++; // Increment milliseconds
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer0
    s = 0;             // Initialize seconds
    ms = 0;            // Initialize milliseconds
    m = 0;             // Initialize minutes
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Exercise 2

// Initialization of variables for digit and time units (seconds, milliseconds, minutes)
int digit = 0;
int s = 0, ms = 0, m = 0;

// Function to display a digit on a 7-segment display
void display(char p, char c)
{
    // Turn off digit and segment lines
    PORTA &= 0b11110000; // Disable digit selection lines
    PORTC &= 0b00000000; // Disable segment lines

    // Switch-case for encoding each digit on the 7-segment display
    switch (c)
    {
    case 0: PORTC |= 0b00111111; break; // Display digit 0
    case 1: PORTC |= 0b00000110; break; // Display digit 1
    case 2: PORTC |= 0b01011011; break; // Display digit 2
    case 3: PORTC |= 0b01001111; break; // Display digit 3
    case 4: PORTC |= 0b01100110; break; // Display digit 4
    case 5: PORTC |= 0b01101101; break; // Display digit 5
    case 6: PORTC |= 0b01111101; break; // Display digit 6
    case 7: PORTC |= 0b00000111; break; // Display digit 7
    case 8: PORTC |= 0b01111111; break; // Display digit 8
    case 9: PORTC |= 0b01100111; break; // Display digit 9
    }

    // Switch-case for selecting the digit on the display
    switch (p)
    {
    case 1: PORTA |= 0b00000001; break; // Select digit 1
    case 2: PORTA |= 0b00000010; break; // Select digit 2
    case 3: PORTA |= 0b00000100; break; // Select digit 3
    case 4: PORTA |= 0b00001000; break; // Select digit 4
    }
}

// Function to initialize Timer2 for timekeeping
void init_timer()
{
    SREG = 1 << 7;      // Enable global interrupts
    TCCR2 = 0b00001011; // Set Timer2 in CTC mode; Set prescaler to 64
    TCNT2 = 0;          // Initialize timer counter
    OCR2 = 250;         // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b10000000; // Enable Timer2 Compare Match Interrupt
}

// Timer2 Interrupt Service Routine
void Timer2_OC_ISR() iv IVT_ADDR_TIMER2_COMP
{
    digit++; // Increment digit counter

    // Switch-case for displaying different digits on the 7-segment display
    switch (digit)
    {
    case 1: display(1, s % 10); break;             // Display units of seconds
    case 2: display(2, (s / 10) % 10); break;      // Display tens of seconds
    case 3: display(3, m % 10);
            PORTC |= 0b10000000; // Turn on a decimal point
            break;                    // Display units of minutes
    case 4: display(4, (m / 10) % 10); digit = 0; break; // Display tens of minutes
    }

    if (ms == 999)
    {
        s++; // Increment seconds
        ms = 0; // Reset milliseconds

        if (s == 60)
        {
            s = 0; // Reset seconds
            m++;   // Increment minutes
        }
    }
    else
        ms++; // Increment milliseconds
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer2
    s = 0;             // Initialize seconds
    ms = 0;            // Initialize milliseconds
    m = 0;             // Initialize minutes
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Exercise 3/4

// Initialization of variables for digit and time units (seconds, milliseconds, minutes)
int digit = 0;
int s = 0, ms = 0, m = 0;

// Function to display a digit on a 7-segment display
void display(char p, char c)
{
    // Turn off digit and segment lines
    PORTA &= 0b11110000; // Disable digit selection lines
    PORTC &= 0b00000000; // Disable segment lines

    // Switch-case for encoding each digit on the 7-segment display
    switch (c)
    {
    case 0: PORTC |= 0b00111111; break; // Display digit 0
    case 1: PORTC |= 0b00000110; break; // Display digit 1
    case 2: PORTC |= 0b01011011; break; // Display digit 2
    case 3: PORTC |= 0b01001111; break; // Display digit 3
    case 4: PORTC |= 0b01100110; break; // Display digit 4
    case 5: PORTC |= 0b01101101; break; // Display digit 5
    case 6: PORTC |= 0b01111101; break; // Display digit 6
    case 7: PORTC |= 0b00000111; break; // Display digit 7
    case 8: PORTC |= 0b01111111; break; // Display digit 8
    case 9: PORTC |= 0b01100111; break; // Display digit 9
    }

    // Switch-case for selecting the digit on the display
    switch (p)
    {
    case 1: PORTA |= 0b00000001; break; // Select digit 1
    case 2: PORTA |= 0b00000010; break; // Select digit 2
    case 3: PORTA |= 0b00000100; break; // Select digit 3
    case 4: PORTA |= 0b00001000; break; // Select digit 4
    }
}

// Function to initialize Timer2 for timekeeping
void init_timer()
{
    SREG = 1 << 7;      // Enable global interrupts
    TCCR2 = 0b00001011; // Set Timer2 in CTC mode; Set prescaler to 64
    TCNT2 = 0;          // Initialize timer counter
    OCR2 = 250;         // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b10000000; // Enable Timer2 Compare Match Interrupt
}

// Function to initialize external interrupts INT0 and INT1
void init_INT0_INT1()
{
    GICR |= (1 << 7); // Enable external interrupt INT0
    GICR |= (1 << 6); // Enable external interrupt INT1

    // Configure external interrupts to trigger on rising edge
    MCUCR |= 0b00001111; // Set INT0 and INT1 to trigger on rising edge
}

// Interrupt Service Routine for INT0
void nume_functie1() iv IVT_ADDR_INT0
{
    s++; // Increment seconds
}

// Interrupt Service Routine for INT1
void INTRERUPERE() iv IVT_ADDR_INT1 ics ICS_AUTO
{
    m++; // Increment minutes
}

// Timer2 Interrupt Service Routine
void Timer2_OC_ISR() iv IVT_ADDR_TIMER2_COMP
{
    digit++; // Increment digit counter

    // Switch-case for displaying different digits on the 7-segment display
    switch (digit)
    {
    case 1: display(1, s % 10); break;             // Display units of seconds
    case 2: display(2, (s / 10) % 10); break;      // Display tens of seconds
    case 3: display(3, m % 10);
            PORTC |= 0b10000000; // Turn on a decimal point
            break;                    // Display units of minutes
    case 4: display(4, (m / 10) % 10); digit = 0; break; // Display tens of minutes
    }

    if (ms == 999)
    {
        s++; // Increment seconds
        ms = 0; // Reset milliseconds

        if (s == 60)
        {
            s = 0; // Reset seconds
            m++;   // Increment minutes
        }
    }
    else
        ms++; // Increment milliseconds
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer2
    init_INT0_INT1();  // Initialize external interrupts INT0 and INT1
    s = 0;             // Initialize seconds
    ms = 0;            // Initialize milliseconds
    m = 0;             // Initialize minutes
}

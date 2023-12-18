// PWM Duty Cycle

// Variables for milliseconds, low byte, high byte, display position, and ADC value
int ms = 0, l, h, poz = 0, value;

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
    case 2: PORTC |= ~0b10100100; break; // Display digit 2
    case 3: PORTC |= ~0b10110000; break; // Display digit 3
    case 4: PORTC |= ~0b10011001; break; // Display digit 4
    case 5: PORTC |= ~0b10010010; break; // Display digit 5
    case 6: PORTC |= ~0b10000010; break; // Display digit 6
    case 7: PORTC |= ~0b11111000; break; // Display digit 7
    case 8: PORTC |= ~0b10000000; break; // Display digit 8
    case 9: PORTC |= ~0b10010000; break; // Display digit 9
    }

    // Switch-case for selecting the digit on the display
    switch (p)
    {
    case 1: PORTA |= 0b00000001; break; // Select digit 1
    case 2: PORTA |= 0b00000010; break; // Select digit 2
    case 3: PORTA |= 0b00000100; break; // Select digit 3
    case 4: PORTA |= 0b00001000; break; // Select digit 4
    }

    // Delay_ms(1); // Uncomment if using delay function
}

// Function to initialize ADC
void init_adc()
{
    ADMUX = 0b01000000; // Reference - AVCC
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128
}

// Function to read ADC value for a given channel
int adc(char ch)
{
    ADMUX &= 0b11100000; // Reset previous channel selection
    ADMUX |= ch;         // Set ADC channel
    ADCSRA |= 1 << 6;    // Start ADC conversion
    while (ADCSRA & (1 << 6))
        ; // Wait for conversion to complete
    l = ADCL;
    h = ADCH;
    return h << 8 | l; // Return the result of the conversion
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    TCCR0 = 0b00001011; // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;          // Initialize timer counter
    OCR0 = 125;         // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Function to initialize PWM
void init_PWM()
{
    TCCR2 = 0b01101001; // Configure Timer2 for fast PWM mode
    OCR2 = 128;         // Set initial duty cycle to 50%
}

// Timer0 Interrupt Service Routine
void ISR_Timer0() iv IVT_ADDR_TIMER0_COMP ics ICS_AUTO
{
    poz++; // Increment display position

    switch (poz)
    {
    case 1: display(1, value % 10); break; // Display units
    case 2: display(2, (value / 10) % 10); break; // Display tens
    case 3: display(3, (value / 100) % 10); break; // Display hundreds
    case 4: display(4, (value / 1000) % 10); poz = 0; break; // Display thousands
    }

    if (ms == 100)
    {
        value = adc(6) / 4; // Read ADC value and scale for PWM duty cycle
        OCR2 = value;       // Update PWM duty cycle
        ms = 0;             // Reset milliseconds counter
    }
    else
        ms++; // Increment milliseconds counter
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b01111111; // Set all PORTC pins as outputs
    DDRD |= 1 << 7;    // Set PD7 as output for PWM
    init_adc();        // Initialize ADC
    init_timer();      // Initialize Timer0
    init_PWM();        // Initialize PWM
    SREG |= 1 << 7;    // Enable global interrupts
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Buzzer

// Variables for note, ADC value, milliseconds, advance, low byte, high byte, display position, and frequency-related parameters
int n, adv, l, h, ms = 0, poz = 0, value;
int ADCMax = 1023, fMax = 20000, fMin = 20, freq, TOP;

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
    case 2: PORTC |= ~0b10100100; break; // Display digit 2
    case 3: PORTC |= ~0b10110000; break; // Display digit 3
    case 4: PORTC |= ~0b10011001; break; // Display digit 4
    case 5: PORTC |= ~0b10010010; break; // Display digit 5
    case 6: PORTC |= ~0b10000010; break; // Display digit 6
    case 7: PORTC |= ~0b11111000; break; // Display digit 7
    case 8: PORTC |= ~0b10000000; break; // Display digit 8
    case 9: PORTC |= ~0b10010000; break; // Display digit 9
    }

    // Switch-case for selecting the digit on the display
    switch (p)
    {
    case 1: PORTA |= 0b00000001; break; // Select digit 1
    case 2: PORTA |= 0b00000010; break; // Select digit 2
    case 3: PORTA |= 0b00000100; break; // Select digit 3
    case 4: PORTA |= 0b00001000; break; // Select digit 4
    }

    // Delay_ms(1); // Uncomment if using delay function
}

// Function to initialize ADC
void init_adc()
{
    ADMUX = 0b01000000; // Reference - AVCC
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128
}

// Function to read ADC value for a given channel
int adc(char ch)
{
    ADMUX &= 0b11100000; // Reset previous channel selection
    ADMUX |= ch;         // Set ADC channel
    ADCSRA |= 1 << 6;    // Start ADC conversion
    while (ADCSRA & (1 << 6))
        ; // Wait for conversion to complete
    l = ADCL;
    h = ADCH;
    return h << 8 | l; // Return the result of the conversion
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    TCCR0 = 0b00001011; // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;          // Initialize timer counter
    OCR0 = 125;         // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Timer0 Interrupt Service Routine
void ISR_Timer0() iv IVT_ADDR_TIMER0_COMP ics ICS_AUTO
{
    poz++; // Increment display position

    switch (poz)
    {
    case 1: display(1, value % 10); break; // Display units
    case 2: display(2, (value / 10) % 10); break; // Display tens
    case 3: display(3, (value / 100) % 10); break; // Display hundreds
    case 4: display(4, (value / 1000) % 10); poz = 0; break; // Display thousands
    }

    if (ms == 10)
    {
        adv = adc(6);
        freq = ((float)(fMax - fMin)) / ADCMax * adv + fMin;
        TOP = 1000000 / freq - 1;
        ICR1H = TOP >> 8;
        ICR1L = TOP;
        value = freq / 10;
        ms = 0;
    }
    else
        ms++; // Increment milliseconds counter
}

// Function to initialize Buzzer
void init_Buzzer()
{
    TCCR1A = 0b00100010; // Configure Timer1 for fast PWM mode
    TCCR1B = 0b00011010; // Set prescaler to 8
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b01111111; // Set all PORTC pins as outputs
    DDRD |= 1 << 4;    // Set PD4 as output for Buzzer
    init_adc();        // Initialize ADC
    init_timer();      // Initialize Timer0
    init_Buzzer();     // Initialize Buzzer
    SREG |= 1 << 7;    // Enable global interrupts
}

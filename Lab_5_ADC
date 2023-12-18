// Exercise 1

// Variables for milliseconds, display position, and ADC value
int ms = 0, poz = 0, value = 0;
char adc_low = 0, adc_high = 0;

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
    case 1: PORTA |= 0b00001000; break; // Select digit 1
    case 2: PORTA |= 0b00000100; break; // Select digit 2
    case 3: PORTA |= 0b00000010; break; // Select digit 3
    case 4: PORTA |= 0b00000001; break; // Select digit 4
    }
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    SREG |= 1 << 7;      // Enable global interrupts
    TCCR0 = 0b00001011;  // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;           // Initialize timer counter
    OCR0 = 125;          // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Function to initialize ADC
void Init_adc()
{
    ADMUX = 0b01000000;  // Reference - AVCC
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128
}

// Function to read ADC value for a given channel
int readADC(char ch)
{
    ADMUX &= 0b11100000; // Clear previous channel selection
    ADMUX |= ch;         // Select ADC channel
    ADCSRA |= 1 << 6;    // Start ADC conversion
    while (ADCSRA & (1 << 6))
        ; // Wait for conversion to complete
    adc_low = ADCL;            // Read lower byte of ADC result
    adc_high = ADCH;           // Read higher byte of ADC result
    return ((adc_high << 8) | adc_low); // Combine high and low bytes
}

// Timer0 Interrupt Service Routine
void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP
{
    poz++; // Increment display position

    switch (poz)
    {
    case 1: display(1, value % 10); break;          // Display units
    case 2: display(2, (value / 10) % 10); break;   // Display tens
    case 3: display(3, (value / 100) % 10); break;  // Display hundreds
    case 4: display(4, (value / 1000) % 10); poz = 0; break; // Display thousands
    }

    if (ms == 999)
    {
        value = readADC(6); // Read ADC value from channel 6
        ms = 0;             // Reset milliseconds counter
    }
    else
        ms++; // Increment milliseconds counter
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer0
    Init_adc();        // Initialize ADC
    ms = 0;            // Reset milliseconds counter
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Exercise 2

// Variables for milliseconds, display position, ADC value, and temperature variables
int ms = 0, poz = 0, value = 0;
char adc_low = 0, adc_high = 0;
int adc, T = 0;
float Vin, tmp;

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
    case 1: PORTA |= 0b00001000; break; // Select digit 1
    case 2: PORTA |= 0b00000100; break; // Select digit 2
    case 3: PORTA |= 0b00000010; break; // Select digit 3
    case 4: PORTA |= 0b00000001; break; // Select digit 4
    }
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    SREG |= 1 << 7;      // Enable global interrupts
    TCCR0 = 0b00001011;  // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;           // Initialize timer counter
    OCR0 = 125;          // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Function to initialize ADC
void Init_adc()
{
    ADMUX = 0b01000000;  // Reference - AVCC
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128
    ADCSRA |= (1 << 3);  // Enable ADC interrupt
}

// Function to trigger ADC conversion for a given channel
void readADC_interrupt(char ch)
{
    ADMUX &= 0b11100000; // Reset previous channel selection
    ADMUX |= ch;         // Set ADC channel
    ADCSRA |= (1 << 6);  // Start ADC conversion
}

// ADC Complete Interrupt Service Routine
void ADC_Completed() iv IVT_ADDR_ADC
{
    adc_low = ADCL;
    adc_high = ADCH;
    adc = (adc_high << 8) | adc_low;
    Vin = ((float)adc * 5) / 1024;
    tmp = Vin * 1000 / 10;
    T = (int)tmp;
}

// Timer0 Interrupt Service Routine
void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP
{
    poz++; // Increment display position

    switch (poz)
    {
    case 1: display(1, value % 10); break;           // Display units
    case 2: display(2, (value / 10) % 10); break;    // Display tens
    case 3: display(3, (value / 100) % 10); break;   // Display hundreds
    case 4: display(4, (value / 1000) % 10); poz = 0; break; // Display thousands
    }

    if (ms == 999)
    {
        readADC_interrupt(7); // Trigger ADC conversion on channel 7
        value = T;            // Update value with temperature
        ms = 0;               // Reset milliseconds counter
    }
    else
        ms++; // Increment milliseconds counter
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer0
    Init_adc();        // Initialize ADC
    ms = 0;            // Reset milliseconds counter
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Exercise 3 & Extra

// Variables for milliseconds, seconds, display position, ADC value, test value, and selection mode
int ms = 0, s = 0, poz = 0, value = 0, test = 0;
char adclow = 0, adchigh = 0;

int adc, T = 0;
float Vin, tmp;

int selection = 0; // 0 for potentiometer, 1 for temperature sensor

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
    case 1: PORTA |= 0b00001000; break; // Select digit 1
    case 2: PORTA |= 0b00000100; break; // Select digit 2
    case 3: PORTA |= 0b00000010; break; // Select digit 3
    case 4: PORTA |= 0b00000001; break; // Select digit 4
    }
}

// Function to initialize Timer0 for timekeeping
void init_timer()
{
    SREG |= 1 << 7;      // Enable global interrupts
    TCCR0 = 0b00001011;  // Set Timer0 in CTC mode; Set prescaler to 64
    TCNT0 = 0;           // Initialize timer counter
    OCR0 = 125;          // Set Output Compare Register for 1 ms interrupt
    TIMSK |= 0b00000010; // Enable Timer0 Compare Match Interrupt
}

// Function to initialize ADC
void init_adc()
{
    ADMUX = 0b01000000;  // Reference - AVCC
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128
}

// Function to read ADC value for a given channel
int readADC(char ch)
{
    ADMUX &= 0b11100000; // Reset previous channel selection
    ADMUX |= ch;         // Set ADC channel
    ADCSRA |= 1 << 6;    // Start ADC conversion
    while (ADCSRA & (1 << 6))
        ; // Wait for conversion to complete
    adclow = ADCL;
    adchigh = ADCH;
    return adchigh << 8 | adclow; // Return the result of the conversion
}

// Function to trigger ADC conversion for a given channel in interrupt mode
void readADC_interrupt(char ch)
{
    ADMUX &= 0b11100000; // Reset channel selection
    ADMUX |= ch;         // Set ADC channel
    ADCSRA |= (1 << 6);  // Start ADC conversion
}

// ADC Complete Interrupt Service Routine
void ADC_Completed() iv IVT_ADDR_ADC
{
    adclow = ADCL;
    adchigh = ADCH;
    adc = (adchigh << 8) | adclow;
    Vin = ((float)adc * 5) / 1024;
    tmp = Vin * 1000;
    T = (int)tmp;
}

// Timer0 Interrupt Service Routine
void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP
{
    poz++; // Increment display position

    switch (poz)
    {
    case 1: display(1, value % 10); break; // Display units
    case 2:
        display(2, (value / 10) % 10);
        if (selection == 0)
            PORTC |= 0b10000000; // Display dot for potentiometer
        break;
    case 3: display(3, (value / 100) % 10); break; // Display hundreds
    case 4: display(4, (value / 1000) % 10); poz = 0; break; // Display thousands
    }

    if (ms == 100)
    {
        if (selection)
            value = readADC(6); // Read potentiometer value
        else
        {
            readADC_interrupt(7); // Trigger ADC conversion on channel 7
            value = T;            // Update value with temperature
        }
        ms = 0; // Reset milliseconds counter
    }
    else
        ms++; // Increment milliseconds counter
}

// External Interrupt Service Routine for switching between potentiometer and temperature sensor
void switch_int() iv IVT_ADDR_INT0
{
    init_adc();           // Initialize ADC with default settings
    ADCSRA ^= (1 << 3);    // Toggle ADIE (ADC interrupt enable) bit
    selection ^= 1;       // Toggle selection between potentiometer and temperature sensor
}

// Function to initialize external interrupt settings
void init_external_int()
{
    GICR |= 0b01000000;  // Enable INT0 interrupt
    MCUCR |= 0b00000010; // Set INT0 to trigger on the rising edge
}

// Main function
void main()
{
    DDRA = 0b00001111; // Set output pins for 7-segment display
    DDRC = 0b11111111; // Set all PORTC pins as outputs
    init_timer();      // Initialize Timer0
    init_external_int(); // Initialize external interrupt settings
    init_adc();        // Initialize ADC
    selection = 1;     // Start with temperature sensor selection
    s = 0;             // Reset seconds counter
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Structure representing an IDT entry
typedef struct {
    uint16_t offsetLow;     // Lower 16 bits of ISR address
    uint16_t selector;      // Code segment selector
    uint8_t zero;           // Always set to 0
    uint8_t typeAttr;       // Type and attributes
    uint16_t offsetHigh;    // Higher 16 bits of ISR address
} __attribute__((packed)) IDTEntry;

// IDT entry count
#define IDT_ENTRY_COUNT 256

// IDT table
IDTEntry idt[IDT_ENTRY_COUNT];

// Function to set up an IDT entry
void setIDTEntry(uint8_t index, uint32_t isrAddress, uint16_t selector, uint8_t typeAttr) {
    idt[index].offsetLow = isrAddress & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].typeAttr = typeAttr;
    idt[index].offsetHigh = (isrAddress >> 16) & 0xFFFF;
}

// Dummy flag variable indicating data availability
bool dataAvailable = true;

// Function to check if data is available in the network device or buffer
bool isDataAvailable() {
    // Check the dataAvailable flag variable to determine if data is available
    return dataAvailable;
}

// Keyboard ISR
void keyboardISR();

// Network ISR
void networkISR();

// Function to read the scan code from the keyboard controller or input buffer
uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Function to read the scan code from the keyboard controller or input buffer
uint8_t readKeyboardScanCode() {
    // Read the scan code from the keyboard controller's data port (usually port 0x60)
    uint8_t scanCode = inb(0x60);
    return scanCode;
}

// Function to write a byte to a port
void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Function to send End of Interrupt (EOI) signal to the PIC
void sendEOIToPIC() {
    // Send the EOI signal to the PIC's command port (usually port 0x20 for master PIC)
    outb(0x20, 0x20);
}


// Function to receive the data from the network device or buffer
uint8_t* receiveData() {
    // Implement the actual code to receive the data from the network device or buffer
    // For simplicity, let's assume a dummy data buffer with the size of 10 bytes
    uint8_t* data = malloc(10 * sizeof(uint8_t));
    // Populate the data buffer with some dummy values
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    return data;
}

// Function to release the received data buffer or perform necessary cleanup
void releaseDataBuffer(uint8_t* data) {
    // Implement the actual code to release the received data buffer or perform necessary cleanup
    // For simplicity, we free the allocated memory
    free(data);
}

// Keyboard ISR
void keyboardISR() {
    // Read the scan code from the keyboard controller or input buffer
    uint8_t scanCode = readKeyboardScanCode();

    // Process the scan code
    printf("Scan code received: 0x%X\n", scanCode);

    // Send End of Interrupt (EOI) signal to the PIC
    sendEOIToPIC();
}

// Network ISR
void networkISR() {
    // Check if data is available in the network device or buffer
    if (isDataAvailable()) {
        // Receive the data from the network device or buffer
        uint8_t* data = receiveData();

        // Process the received data
        printf("Received data: ");
        for (int i = 0; i < 10; i++) {
            printf("%X ", data[i]);
        }
        printf("\n");

        // Release the received data buffer or perform necessary cleanup
        releaseDataBuffer(data);
    }

    // Send End of Interrupt (EOI) signal to the PIC
    sendEOIToPIC();
}


// Function to initialize the IDT
void initIDT() {
    // Clear the IDT
    memset(idt, 0, sizeof(IDTEntry) * IDT_ENTRY_COUNT);

    // Set up IDT entries for Keyboard ISR and Network ISR
    setIDTEntry(0x21, (uint32_t)&keyboardISR, 0x08, 0x8E);     // Keyboard ISR at index 0x21
    setIDTEntry(0x2E, (uint32_t)&networkISR, 0x08, 0x8E);      // Network ISR at index 0x2E

    // Load the IDT
    loadIDT();
}

// Function to load the IDT
void loadIDT() {
    // Structure representing the IDT pointer
    typedef struct {
        uint16_t limit;     // Size of IDT
        uint32_t base;      // Base address of IDT
    } __attribute__((packed)) IDTPointer;

    // Set up the IDT pointer
    IDTPointer idtPtr;
    idtPtr.limit = sizeof(IDTEntry) * IDT_ENTRY_COUNT - 1;
    idtPtr.base = (uint32_t)&idt;

    // Load the IDT pointer
    asm volatile("lidt %0" : : "m"(idtPtr));
}

// Enable interrupts
void enableInterrupts() {
    asm volatile("sti");
}

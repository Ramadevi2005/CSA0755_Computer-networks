#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Function to perform bit stuffing
void bitStuffing(uint8_t *input, size_t inputLength, uint8_t *output, size_t *outputLength) {
    size_t outputIndex = 0;
    size_t bitCount = 0;
    uint8_t flagSequence[1] = {0x7E}; // Flag sequence (01111110)

    // Start with flag sequence
    output[outputIndex++] = flagSequence[0];

    // Process each byte of input data
    for (size_t i = 0; i < inputLength; i++) {
        uint8_t currentByte = input[i];
        for (int j = 7; j >= 0; j--) {
            if ((currentByte >> j) & 1) {
                bitCount++;
                if (bitCount == 5) {
                    // Stuff a 0 bit after five consecutive 1s
                    output[outputIndex++] = 0;
                    bitCount = 0;
                }
            } else {
                bitCount = 0;
            }
            output[outputIndex++] = (currentByte >> j) & 1;
        }
    }

    // End with flag sequence
    output[outputIndex++] = flagSequence[0];

    *outputLength = outputIndex;
}

void printHex(uint8_t *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    // Example input frame (in hexadecimal format)
    uint8_t inputFrame[] = {0xFF, 0x00, 0xAA}; // Example input data
    size_t inputLength = sizeof(inputFrame) / sizeof(inputFrame[0]);

    // Prepare output frame
    uint8_t outputFrame[1024];
    size_t outputLength = 0;

    // Perform bit stuffing
    bitStuffing(inputFrame, inputLength, outputFrame, &outputLength);

    // Print input and output frames in hexadecimal format
    printf("Input Frame:\n");
    printHex(inputFrame, inputLength);

    printf("Output Frame:\n");
    printHex(outputFrame, outputLength);

    return 0;
}


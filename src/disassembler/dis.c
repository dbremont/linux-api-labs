#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Instruction structure
typedef struct {
    uint8_t opcode;
    const char *mnemonic;
} Instruction;

// Basic x86-64 instruction lookup table
Instruction instructions[] = {
    {0x48, "REX.W"},    // REX prefix for 64-bit instructions
    {0x89, "MOV"},      // MOV r/m64, r64
    {0x8B, "MOV"},      // MOV r64, r/m64
    {0x01, "ADD"},      // ADD r/m64, r64
    {0x29, "SUB"},      // SUB r/m64, r64
    {0xC3, "RET"},      // RET
    {0xCD, "INT"},      // INT (software interrupt)
    {0xB8, "MOV EAX, imm32"}, // MOV EAX, immediate
    {0x00, NULL}        // End of table
};

// Function to find instruction mnemonic
const char *decode_opcode(uint8_t opcode) {
    for (int i = 0; instructions[i].mnemonic != NULL; i++) {
        if (instructions[i].opcode == opcode) {
            return instructions[i].mnemonic;
        }
    }
    return "UNKNOWN"; // If instruction is not recognized
}

// Disassembler function
void disassemble(const uint8_t *code, size_t size) {
    printf("Disassembly:\n");

    for (size_t i = 0; i < size; i++) {
        uint8_t opcode = code[i];
        const char *mnemonic = decode_opcode(opcode);

        printf("0x%04lx: %-10s (0x%02X)\n", i, mnemonic, opcode);
        
        // Handle special cases for multi-byte instructions
        if (opcode == 0xCD && (i + 1) < size) { // INT immediate operand
            printf("0x%04lx:     INT 0x%02X\n", i + 1, code[i + 1]);
            i++;
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open binary file
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory and read file
    uint8_t *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }
    fread(buffer, 1, file_size, file);
    fclose(file);

    // Disassemble
    disassemble(buffer, file_size);

    // Cleanup
    free(buffer);
    return EXIT_SUCCESS;
}

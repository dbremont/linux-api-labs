#include <stdio.h>
#include <stdlib.h>
#include <capstone/capstone.h>

void disassemble(const uint8_t *code, size_t code_size) {
    csh handle;
    cs_insn *insn;
    size_t count;

    // Initialize Capstone disassembler for x86-64
    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
        fprintf(stderr, "Failed to initialize Capstone.\n");
        return;
    }

    // Disassemble the code
    count = cs_disasm(handle, code, code_size, 0x1000, 0, &insn);
    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            printf("0x%llx:\t%s\t%s\n", insn[i].address, insn[i].mnemonic, insn[i].op_str);
        }
        cs_free(insn, count);
    } else {
        fprintf(stderr, "Disassembly failed.\n");
    }

    // Close Capstone
    cs_close(&handle);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Read the binary file
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = malloc(file_size);
    if (!buffer) {
        perror("Could not allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    // Disassemble the binary
    disassemble(buffer, file_size);

    // Clean up
    free(buffer);
    return EXIT_SUCCESS;
}


void print_text(const char* text, int row, int col) {
    volatile uint16_t* video_memory = (uint16_t*)0xB8000;
    int i = 0;

    while (text[i] != '\0') {
        video_memory[row * 80 + col + i] = (0x0F << 8) | text[i];  // Texto blanco
        i++;
    }
}
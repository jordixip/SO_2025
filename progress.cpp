void draw_progress_bar(int progress) {
    volatile uint16_t* video_memory = (uint16_t*)0xB8000;
    int bar_start = 12 * 80 + 20; // Posición en pantalla

    for (int i = 0; i < progress; i++) {
        video_memory[bar_start + i] = (0x0A << 8) | '='; // Color verde
    }
}
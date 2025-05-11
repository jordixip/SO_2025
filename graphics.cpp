void set_graphics_mode() {
    struct VBEInfoBlock vbe;
    vbe.VbeSignature[0] = 'V';
    vbe.VbeSignature[1] = 'B';
    vbe.VbeSignature[2] = 'E';
    vbe.VbeSignature[3] = '2';

    vbe_call(0x4F02, (void*)0x118); // Activar modo 1024x768, 32 bits
}

void put_pixel(int x, int y, uint32_t color) {
    uint32_t* framebuffer = (uint32_t*)0xA0000;
    framebuffer[y * SCREEN_WIDTH + x] = color;
}
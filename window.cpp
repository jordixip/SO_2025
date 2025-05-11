class Window {
public:
    int x, y, width, height;
    uint32_t color;

    Window(int x, int y, int w, int h, uint32_t col);
    void draw();
};

Window::Window(int x, int y, int w, int h, uint32_t col)
    : x(x), y(y), width(w), height(h), color(col) {
}

void Window::draw() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            put_pixel(x + j, y + i, color);
        }
    }
}
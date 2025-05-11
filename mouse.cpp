void handle_mouse_click(int mouse_x, int mouse_y) {
    for (Window& win : windows) {
        if (mouse_x >= win.x && mouse_x <= win.x + win.width &&
            mouse_y >= win.y && mouse_y <= win.y + win.height) {
            win.color = 0xFF0000;  // Cambiar color al hacer clic
            win.draw();
        }
    }
}
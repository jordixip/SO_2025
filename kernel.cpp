void kernel_main() {
    print_text("Cargando Kernel...", 10, 30);

    for (int p = 0; p < 50; p++) {
        draw_progress_bar(p);
        sleep(50);
    }

    set_graphics_mode();
    enable_mouse();

    Window main_window(50, 50, 200, 150, 0x00AAFF);
    main_window.draw();

    while (1) {
        update_cursor();
        handle_mouse_click(mouse_x, mouse_y);
    }
}
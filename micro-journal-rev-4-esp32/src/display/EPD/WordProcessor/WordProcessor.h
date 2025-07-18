#ifndef WORDPROCESSOR_h
#define WORDPROCESSOR_h

#include <Arduino.h>

//
void WP_setup();

// 
void WP_render();

// 
void WP_keyboard(char key, bool pressed, int index);

//
void WP_render_cursor();

//
void WP_render_text();
void WP_render_text_line(int i, int cursorY);
void WP_clear_row(int row);

void WP_render_status();
void WP_check_saved();
void WP_check_sleep();

//
void convert_extended_ascii_to_utf8(const char *input, char *output, size_t output_size);

#endif
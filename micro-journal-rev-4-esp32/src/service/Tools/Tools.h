#ifndef Tools_h
#define Tools_h

#include <Arduino.h>

String formatNumber(int num);
size_t fileSize(String fileName);
String asciiToUnicode(uint8_t value);

#endif
#ifndef __SEG7_H__
#define __SEG7_H__
#ifdef __cplusplus
extern "C" {
    #endif

    #include <stdint.h>
    #include <Arduino.h>

    void seg7_init(const uint8_t* pins);
    void seg7_display(uint8_t num);

    #ifdef __cplusplus
}
#endif
#endif /* #ifndef __SEG_7_H__ */
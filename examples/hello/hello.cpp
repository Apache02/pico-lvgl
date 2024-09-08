#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/binary_info.h"
#include "drivers/led.h"
#include "drivers/SPI.h"
#include "drivers/st7789/io.h"
#include "drivers/st7789/display.h"
#include "lvgl/lvgl.h"


// board config
#define LED_PIN PICO_DEFAULT_LED_PIN

#define DISPLAY_SPI_SDA          19
#define DISPLAY_SPI_SCL          18
#define DISPLAY_SPI_CS           17
#define DISPLAY_SPI_DC           16
#define DISPLAY_SPI_RES          22
#define DISPLAY_SPI_WIDTH        240
#define DISPLAY_SPI_HEIGHT       320

// global variables
LED led(LED_PIN);
IO::SPI spi(DISPLAY_SPI_SDA, -1, DISPLAY_SPI_SCL);
st7789::IO_Spi display_io(spi, DISPLAY_SPI_CS, DISPLAY_SPI_DC, DISPLAY_SPI_RES);
//st7789::IO_Spi_Dma display_io(spi, DISPLAY_SPI_CS, DISPLAY_SPI_DC, DISPLAY_SPI_RES);
st7789::Display display(&display_io, DISPLAY_SPI_WIDTH, DISPLAY_SPI_HEIGHT);

// recommended buffer size 1/10 of screen size
uint16_t buf1[DISPLAY_SPI_WIDTH * DISPLAY_SPI_HEIGHT / 10];
uint16_t buf2[DISPLAY_SPI_WIDTH * DISPLAY_SPI_HEIGHT / 10];


void startup_test() {
    printf("%s START\n", __FUNCTION__);
    led.on();
    sleep_ms(2000);
    led.off();
    sleep_ms(10);
    printf("%s DONE\n", __FUNCTION__);
}

void lv_flush_cb(lv_display_t *lvDisplay, const lv_area_t *lvArea, uint8_t *px_map) {
    display.draw(
            lvArea->x1, lvArea->y1,
            lvArea->x2, lvArea->y2,
            (uint16_t *) px_map,
            (lvArea->x2 - lvArea->x1 + 1) * (lvArea->y2 - lvArea->y1 + 1)
    );

    /* IMPORTANT!!!
     * Inform LVGL that you are ready with the flushing and buf is not used anymore*/
    lv_display_flush_ready(lvDisplay);
}

int main() {
    bi_decl(bi_program_description("This is a pico-drivers-example binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();
    spi.init(IO::SPI_BAUDRATE_MAX);
    display_io.init();
    display.init();

    // lvgl init
    lv_init();
    lv_display_t *lvDisplay = lv_display_create(DISPLAY_SPI_WIDTH, DISPLAY_SPI_HEIGHT);
    lv_display_set_flush_cb(lvDisplay, lv_flush_cb);
    lv_display_set_buffers(lvDisplay, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    startup_test();

    // draw
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    repeating_timer_callback_t do_tick_cb = [](repeating_timer_t *rt) {
        lv_tick_inc(5);

        return true;
    };
    repeating_timer_t timer;
    add_repeating_timer_ms(
            5,
            do_tick_cb,
            NULL,
            &timer
    );

    for (;;) {
        lv_task_handler();
        sleep_ms(500);
    }

    return 0;
}

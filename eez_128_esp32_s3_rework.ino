#include <lvgl.h>
#include "lv_conf.h"
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "ui.h"
#include <screens.h>
#include <TFT_eSPI.h>

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
#define DEMO_SCREEN_COUNT 5
const unsigned long screenInterval = 5000;  

lv_obj_t* demoScreens[DEMO_SCREEN_COUNT];

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); 

#if LV_USE_LOG != 0
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void example_increase_lvgl_tick(void *arg)
{
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

void uiTask(void* pvParameters) {
    while (true) {
        lv_timer_handler();  // Handle LVGL updates
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


void setup(){
    Serial.begin(115200);
    pinMode(40, OUTPUT); 
    digitalWrite(40, HIGH); // Turn it on at boot  
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    ////Iniatialize LVGL
    lv_init();

    tft.begin();          /* TFT init */
    tft.setRotation( 2 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    Serial.println("1");
    lv_disp_drv_register( &disp_drv );

    const esp_timer_create_args_t lvgl_tick_timer_args = {
      .callback = &example_increase_lvgl_tick,
      .name = "lvgl_tick"
    };

    esp_timer_handle_t lvgl_tick_timer = NULL;
    esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);
    ui_init();
  
    xTaskCreatePinnedToCore(uiTask, "UI Task", 4096, NULL, 1, NULL, 1);
    Serial.println("Setup done");
}



void loop(){
    // (if using freertos task uiTask, this is not needed, hence commented out)
    // lv_timer_handler(); 
    
    ui_tick();
    delay(5);
}

// Test
// test
/* Test2 */
typedef struct {
    uint16_t schema;
    uint16_t address;           
    uint32_t uptime_ms;         
    uint8_t n;                  

    uint16_t batt_mv[6];        
    uint16_t panel_mv[6];       
    uint32_t bmp085_press_pa;   
    int16_t bmp085_temp_decic;  
    uint16_t apogee_w_m2[20];
} schema_3;

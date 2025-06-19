/*
 * File:   main.c
 */
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char operational_mode = WASHING_PROGRAM_SCREEN;
unsigned char reset_flag = RESET_WASH_PROGRAM_SCREEN;

static void init_config(void) {
    //initialize clcd
    init_clcd();
    //initialize digital keypad
    init_digital_keypad();
    //initialize timer
    init_timer2();
    //initialize global and peripheral interrupts
    GIE=1;
    PEIE=1;
    BUZZER_DDR = 0;
    FAN_DDR = 0; 
    BUZZER = OFF;
    FAN = OFF;
            
}

void main(void) {
    init_config();
    unsigned char key;

    clcd_print("Press Key5 to", LINE1(1));
    clcd_print("Power On", LINE2(5));
    clcd_print("Washing Machine", LINE3(1));
    
    while (read_digital_keypad(STATE)!=SW5){
        for(unsigned long int delay=3000; delay--;);//wait till SW5 is pressed
    }
    
    clear_screen();
    power_on_screen();
 
    
    
    while (1) {
       
        key = read_digital_keypad(STATE);
        //to avoid bouncing
        for(unsigned int delay=100; delay--;);
        
        if (key==LPSW4 && operational_mode == WASHING_PROGRAM_SCREEN){
            operational_mode = WATER_LEVEL_SCREEN;
            reset_flag = RESET_WATER_LEVEL_SCREEN;
        }
        else if (key==LPSW4 && operational_mode == WATER_LEVEL_SCREEN){
            operational_mode = START_STOP_SCREEN;
            clear_screen();
        }
        else if (key == SW5 && operational_mode == PAUSE) {
            TMR2ON = 1;
            FAN = ON;
            operational_mode = START_SCREEN;
        }
        switch (operational_mode) {
            case WASHING_PROGRAM_SCREEN:
                washing_program_display(key);
                break;
            case WATER_LEVEL_SCREEN:
                water_level_display(key);
                break;
            case START_STOP_SCREEN:
                start_stop_display(key);
                if (key == SW5) {
                    operational_mode = START_SCREEN;
                    reset_flag = RESET_START_SCREEN;
                }
                else if (key == SW6) {
                    clear_screen();
                    operational_mode = WASHING_PROGRAM_SCREEN;
                    reset_flag = RESET_WASH_PROGRAM_SCREEN;
                }
                break;
            case START_SCREEN:
                start_screen_display();
                if (key == SW6) {
                    TMR2ON = 0;
                    FAN = OFF;
                    operational_mode = PAUSE;
                }
                else if (key == SW1) {
                    TMR2ON = 0;
                    FAN = OFF;
                    clear_screen();
                }
                door_status_check(key);
                break;
        }
            
               
    }
    return;
}

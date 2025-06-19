#include "main.h"
char *washing_program[]={"Daily", "Heavy" , "Dedicates", "Whites", "Stain wash","Eco cottons", "Woolens" , "Bed sheets", "Rinse+Dry" , "Dry only",
"Wash only" , "Aqua store"};
unsigned char program_no = 0;
char *water_level[] = {"Auto", "Low", "Medium", "High", "Max"};
unsigned char level=0;
unsigned char secs,min;
unsigned int total_time,wash_time,rinse_time,spin_time,time; 

void power_on_screen(void) {
    
    unsigned char i;
    while(i<=15) {
        clcd_putch(Block,LINE1(i));
        __delay_ms(50);
        i++;
    }
    i=0;
    clcd_print("Powering On",LINE2(3));
    clcd_print("Washing Machine",LINE3(1));
    while(i<=15) {
        clcd_putch(Block,LINE4(i));
        __delay_ms(50);
        i++;
    }
    __delay_ms(1000);
    
}

void clear_screen(void) {
    
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
    
}

void washing_program_display(unsigned char key) {
    
    if (reset_flag == RESET_WASH_PROGRAM_SCREEN) {
        
        clear_screen();
        reset_flag = RESET_NOTHING;
        
    }
    if (key == SW4){
        clear_screen();
        program_no++;
        if(program_no == 12) {
            program_no = 0;
        }
    }
    clcd_print("Washing Program: ",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(washing_program[program_no % 12], LINE2(1));
    clcd_print(washing_program[(program_no + 1) % 12], LINE3(1));
    clcd_print(washing_program[(program_no + 2) % 12], LINE4(1));
   
}

void water_level_display(unsigned char key) {
    
    
    if (reset_flag == RESET_WATER_LEVEL_SCREEN) {
        
        clear_screen();
        reset_flag = RESET_NOTHING;
        
    }
    if (key == SW4){
        clear_screen();
        level++;
        if(level == 5) {
            level = 0;
        }
    }
    clcd_print("Water Level: ",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(water_level[level % 5], LINE2(1));
    clcd_print(water_level[(level + 1)% 5], LINE3(1));
    clcd_print(water_level[(level + 2) % 5], LINE4(1));
    
}

void start_stop_display(unsigned char key) {
    
    
    clcd_print("Press Switch: ",LINE1(0));
    clcd_print("SW5: Start",LINE2(0));
    clcd_print("SW6: Stop",LINE3(0));
    
}

void start_screen_display(void){
    static unsigned char displayed =0;
    if (reset_flag == RESET_START_SCREEN) {
        
        clear_screen();
        reset_flag = RESET_NOTHING;
        displayed =0;
    }
    if (!displayed) {
    set_time();
           
    clcd_print("Prog: ",LINE1(0));
    clcd_print(washing_program[program_no%12],LINE1(6));
    clcd_print("Time: ",LINE2(0));
    clcd_putch((min/10) + '0',LINE2(6));
    clcd_putch((min%10) +'0',LINE2(7));
    clcd_putch(':',LINE2(8));
    clcd_putch((secs/10) + '0',LINE2(9));
    clcd_putch((secs%10) +'0',LINE2(10));
    
    __delay_ms(1000);
    
    clear_screen();
    FAN = ON;
    clcd_print("Function: ",LINE1(0));
    clcd_print("Time:",LINE2(0));
    clcd_print("SW5-START",LINE3(0));
    clcd_print("SW6-PAUSE",LINE4(0));
    
   
    total_time = time = min*60 + secs;
    wash_time = (int)total_time * 0.46;
    rinse_time = (int)total_time * 0.12;
    spin_time = (int)total_time* 0.42;
    
    //switching on timer
    TMR2ON = 1;
    displayed = 1;
    }
 
    total_time = min*60 + secs;
    
    if (program_no<=7) {
        
        if (total_time>rinse_time + spin_time) {
            
            clcd_print("WASH  ",LINE1(10));
           
        }
        else if (total_time> spin_time) {
            
            clcd_print("RINSE ",LINE1(10));
            
        }
        else {
            clcd_print("SPIN  ",LINE1(10));
        }
    }
    else if (program_no==8) {
        if (total_time>= time - (time * 0.40)) {
            clcd_print("RINSE",LINE1(10));
        }
        else  {
            clcd_print("SPIN  ",LINE1(10));
        }
    }
    else if (program_no==9) {
        clcd_print("SPIN  ",LINE1(10));
    }
    else if (program_no==11) {
        clcd_print("RINSE",LINE1(10));
    }
    else{
        clcd_print("WASH  ",LINE1(10));
    }
    clcd_putch((min/10) + '0',LINE2(6));
    clcd_putch((min%10) +'0',LINE2(7));
    clcd_putch(':',LINE2(8));
    clcd_putch((secs/10) + '0',LINE2(9));
    clcd_putch((secs%10) +'0',LINE2(10));
    
    if (secs==0 && min==0) {
        static unsigned char displayed =0;
        if (!displayed){
            
        clear_screen();
        FAN = OFF;
        BUZZER = ON;
        clcd_print("Program Finished",LINE1(0));
        clcd_print("Remove Clothes",LINE3(1));
        __delay_ms(2000);
        BUZZER = OFF;
        displayed=1;
        TMR2ON = 0;
        operational_mode = WASHING_PROGRAM_SCREEN;
        reset_flag = RESET_WASH_PROGRAM_SCREEN;
        }
    }

} 

void set_time(void) {
    unsigned char sec;
    switch (program_no) {
        case 0: //daily
            switch (level) {
                case 1:
                    sec = 33;
                    break;
                case 0:
                case 2:
                    sec = 41;
                    break;
                case 3:
                case 4:
                    sec = 45;
                    break;
            }
            break;
            
        case 1: //heavy
             switch (level) {
                case 1:
                    sec = 43;
                    break;
                case 0:
                case 2:
                    sec = 50;
                    break;
                case 3:
                case 4:
                    sec = 57;
                    break;
            }
            break; 
            
        case 2: //Dedicates
             switch (level) {
                case 1:
                case 0:
                case 2:
                    sec = 26;
                    break;
                case 3:
                case 4:
                    sec = 31;
                    break;
            }
            break; 
            
        case 3: //Whites
            sec = 76;
            break;

        case 4: //Stain wash
            sec = 96;
            break;

        case 5: //Eco cottons
             switch (level) {
                case 1:
                case 0:
                case 2:
                    sec = 31;
                    break;
                case 3:
                case 4:
                    sec = 36;
                    break;
            }
            break; 
            
        case 6: //Woolens
            sec = 29;
            break;

        case 7: //Bed sheets
             switch (level) {
                case 1:
                    sec = 46;
                    break;
                case 0:
                case 2:
                    sec = 53;
                    break;
                case 3:
                case 4:
                    sec = 60;
                    break;
            }
            break;

        case 8: //Rinse+Dry
             switch (level) {
                case 1:
                    sec = 18;
                    break;
                case 0:
                case 2:
                case 3:
                case 4:
                    sec = 20;
                    break;
            }
            break;
            
        case 9: //Dry only
            sec = 6;
            break;

        case 10: //Wash only
             switch (level) {
                case 1:
                    sec = 16;
                    break;
                case 0:
                case 2:
                    sec = 21;
                    break;
                case 3:
                case 4:
                    sec = 26;
                    break;
            }
            break;
            
        case 11: //Aqua store
            sec = 50;
            break;
    }
    
    if(sec>=60) {
        min = sec/60;
        secs = sec-60; 
    }
    else if (sec<60) {
        min = 0;
        secs = sec;
    }
    
}

void door_status_check(unsigned char key) {
    
    if (RB0 == 0) {
        TMR2ON = 0;
        FAN = OFF;
        BUZZER = ON;
        clear_screen();
        clcd_print("Door is Open",LINE1(2));
        clcd_print("Please CLose",LINE3(2));
        clcd_print("the Door!",LINE4(4));
        while(RB0 == 0) {
            ;
        }
        FAN = ON;
        BUZZER = OFF;
        TMR2ON = 1;
        clear_screen();
        clcd_print("Function: ", LINE1(0));
        clcd_print("Time:", LINE2(0));
        clcd_print("SW5-START", LINE3(0));
        clcd_print("SW6-PAUSE", LINE4(0));
    }
}

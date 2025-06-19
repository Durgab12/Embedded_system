/* 
 * File:   washing_machine_header.h
 * Author: Durga B
 *
 * Created on 15 June, 2025, 7:51 PM
 */

#ifndef WASHING_MACHINE_HEADER_H
#define	WASHING_MACHINE_HEADER_H

void power_on_screen(void);
void clear_screen(void);
void washing_program_display(unsigned char key);
void water_level_display(unsigned char key);
void start_stop_display(unsigned char key);
void start_screen_display(void);
void set_time(void);
void door_status_check(unsigned char key);
#endif	/* WASHING_MACHINE_HEADER_H */


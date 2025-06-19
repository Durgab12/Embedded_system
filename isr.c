#include <xc.h>
extern unsigned char secs,min;
unsigned int count ;
__interrupt() isr( void )
{
    if(TMR2IF)
    {
        if( ++count == 20000) // 250 , 200ns 8 bit timer for 1 sec
        {
            if (secs!=0) {
                secs--;
            }
            else if (secs==0 && min!=0) {
                min--;
                secs=60;
            }
            count = 0;
            
            PORTD = ~PORTD;
        }
        
        TMR2IF = 0; // clear interrupt flag 
        
    }
    
    
}


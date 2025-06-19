# Embedded_system_washing_machine_stimulation
**Implementation Workflow**

This project simulates the operation of a real washing machine using the PIC16F877A microcontroller on a PIC Genios board. The entire system is developed using Embedded C from scratch and emulates user interaction, program logic, timing control, and state transitions, similar to an actual washing machine.

**Key Implementation Steps:**

**Understanding the Logic**

We began by studying the working of a real-world washing machine — including how it handles inputs, manages different washing modes, and transitions through states like wash, rinse, and spin.

**Code Development from Scratch**

The project was built using Embedded C, starting from the base display logic to user interaction and final program execution.

**Startup & User Input**

The system displays an initial startup screen and waits for a power-on key press from the user.

**Program & Water Level Selection**

Once powered on, the user can choose a washing program (e.g., Daily, Heavy, Delicate) and a water level (Low, Medium, High).

**Time Calculation & Display**

The total washing time is set dynamically based on the selected program and water level. This value is displayed on a 16x2 character LCD.

**Washing Cycle Execution**

The system begins executing the wash cycle:

**Displays the remaining time**

Transitions through Wash → Rinse → Spin phases based on internal timers

A fan indicator (e.g., LED) is turned ON during active phases

**Door Safety Logic**

The system constantly monitors door status:

If the door is opened mid-cycle, the system pauses

A buzzer is turned ON and remains active until the door is closed

**Cycle Completion**

At the end of the washing cycle, a "Wash Complete" message is displayed, and the buzzer is triggered briefly to indicate successful completion.

This approach ensures that the embedded system mimics real-life washing machine behavior in terms of timing, safety, user interface, and state management — all implemented using low-level embedded C code on a microcontroller platform.


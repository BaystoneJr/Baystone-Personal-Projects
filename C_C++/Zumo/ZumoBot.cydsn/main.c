/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include <stdlib.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

void prog_Start(u_int32_t delay);
void prog_End(void);
void long_turn(void);
void random_Tank_Turn(int turn_degrees);
int reflect_comparison(struct sensors_ first, struct sensors_ second);
void reflect_turn(struct sensors_ dig, int leftOrRight);
void random_Turn_Left_Right(int direction);

#if 0
    
//Week 3, assignment 1
void zmain(void) {
    motor_start();
    motor_forward(0, 0);
    
    prog_Start(500);
    
    //first straight
    motor_forward(100, 3350);
    
    //first turn
    motor_turn(100, 0, 525);
   
    //second straight
    motor_forward(100, 2550);
    
    //second turn
    motor_turn(100, 0, 525);
    
    //third straight
    motor_forward(100, 2750);
    
    //third turn
    motor_turn(100, 0, 625);
    
    motor_turn(100, 0, 25);
    //start of the fourth long turn
    long_turn();
    //end of the fourht long turn
    
    //start of the final straight
    motor_forward(100, 700);
    
    motor_forward(0, 0);
    
    prog_End();
}
#endif
#if 0
//Week 3, assignment 2    
    
//2,33 delay = 1 degree  
//210 delay = 90 degrees
//280 delay = 120 degrees
//630 delay = 270 degrees

//If you want to stop the robots running in the simulator, press the reset button on the board
    
void zmain(void) {
    //start the required components
    motor_start();
    Ultra_Start();
    
    int ultraDistance = 0;
     
    //Start the program by pressing the button in the middle of the board
    prog_Start(500);
    
    motor_forward(100, 700);
    
    while(true) {
        //Get the reading from the ultra sonic sensor
        ultraDistance = Ultra_GetDistance();
       
        printf("Ultra distance value: %d\n", ultraDistance);
        
        if(ultraDistance < 10) {
            //If the robot is close enough to the walls, the robot will back off a little and turn 120 degrees left
            motor_forward(0,0);
            
            vTaskDelay(500);
            
            motor_backward(150, 100);
            
            motor_forward(0, 0);
            
            vTaskDelay(300);
            
            motor_turn(255, 0, 280);
            
            motor_forward(0, 0);
            
            vTaskDelay(500);
            
            motor_forward(100, 700);
        } else {
            //If the robot is not close enough, it will delay for the ultra sonic sensor reading
           vTaskDelay(100); 
        }
    }
    
    prog_End();
}
#endif
#if 0
//Week 3, assignment 3    
    
//2,33 delay = 1 degree  
//210 delay = 90 degrees
//280 delay = 120 degrees
//630 delay = 270 degrees

//If you want to stop the robots running in the simulator, press the reset button on the board
    
void zmain(void) {
    //Activate all the necessary components and assign seed for rand()-function
    motor_start();
    Ultra_Start();
    srand(2);
   
    int ultraDistance = 0;
    
    //Start the program by pressing the middle button of the board
    prog_Start(500);
    
    //Move the robot
    motor_forward(100, 700);
    
    while(true) {
        //Get random turn degrees, the degrees are based on the speed of the turn
        int turn_degrees = rand() % 421 + 210;
        
        //Get the distance to the barrier
        ultraDistance = Ultra_GetDistance();
       
        printf("Ultra distance value: %d\n", ultraDistance);
        
        if(ultraDistance < 10) {
            //If the robot is close enough, it will back off little, and turn the random degrees between 90-270, and then continue foward
            motor_forward(0,0);
            
            vTaskDelay(500);
            
            motor_backward(150, 300);
            
            motor_forward(0, 0);
            
            vTaskDelay(300);
            
            random_Tank_Turn(turn_degrees);
            
            motor_forward(0, 0);
            
            vTaskDelay(500);
            
            motor_forward(100, 700);
        } else {
            //If it is not close enough, it will just delay for the ultra_sonic to get the reading
            vTaskDelay(100);
        }
    }
    
    prog_End();
}
#endif
#if 0
 //Week 4, Assignment 1
 void zmain(void) {
    //define structures for reflect input, temporary input and comparison for a line
    struct sensors_ dig;
    struct sensors_ line_comparison = {1, 1, 1, 1, 1, 1};
    struct sensors_ valiaikainen;
    
    //define variables that program will use for counting lines and comparing reflect sensor input
    int line_counter = 0;
    int isStructsSame = 0;
    int isSameasLine = 0;
    
    //start motor and reflect sensor and set treshold for reflect sensor
    motor_start();
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    //start program by pressing middle button on the microcontroller. After starting it will drive for the starting line and wait for the IR signal
    prog_Start(500);
    
    reflectance_digital(&dig);
    
    isSameasLine = reflect_comparison(dig, line_comparison);
    
    while(isSameasLine != 1) {
        motor_forward(25, 100); 
        reflectance_digital(&dig);
        isSameasLine = reflect_comparison(dig, line_comparison);
    }
    
    printf("Robot on the line\n");
    printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
    
    
    motor_forward(0, 0);
   
    valiaikainen = dig;
    
    IR_wait();

    //after getting the IR signal, robot will start to move foward and for five lines 
    while(line_counter != 5)
    {   
        motor_forward(50, 200);
        reflectance_digital(&dig); 
        isStructsSame = reflect_comparison(dig, valiaikainen);
        isSameasLine = reflect_comparison(dig, line_comparison);
                
        //logic for counting lines, function compares to structure inputs, the first one compares inputs between temporary and current reflect input,
        //second one compares inputs between current and a vertical line, and if the input is a sideway line and it is not the same as temporary aka not same as...
        //last line input, it will count a line
        if(isStructsSame == 1 && isSameasLine != 1) {
            printf("Current: %5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
        } else if(isStructsSame != 0 && isSameasLine == 1) {
            line_counter++;
            printf("Current: %5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            printf("Line counter: %d\n", line_counter);
            valiaikainen = dig;
        }
    }
    motor_forward(0,0);
    prog_End();
}
#endif
#if 0
//Week 4, assignment 2
void zmain(void) {
    //define structures for reflect input, temporary input and comparison for a line
    struct sensors_ dig;
    struct sensors_ line_comparison = {1, 1, 1, 1, 1, 1};
    struct sensors_ valiaikainen;
    
    //define variables that program will use for counting lines and comparing reflect sensor input
    int line_counter = 0;
    int isStructsSame = 0;
    int isSameasLine = 0;

    //start motor and reflect sensor and set treshold for reflect sensor
    motor_start();
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    //start program by pressing middle button on the microcontroller. After starting it will drive for the starting line and wait for the IR signal
    prog_Start(500);
    
    reflectance_digital(&dig);
    
    isSameasLine = reflect_comparison(dig, line_comparison);
    
    while(isSameasLine != 1) {
        motor_forward(25, 100); 
        reflectance_digital(&dig);
        isSameasLine = reflect_comparison(dig, line_comparison);
    }
    
    printf("Robot on the line\n");
    printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
    
    
    motor_forward(0, 0);
   
    valiaikainen = dig;
    
    IR_wait();
    isSameasLine = 0;

    //after getting the IR signal, the robot will continue the track and automatically turn itself, if either of the middle two reflect sensors goes of the track, the robot will fix it's course
    while(line_counter != 2) {
        reflectance_digital(&dig);
        if(dig.R1 == 1 && dig.L1 == 1) {
            motor_forward(25, 200);
            printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
        } else if(dig.R1 == 0 && dig.L1 == 1) {
            motor_forward(0, 0);
            motor_turn(0, 25, 100);
        } else if(dig.R1 == 1 && dig.L1 == 0) {
            motor_forward(0, 0);
            motor_turn(25, 0, 100);
        }

        isSameasLine = reflect_comparison(dig, line_comparison);
        isStructsSame = reflect_comparison(dig, valiaikainen);
        //this checks for a sideways line and adds to line counter if its true
        if(isSameasLine == 1 && isStructsSame == 0) {
           line_counter++;
           valiaikainen = dig;
        }
    }
    motor_forward(0, 0);
    prog_End();
    }
#endif
#if 0
//Week 4, assignment 3
void zmain(void) {
    //define structures for reflect input, temporary input and comparison for a line
    struct sensors_ dig;
    struct sensors_ line_comparison = {1, 1, 1, 1, 1, 1};
    struct sensors_ valiaikainen;
    
    //define variables that program will use for counting lines, turns and comparing reflect sensor input
    int line_counter = 0;
    int turn_counter = 0;
    int isStructsSame = 0;
    int isSameasLine = 0;
    
    //start motor and reflect sensor and set treshold for reflect sensor
    motor_start();
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    //start program by pressing middle button on the microcontroller. After starting it will drive for the starting line and wait for the IR signal
    prog_Start(500);
    
    reflectance_digital(&dig);
    
    isSameasLine = reflect_comparison(dig, line_comparison);
    
    while(isSameasLine != 1) {
        motor_forward(25, 100); 
        reflectance_digital(&dig);
        isSameasLine = reflect_comparison(dig, line_comparison);
    }
    
    printf("Robot on the line\n");
    printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
    
    motor_forward(0, 0);
   
    valiaikainen = dig;
    
    IR_wait();
    
    //after getting the IR signal, the program will start, the robot will go foward till it counts four lines
    isSameasLine = 0;
    motor_forward(50, 50);
    while(line_counter != 4) {
        printf("Start of mainloop\n");
        reflectance_digital(&dig); //gets current reflect sensor input
        isSameasLine = reflect_comparison(dig, line_comparison); //compares current input to a sideways line input
        isStructsSame = reflect_comparison(dig, valiaikainen); //compares current input to temporary input

        //First two if/else if statements check for a new line and will count for it, the last two else if statements check if the robot is of the track line and will correct the heading            
        if(isStructsSame == 1 && isSameasLine != 1) {
            printf("Current: %5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
        } else if(isStructsSame != 0 && isSameasLine == 1) {
            line_counter++;
            printf("Current: %5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            printf("Line counter: %d\n", line_counter);
            valiaikainen = dig;
        } else if(dig.R1 == 0 && dig.L1 == 1) {
            motor_forward(0, 0);
            while(dig.R1 != 1) {
                motor_turn(0, 15, 25);
                reflectance_digital(&dig);
            }
        } else if(dig.R1 == 1 && dig.L1 == 0) {
            motor_forward(0, 0);
            while(dig.L1 != 1) {
                motor_turn(15, 0, 25);
                reflectance_digital(&dig);
            }
        }
        
        //logic for turning on the correct lines. Switch statement takes the line counter as expression and will turn when line counter is 1, 2 or 3...
        //... If the robot has made the turn already or the are no cases for the counter values, robot will continue foward
        switch(line_counter) {
            case 1:
                //checks if robot has made the turn or not, if it has not, it will turn and change the turn counter value to notate the turn, if it has turned, it will go straight
                if(turn_counter == 0) {
                    reflect_turn(dig, 1);
                    turn_counter++;
                    break;
                }
                goto go_foward;
                break;
            case 2:
                //checks if robot has made the turn or not, if it has not, it will turn and change the turn counter value to notate the turn, if it has turned, it will go straight
                if(turn_counter == 1) {
                    reflect_turn(dig, 0);
                    turn_counter++;
                    break;
                }
                goto go_foward;
                break;
            case 3:
                //checks if robot has made the turn or not, if it has not, it will turn and change the turn counter value to notate the turn, if it has turned, it will go straight
                if(turn_counter == 2) {
                    reflect_turn(dig, 0);
                    turn_counter++;
                    break;
                }
                goto go_foward;
                break;
            default:
                go_foward:
                motor_forward(50, 50);
            break;
        }
        

    }
    motor_forward(0, 0);
    prog_End();
}
#endif
#if 0
 //Week 5, assignment 1
 void zmain(void) {
    const int RELEASED = 0;
    const int PRESSED = 1;
    int button_read = 0;
    int last_press = 0;
    const char *topic = "COM5/button";
    int current_tick = 0;
    int last_tick = 0;
    int elapsed_time = 0;   
        
    prog_Start(500);
    
    while(true) {
        button_read = SW1_Read();
            
        if(button_read == PRESSED && last_press == RELEASED) {
            current_tick = xTaskGetTickCount();
            elapsed_time = current_tick - last_tick;
            print_mqtt(topic, "time: %d ms", elapsed_time);
            last_tick = xTaskGetTickCount();
            last_press = 1;
        } else if(button_read == RELEASED) {
            last_press = RELEASED;
        }    
    }
    prog_End();
}
#endif
#if 0
//Week 5, assignment 2
//2,33 delay = 1 degree  
//210 delay = 90 degrees
//280 delay = 120 degrees
//630 delay = 270 degrees
    
void zmain(void) {
    //Activate all the necessary components and assign seed for rand()-function
    motor_start();
    Ultra_Start();
    srand(2);
   
    const char *topic = "COM5/turn";
    char *turn_char;
    int ultraDistance = 0;
    
    //Start the program by pressing the middle button of the board
    prog_Start(500);
    
    //Move the robot
    motor_forward(100, 700);
    
    while(true) {
        //Get the random number for direction, 0 is left and 1 right
        int rand_direction = rand() % 2;
        
        //Get the distance to the barrier
        ultraDistance = Ultra_GetDistance();
        
        if(ultraDistance < 10) {
            //If the robot is close enough, it will back off little, and turn degrees 90 to random direction, and then continue foward
            motor_forward(0,0);
            
            vTaskDelay(500);
            
            motor_backward(150, 300);
            
            motor_forward(0, 0);
            
            vTaskDelay(300);
            
            random_Turn_Left_Right(rand_direction); //funtion for turningn to random direction
            
            turn_char = (rand_direction == 0) ? "Left" : "Right";   //ternary opertaion to determine the correct mqtt message
            
            print_mqtt(topic, ": %s", turn_char);
            
            motor_forward(0, 0);
            
            vTaskDelay(500);
            
            motor_forward(100, 700);
        } else {
            //If it is not close enough, it will just delay for the ultra_sonic to get the reading
            vTaskDelay(100);
        }
    }
    
    prog_End();
}
#endif
#if 1
//Week 5, assignemnt 3
//uses 5-step ladder
//counts for one lap/line only
void zmain(void) {
    //define structures for reflect input, temporary input and comparison for a line
    struct sensors_ dig;
    struct sensors_ line_comparison = {1, 1, 1, 1, 1, 1};
    struct sensors_ valiaikainen;
    
    //define variables that program will use for counting lines, comparing reflect sensor input, storing and counting time and for mqtt topic
    int line_counter = 0;
    int isStructsSame = 0;
    int isSameasLine = 0;
    int startTime = 0, endTime = 0, elapsedTime = 0;
    const char *topic = "COM5/lap";
    
    //start motor and reflect sensor and set treshold for reflect sensor
    motor_start();
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    //start program by pressing middle button on the microcontroller. After starting it will drive for the starting line and wait for the IR signal
    prog_Start(500);
    
    reflectance_digital(&dig);
    
    isSameasLine = reflect_comparison(dig, line_comparison);
    
    while(isSameasLine != 1) {
        motor_forward(25, 100); 
        reflectance_digital(&dig);
        isSameasLine = reflect_comparison(dig, line_comparison);
    }
    
    printf("Robot on the line\n");
    printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
    
    
    motor_forward(0, 0);
   
    valiaikainen = dig;
    
    IR_wait();
    
    startTime =  xTaskGetTickCount();
    //after getting the IR signal, robot will start to move foward and for five lines 
    while(line_counter != 1)
    {   
        motor_forward(50, 200);
        reflectance_digital(&dig); 
        isStructsSame = reflect_comparison(dig, valiaikainen);
        isSameasLine = reflect_comparison(dig, line_comparison);
                
        //logic for counting lines, function compares to structure inputs, the first one compares inputs between temporary and current reflect input,
        //second one compares inputs between current and a vertical line, and if the input is a sideway line and it is not the same as temporary aka not same as...
        //last line input, it will count a line
        if(isStructsSame == 1 && isSameasLine != 1) {
            continue;
        } else if(isStructsSame != 0 && isSameasLine == 1) {
            line_counter++;
            valiaikainen = dig;
        }
    }
    endTime = xTaskGetTickCount();
    elapsedTime = endTime - startTime;
    print_mqtt(topic, "lap: %d",elapsedTime);
    motor_forward(0,0);
    prog_End();
}
#endif
#if 0
// Name and age
void zmain(void)
{
    char name[32];
    int age;
    
    
    printf("\n\n");
    
    printf("Enter your name: ");
    //fflush(stdout);
    scanf("%s", name);
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    
    printf("You are [%s], age = %d\n", name, age);

    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//battery level//
void zmain(void)
{
    ADC_Battery_Start();        

    int16 adcresult =0;
    float volts = 0.0;

    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

    while(true)
    {
        char msg[80];
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            
            // Print both ADC results and converted value
            printf("%d %f\r\n",adcresult, volts);
        }
        vTaskDelay(500);
    }
 }   
#endif

#if 0 

//Tick Timer Example
void zmain(void) 
{
	TickType_t Ttime = xTaskGetTickCount();
	TickType_t PreviousTtime = 0;

	while(true) 
	{
		while(SW1_Read()) vTaskDelay(1); // loop until user presses button
		Ttime = xTaskGetTickCount(); // take button press time
		/*Print out the time between button presses in seconds. int cast used to suppress warning messages*/
		printf("The amount of time between button presses is: %d.%d seconds\n", (int)(Ttime-PreviousTtime)/1000%60, (int)(Ttime-PreviousTtime)%1000);
		while(!SW1_Read())vTaskDelay(1); // loop while user is pressing the button
		PreviousTtime = Ttime; // remember previous press time
	}
	
}

#endif

#if 0
// button
void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
	    TickType_t Ttime = xTaskGetTickCount(); // take start time
        bool timeout = false;
        while(SW1_Read() == 1) {
            if(xTaskGetTickCount() - Ttime > 5000U) { // too long time since start
                timeout = true;
                break;
            }
            vTaskDelay(10);
        }
        if(timeout) {
            printf("You didn't press the button\n");
        }
        else {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    while(true)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif


#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    
    while(true) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
    }
}   
#endif

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    while(true)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif



#if 0
//IR receiver - read raw data
// RAW data is used when you know how your remote modulates data and you want to be able detect 
// which button was actually pressed. Typical remote control protocols requires a protocol specific
// state machine to decode button presses. Writing such a state machine is not trivial and requires
// that you have the specification of your remotes modulation and communication protocol    
void zmain(void)
{
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    // print received IR pulses and their lengths
    while(true)
    {
        if(IR_get(&IR_val, portMAX_DELAY)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
        }
    }    
 }   
#endif


#if 0
//reflectance
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);        
        
        vTaskDelay(200);
    }
}   
#endif


#if 0
//motor
void zmain(void)
{
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif

#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    while(true)
    {
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(50);
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    while(true)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif


#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    while(true)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.L3, ref.L2, ref.L1, ref.R1, ref.R2, ref.R3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.L3, dig.L2, dig.L1, dig.R1, dig.R2, dig.R3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    while(true)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

/* [] END OF FILE */

//Custom functions

void prog_Start(u_int32_t delay) {
    while(SW1_Read() == 1);
    BatteryLed_Write(1);
    vTaskDelay(delay);
    BatteryLed_Write(0);
}
void prog_End(void) {
    while(true) {
        vTaskDelay(2000);
    }
}
void long_turn() {
        
    
    motor_forward(100, 250);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 150);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 350);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 350);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 350);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 250);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 250);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 250);
    
    motor_turn(100, 0, 50);
    
    motor_forward(100, 250);
    
}
void random_Tank_Turn(int turn_degrees) {

    //int turn_degrees = rand() % 421 + 210;
    
    printf("Random value: %d\n", turn_degrees);
    
    SetMotors(0, 1, 255, 255, turn_degrees);

}
int reflect_comparison(struct sensors_ first, struct sensors_ second) {
    if((first.L1 == second.L1) && (first.L2 == second.L2) && (first.L3 == second.L3) && (first.R1 == first.R1) && (first.R2 == second.R2) && (first.R3 == second.R3)) {
        return 1;
    } else {
       return 0;
    } 
}
void reflect_turn(struct sensors_ dig, int leftOrRight) {
    int turnStructSame = 0;
    int isgoingStraight = 0;
    struct sensors_ straight_comparison = {0, 0, 1, 1, 0, 0};
    
    //if leftOrRight is 0, turn right, else turn left
    if(leftOrRight == 0) {
        motor_forward(0, 0);
        printf("If starts here\n");
        while(turnStructSame != 1) {
            reflectance_digital(&dig);
            if(dig.L1 == 0) {
                turnStructSame = 1;
            } else {
                motor_turn(15, 0, 25);
            }
        }
        printf("Start of second while\n");
        while(turnStructSame != 2) {
            reflectance_digital(&dig);
            isgoingStraight = reflect_comparison(dig, straight_comparison);
            if(isgoingStraight == 1) {
                turnStructSame = 2;
            } else {
                motor_turn(15, 0, 25);
            }
        }
        printf("End of if\n");
        
    } else {
        motor_forward(0, 0);
        printf("If starts here\n");
            while(turnStructSame != 1) {
                reflectance_digital(&dig);
                if(dig.R1 == 0) {
                    turnStructSame = 1;
                } else {
                    motor_turn(0, 15, 25);
                }
            }
        printf("Start of second while\n");
        while(turnStructSame != 2) {
            reflectance_digital(&dig);
            isgoingStraight = reflect_comparison(dig, straight_comparison);
            if(isgoingStraight == 1) {
                turnStructSame = 2;
            } else {
                motor_turn(0, 15, 25);
            }
        }
        printf("End of if\n");
    }
}
void random_Turn_Left_Right(int direction) {
    //turn left
    if(direction == 0) {
        motor_turn(255, 0, 210);
    } else if(direction == 1) {            //turn right
        motor_turn(0, 255, 210);
    }
}
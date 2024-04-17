#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHRCS.h>
#include <FEHBattery.h>

// Servo Max: 2277
// Servo Min: 500

// servo2 max: 2330
// servo2 min: 500

// function prototypes for all functions
void driveForward(float time, int percent);
void turn(char direction, float time, int dominant_motor_percent, int nondom_motor_percent);
void fuel(int correctLever);
void luggage();
void boardPass();
void passport();
void driveback();

// declare motor on motor port 0, set maximum voltage to 9.0 V
FEHMotor blm(FEHMotor::Motor1, 7.0);
FEHMotor brm(FEHMotor::Motor3, 7.0);
FEHMotor flm(FEHMotor::Motor0, 7.0);
FEHMotor frm(FEHMotor::Motor2, 7.0);

// declare servo motors, s1 = fuel servo, s2 = passport/luggage servo
FEHServo s1(FEHServo::Servo6);
FEHServo s2(FEHServo::Servo7);

// declare CdS cell
AnalogInputPin light(FEHIO::P2_7);

int main()
{
    // initialize RCS connection
    RCS.InitializeTouchMenu("E6aMLIy03");

    // wait for start light to turn on
    while (light.Value() > 0.9)
        ;

    // Get correct lever from the RCS
    int correctLever = RCS.GetCorrectLever();

    // reset servo motors
    s1.SetDegree(180);
    s2.SetDegree(80);

    // Hit Starting light
    driveForward(0.25, -40);

    // call fuel function, passing in correct lever
    fuel(correctLever);

    // reset servo after fuel task
    s1.SetDegree(180);

    // intermediate step to turn to luggage task
    turn('R', 0.655, 100, -100);

    // call luggage function
    luggage();

    // intermediate step to turn towards boarding pass light
    turn('L', 0.81, 100, -100);

    // call boarding pass function
    boardPass();

    // call passport stamp function
    passport();

    // call drive back function
    driveback();
}

void fuel(int correctLever)
{
    // set arm so it doesn't hit an fuel levers
    s1.SetDegree(120);

    // drive towards levers
    driveForward(0.78, 100);

    Sleep(0.25);

    // slight left
    turn('L', 0.9, 100, 25);

    // Check which lever to flip and perform some action
    if (correctLever == 0)
    {
        // Perform actions to flip left lever

        driveForward(0.26, -100);

        Sleep(0.5);
        // flip down
        s1.SetDegree(100);
        Sleep(5.0);
        // flip up
        s1.SetDegree(135);

        Sleep(0.5);
        //reset arm
        s1.SetDegree(120);

        driveForward(0.84, 100);
    }
    else if (correctLever == 1)
    {

        // horziontally towards ramp
        driveForward(0.07, 100);

        Sleep(0.5);
        // flip down
        s1.SetDegree(100);

        Sleep(5.0);
        // flip up
        s1.SetDegree(135);

        Sleep(0.5);
        // reset arm
        s1.SetDegree(120);

        driveForward(0.5175, 100);
    }
    else if (correctLever == 2)
    {
        // horziontally towards ramp
        driveForward(0.33, 100);

        Sleep(0.5);
        // flip down
        s1.SetDegree(100);

        Sleep(5.0);
        // flip up
        s1.SetDegree(135);

        Sleep(0.5);

        driveForward(0.25, 100);
    }
}
void luggage()
{
    // up ramp
    driveForward(1.9, 100);

    // turn right after ramp
    turn('R', 0.7, 100, -100);

    // drive to be aside luggage depository
    driveForward(0.7, 100);

    Sleep(0.6);

    // deposit luggage
    s2.SetDegree(30);

    Sleep(0.6);
}
void boardPass()
{
    // declare variables
    int button;
    int override;

    frm.SetPercent(40);
    flm.SetPercent(40);
    brm.SetPercent(40);
    blm.SetPercent(40);

    float t = TimeNow();

    //drive until light is detected, or if no light is detected, for 4.5 seconds
    while (light.Value() > 1.9)
        if (TimeNow() - t > 4.5)
        {
            override = 1;
            break;
        };

    float value = 3;
    while (abs(value-light.Value()) > 0.1 && override != 1) {
        value = light.Value();
        Sleep(100);
    }

    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);


    // repositioning if robot missed light
    if (override == 1)
    {
        driveForward(0.5, -100);
    };

    // display light color and value on Proteus
    if (light.Value() < 0.9)
    {
        LCD.SetBackgroundColor(RED);
        LCD.Write(light.Value());
        LCD.Clear();
        frm.SetPercent(0);
        flm.SetPercent(0);
        brm.SetPercent(0);
        blm.SetPercent(0);

        button = 0;
    }
    else
    {
    LCD.SetBackgroundColor(BLUE);
    LCD.Write(light.Value());

    LCD.Clear();
    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);

    button = 1;
    }

    Sleep(0.5);

    LCD.WriteLine(button);

    // code to hit the correct button
    if (button == 0)
    {
        LCD.WriteLine("RED");
        driveForward(0.4, -100);
        turn('R', 0.54, 100, -100);
        driveForward(0.63, 100);
        turn('L', 0.41, 100, -100);
        driveForward(0.5, 100);
    }
    else
    {
        LCD.WriteLine("BLUE");
        driveForward(0.4, -100);
        turn('R', 0.54, 100, -100);
        driveForward(0.23, 100);
        turn('L', 0.41, 100, -100);
        driveForward(0.5, 100);
    }

    // code to back up from the button
    driveForward(0.2, -100);

    // turn robot rear towards passport mechanism
    turn('L', 0.8, 100, -100);

    // move passport servo all the way left to ground
    s2.SetDegree(150);
    Sleep(0.5);

    // drive towards passport mechanism
    if (button == 0)
    {
        driveForward(0.5, -100);
    }
    else
    {
        driveForward(1, -100);
    }
}
void passport()
{
    driveForward(0.22, 50);
    // flip passport mechanism up
    s2.SetDegree(60);
    Sleep(0.5);
    // servo back to ground
    s2.SetDegree(150);
    Sleep(0.5);
}

void driveback()
{
    // path to drive from platform back to start area
    turn('R', 0.8, 100, -100);
    driveForward(0.15, -50);
    s2.SetDegree(80);
    Sleep(0.5);
    turn('R', 1.0, -80, -25);
    driveForward(1.2, -100);
    turn('L', 1.0, -80, -25);
    driveForward(1.0, -100);
    turn('L', 0.7, -80, -25);
    driveForward(0.3, -100);
    turn('R', 0.7, -80, -25);
    // press final button
    driveForward(0.5, -100);
}

// function to drive forward
void driveForward(float time, int percent)
{
    // set all motors at desired percent
    frm.SetPercent(percent);
    flm.SetPercent(percent);
    brm.SetPercent(percent);
    blm.SetPercent(percent);
    // sleep for desired time
    Sleep(time);
    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);
}

void turn(char direction, float time, int dominant_motor_percent, int nondom_motor_percent)
{

    // set motors to desired percent based on desired direction
    if (direction == 'L')
    {
        frm.SetPercent(dominant_motor_percent);
        flm.SetPercent(nondom_motor_percent);
        brm.SetPercent(dominant_motor_percent);
        blm.SetPercent(nondom_motor_percent);
    }
    else if (direction == 'R')
    {
        frm.SetPercent(nondom_motor_percent);
        flm.SetPercent(dominant_motor_percent);
        brm.SetPercent(nondom_motor_percent);
        blm.SetPercent(dominant_motor_percent);
    }
    // sleep for desired time
    Sleep(time);
    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);
}

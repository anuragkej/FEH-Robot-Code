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

void driveForward(float time, int percent);
void turn(char direction, float time, int dominant_motor_percent, int nondom_motor_percent);
// declare motor on motor port 0, set maximum voltage to 9.0 V
// right motor is inversed (i.e, driving forward, RM would be at a negative percent)

FEHMotor blm(FEHMotor::Motor1, 7.0);
FEHMotor brm(FEHMotor::Motor3, 7.0);
FEHMotor flm(FEHMotor::Motor0, 7.0);
FEHMotor frm(FEHMotor::Motor2, 7.0);

int main()
{
    RCS.InitializeTouchMenu("E6aMLIy03");

    FEHServo s1(FEHServo::Servo6);
    FEHServo s2(FEHServo::Servo7);

    AnalogInputPin light(FEHIO::P2_7);

    while (light.Value() > 0.9)
        ;

    // reset servo motors
    s1.SetDegree(180);
    s2.SetDegree(90);

    driveForward(0.4, -40);

    // forward out of start
    driveForward(0.7, 100);

    // slight left
    turn('L', 0.5, 100, 25);

    // horziontally towards ramp
    driveForward(0.9, 100);

    // 90 degree turn
    turn('R', 0.48, 100, -100);

    // up ramp
    driveForward(2.0, 100);

    turn('R', 0.6, 100, -100);

    driveForward(1.2, 100);

    s2.SetDegree(40);

    // turn('R', 0.7, 80, 25);
    // driveForward(0.3, 100);
    // turn('L', 0.7, 80, 25);
    // driveForward(1.0, 100);
    // turn('L', 1.0, 80, 25);
    // driveForward(1.2, 100);
    // turn('R', 1.0, 80, 25);
    // Sleep(0.5);
    // driveForward(0.15, 50);
    // turn('L', 0.8, 100, -100);
    // s2.SetDegree(150);
    // Sleep(0.5);
    // driveForward(0.5, -100);
    // driveForward(0.15, 50);
    // s2.SetDegree(60);
    // Sleep(0.5);
    // s2.SetDegree(150);
}
void driveForward(float time, int percent)
{
    /*float adjustedpercent;
    adjustedpercent = (11.5 / Battery.Voltage()) * percent;*/
    frm.SetPercent(percent);
    flm.SetPercent(percent);
    brm.SetPercent(percent);
    blm.SetPercent(percent);
    Sleep(time);
    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);
}

void turn(char direction, float time, int dominant_motor_percent, int nondom_motor_percent)
{

    /*float adj_dominant_motor_percent = (11.5 / Battery.Voltage()) * dominant_motor_percent;
    float adj_nondom_motor_percent = (11.5 / Battery.Voltage()) * nondom_motor_percent;*/

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
    Sleep(time);
    frm.SetPercent(0);
    flm.SetPercent(0);
    brm.SetPercent(0);
    blm.SetPercent(0);
}

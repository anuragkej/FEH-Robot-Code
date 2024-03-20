#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>

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
    float button = 2.5;
    // // DigitalInputPin fl(FEHIO::P0_0);
    // // DigitalInputPin bl(FEHIO::P0_1);
    // // DigitalInputPin fr(FEHIO::P3_7);
    // // DigitalInputPin br(FEHIO::P3_6);

    AnalogInputPin light(FEHIO::P2_7);

    while (light.Value() > 0.9)
        ;

    // forward out of start
    driveForward(0.6, 100);

    // slight left
    turn('L', 0.5, 100, 25);

    // horziontally towrads ramp
    driveForward(0.9, 100);

    // 90 degree turn
    turn('R', 0.565, 100, -100);

    // up ramp
    driveForward(2.0, 100);

    // slight right
    turn('R', 0.26, 100, -50);

    /*// drive to boarding pass station
    driveForward(1.2, 100);

    // slight left
    turn('L', 0.15, 100, -50);*/

    frm.SetPercent(25);
    flm.SetPercent(25);
    brm.SetPercent(25);
    blm.SetPercent(25);

    while (light.Value() > 2.0)
        ;

    float t = TimeNow();

    while (light.Value() < 1.7)
    {

        frm.SetPercent(0);
        flm.SetPercent(0);
        brm.SetPercent(0);
        blm.SetPercent(0);

        button = 1.5;

        if (TimeNow() - t > 2.0)
        {
            break;
        }
    }

    t = TimeNow();

    while (light.Value() < 1.97)
    {
        frm.SetPercent(0);
        flm.SetPercent(0);
        brm.SetPercent(0);
        blm.SetPercent(0);

        button = 1.5;

        if (TimeNow() - t > 2.0)
        {
            break;
        }
    }

    Sleep(0.5);

    LCD.WriteLine(button);

    if (button < 1.7)
    {
        LCD.WriteLine("RED");
        driveForward(0.4, -100);
        turn('R', 0.41, 100, -100);
        driveForward(1.05, 100);
        turn('L', 0.54, 100, -100);
        driveForward(0.5, 100);
    }
    else
    {
        LCD.WriteLine("BLUE");
        driveForward(0.4, -100);
        turn('R', 0.41, 100, -100);
        driveForward(0.63, 100);
        turn('L', 0.54, 100, -100);
        driveForward(0.5, 100);
    }

    // back up
    driveForward(1.5, -100);

    if (button < 1.7)
    {
        // wide right
        turn('R', 0.55, 100, -100);
        // drive towards ramp
        driveForward(0.4, 100);
        turn('R', 0.82, 100, -100);
    }
    else
    {
        // wide right
        turn('R', 0.55, 100, -100);
        // drive towards ramp
        driveForward(0.98, 100);
        turn('R', 0.82, 100, -100);
    }

    // go down ramp
    driveForward(2.3, 100);
}

void driveForward(float time, int percent)
{
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
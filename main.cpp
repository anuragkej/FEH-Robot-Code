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
    driveForward(1.1, 100);

    // 90 degree turn
    turn('R', 0.6, 100, -100);

    // up ramp
    driveForward(2.0, 100);

    // slight right
    turn('R', 0.45, 100, -50);

    // drive to boarding pass station
    driveForward(1.2, 100);

    // slight left
    turn('L', 0.45, 100, -50);

    // drive to boarding pass station
    driveForward(0.55, 100);

    // back up
    driveForward(1.55, -100);

    // wide right
    turn('R', 2.25, 100, -25);

    // drive towards ramp
    driveForward(0.6, 100);

    // slight right to readjust down ramp
    turn('R', 0.2, 100, -100);

    // go down ramp
    driveForward(2.0, 100);
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

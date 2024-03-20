#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHRCS.h>

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

    // Initialize the RCS
    RCS.InitializeTouchMenu("B7p93noDy");

    // Get correct lever from the RCS
    int correctLever = RCS.GetCorrectLever();

    AnalogInputPin light(FEHIO::P2_7);

    while (light.Value() > 0.9)
        ;

    // forward out of start
    driveForward(0.8, 100);

    // slight left
    turn('L', 0.7, 100, 25);

    // Check which lever to flip and perform some action
    if (correctLever == 0)
    {
        // Perform actions to flip left lever

        // horziontally towrads ramp
        driveForward(0.15, 100);

        // 90 degree turn
        turn('L', 0.565, 100, -100);
    }
    else if (correctLever == 1)
    {

        // horziontally towrads ramp
        driveForward(0.5, 100);

        // 90 degree turn
        turn('L', 0.565, 100, -100);
        // Perform actions to flip middle lever
    }
    else if (correctLever == 2)
    {

        // horziontally towrads ramp
        driveForward(0.6, 100);

        // 90 degree turn
        turn('L', 0.4, 100, -100);
        // Perform actions to flip right lever
    }
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
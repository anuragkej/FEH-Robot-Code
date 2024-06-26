#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHRCS.h>

// Servo Max: 2277
// Servo Min: 500

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
    RCS.InitializeTouchMenu("E6aMLIy03");

    // Get correct lever from the RCS
    int correctLever = RCS.GetCorrectLever();

    FEHServo s1(FEHServo::Servo7);

    s1.SetMin(500);
    s1.SetMax(2277);

    AnalogInputPin light(FEHIO::P2_7);

    while (light.Value() > 0.9)
        ;

    // forward out of start
    driveForward(0.7, 100);

    Sleep(0.25);

    // slight left
    turn('L', 0.9, 100, 25);

    s1.SetDegree(110);

    // Check which lever to flip and perform some action
    if (correctLever == 0)
    {
        // Perform actions to flip left lever

        // horziontally towrads ramp
        driveForward(0.26, -100);

        /*// 90 degree turn
        turn('L', 0.75, 100, -100);

        driveForward(0.2, 100);*/

        Sleep(0.5);

        s1.SetDegree(100);

        Sleep(5.0);

        s1.SetDegree(135);
    }
    else if (correctLever == 1)
    {

        // horziontally towards ramp
        driveForward(0.0625, 100);

        /*// 90 degree turn
        turn('L', 0.75, 100, -100);

        driveForward(0.2, 100);*/

        Sleep(0.5);

        s1.SetDegree(100);

        Sleep(5.0);

        s1.SetDegree(135);
    }
    else if (correctLever == 2)
    {
        // horziontally towards ramp
        driveForward(0.33, 100);

        /*// 90 degree turn
        turn('L', 0.75, 100, -100);

        driveForward(0.2, 100);*/

        Sleep(0.5);

        s1.SetDegree(100);

        Sleep(5.0);

        s1.SetDegree(135);
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

#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>

void driveForward(double time, int percent);
void turn(int degrees);
// declare motor on motor port 0, set maximum voltage to 9.0 V
// right motor is inversed (i.e, driving forward, RM would be at a negative percent)

FEHMotor leftM(FEHMotor::Motor2, 9.0);
FEHMotor rightM(FEHMotor::Motor1, 9.0);

int main()
{
    // // DigitalInputPin fl(FEHIO::P0_0);
    // // DigitalInputPin bl(FEHIO::P0_1);
    // // DigitalInputPin fr(FEHIO::P3_7);
    // // DigitalInputPin br(FEHIO::P3_6);

    AnalogInputPin light(FEHIO::P2_7);

    // while (bl.Value())
    //     ;

    // left_motor.SetPercent(39);
    // right_motor.SetPercent(-39);

    // while (fl.Value() || fr.Value())
    //     ;

    // left_motor.Stop();
    // right_motor.Stop();

    // Sleep(2.0);

    // right_motor.SetPercent(39);

    // while (br.Value() || bl.Value())
    //     ;

    // right_motor.Stop();

    // Sleep(2.0);

    // left_motor.SetPercent(39);
    // right_motor.SetPercent(-39);

    // while (fl.Value() || fr.Value())
    //     ;

    // left_motor.Stop();
    // right_motor.Stop();

    // Sleep(2.0);

    // left_motor.SetPercent(-39);

    // while (br.Value() || bl.Value())
    //     ;

    // left_motor.Stop();

    // Sleep(2.0);

    // left_motor.SetPercent(39);
    // right_motor.SetPercent(-39);

    // while (fl.Value() || fr.Value())
    //     ;

    // left_motor.Stop();
    // right_motor.Stop();
    while (1)
    {
        float lightVal = light.Value();
        if (lightVal > 0.01 && lightVal < 0.5)
        {
            turn(45);
            driveForward(8.0, 40);
        }
    }
}

void driveForward(double time, int percent)
{
    leftM.SetPercent(percent);
    rightM.SetPercent(-percent);
    Sleep(time);
    leftM.SetPercent(10);
    rightM.SetPercent(10);
}

void turn(int degrees)
{
    if (degrees > 0)
    {
        leftM.SetPercent(-20);
        rightM.SetPercent(20);
        Sleep(0.03 * degrees);
    }
    else
    {
        leftM.SetPercent(20);
        rightM.SetPercent(-20);
        Sleep(0.03 * degrees);
    }
    leftM.SetPercent(0);
    rightM.SetPercent(0);
}

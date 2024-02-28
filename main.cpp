#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>

// declare motor on motor port 0, set maximum voltage to 9.0 V
// right motor is inversed (i.e, driving forward, RM would be at a negative percent)

FEHMotor blm(FEHMotor::Motor2, 9.0);
FEHMotor brm(FEHMotor::Motor3, 9.0);
FEHMotor flm(FEHMotor::Motor0, 9.0);
FEHMotor frm(FEHMotor::Motor1, 9.0);

int main()
{
    // // DigitalInputPin fl(FEHIO::P0_0);
    // // DigitalInputPin bl(FEHIO::P0_1);
    // // DigitalInputPin fr(FEHIO::P3_7);
    // // DigitalInputPin br(FEHIO::P3_6);

    AnalogInputPin light(FEHIO::P2_8);

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

    float lightVal = light.value();
    if (lightVal > 0.01 && lightVal < 0.5)
    {
        driveForward(8.0, 40);
    }
}

driveForward(double time, int percent)
{
    frm.SetPercent(percent);
    flm.SetPercent(-percent);
    Sleep(time);
    frm.SetPercent(10);
    flm.SetPercent(10);
}

turn(int degrees)
{
    if (degrees > 0)
    {
        left_motor.SetPercent(20);
        right_motor.SetPercent(20);
        Sleep(0.03 * degrees);
    }
    else
    {
        left_motor.SetPercent(-20);
        right_motor.SetPercent(-20);
        Sleep(0.03 * degrees);
    }
    left_motor.SetPercent(0);
    right_motor.SetPercent(0);
}

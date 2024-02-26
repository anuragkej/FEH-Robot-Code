#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
// declare motor on motor port 0, set maximum voltage to 9.0 V
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
FEHMotor right_motor(FEHMotor::Motor3, 9.0);

int main()
{
    DigitalInputPin fl(FEHIO::P0_0);
    DigitalInputPin bl(FEHIO::P0_1);
    DigitalInputPin fr(FEHIO::P3_7);
    DigitalInputPin br(FEHIO::P3_6);

    while (bl.Value())
        ;

    left_motor.SetPercent(39);
    right_motor.SetPercent(-39);

    while (fl.Value() || fr.Value())
        ;

    left_motor.Stop();
    right_motor.Stop();

    Sleep(2.0);

    right_motor.SetPercent(39);

    while (br.Value() || bl.Value())
        ;

    right_motor.Stop();

    Sleep(2.0);

    left_motor.SetPercent(39);
    right_motor.SetPercent(-39);

    while (fl.Value() || fr.Value())
        ;

    left_motor.Stop();
    right_motor.Stop();

    Sleep(2.0);

    left_motor.SetPercent(-39);

    while (br.Value() || bl.Value())
        ;

    left_motor.Stop();

    Sleep(2.0);

    left_motor.SetPercent(39);
    right_motor.SetPercent(-39);

    while (fl.Value() || fr.Value())
        ;

    left_motor.Stop();
    right_motor.Stop();
}

drive_forward(double time, int percent)
{
    left_motor.SetPercent(percent);
    right_motor.SetPercent(-percent);
    Sleep(time);
    left_motor.SetPercent(0);
    right_motor.SetPercent(0);
}
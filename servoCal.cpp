#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHRCS.h>

int main()
{

    FEHServo s1(FEHServo::Servo7);

    s1.TouchCalibrate();
}
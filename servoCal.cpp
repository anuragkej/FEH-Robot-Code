#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHRCS.h>

// Servo Max: 2277
// Servo Min: 500

int main()
{

    FEHServo s1(FEHServo::Servo7);

    s1.SetMin(500);
    s1.SetMax(2277);

    s1.SetDegree(0);
    Sleep(0.5);
    s1.SetDegree(180);
}
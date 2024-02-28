#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>

int main()
{
    AnalogInputPin light(FEHIO::P2_7);
    while (1)
    {
        LCD.Write(light.Value());
        Sleep(100);
        LCD.Clear();
    }
}
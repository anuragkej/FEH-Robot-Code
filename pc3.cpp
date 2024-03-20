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
}
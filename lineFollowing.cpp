#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHServo.h>

enum LineStates
{
    MIDDLE,
    RIGHT,
    LEFT
};

int main()
{
    AnalogInputPin light(FEHIO::P2_7);
    AnalogInputPin rS(FEHIO::P2_4);
    AnalogInputPin mS(FEHIO::P2_5);
    AnalogInputPin lS(FEHIO::P2_6);

    FEHMotor leftM(FEHMotor::Motor0, 9.0);
    FEHMotor rightM(FEHMotor::Motor1, 9.0);

    int state = MIDDLE; // Set the initial state
    while (true)
    { // I will follow this line forever!
        switch (state)
        {
        // If I am in the middle of the line...
        case MIDDLE:
            // Set motor powers for driving straight
            /* Drive */
            leftM.SetPercent(25);
            rightM.SetPercent(25);
            if (rS.Value() > 2.2)
            {
                state = RIGHT; // update a new state
            }

            /* Code for if left sensor is on the line */
            if (lS.Value() > 2.0)
            {
                state = LEFT; // update a new state

                break;

            // If the right sensor is on the line...
            case RIGHT:
                // Set motor powers for right turn
                /* Drive */
                leftM.SetPercent(25);
                rightM.SetPercent(0);
                if (rS.Value() < 2.2)
                {
                    state = MIDDLE;
                }
                break;

            // If the left sensor is on the line...
            case LEFT:
                /* Mirror operation of RIGHT state */
                // Set motor powers for right turn
                /* Drive */
                leftM.SetPercent(0);
                rightM.SetPercent(25);
                if (lS.Value() < 2.0)
                {
                    state = MIDDLE;
                }
                break;

            default: // Error. Something is very wrong.
                break;
            }
            Sleep(0.02);
        }
    }
}

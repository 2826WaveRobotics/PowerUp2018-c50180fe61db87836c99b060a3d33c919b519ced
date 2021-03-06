// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ctre/Phoenix.h"


#include "Kirby.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Kirby::Kirby() : frc::Subsystem("Kirby") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    kirbyRight = RobotMap::kirbyKirbyRight;
    kirbyLeft = RobotMap::kirbyKirbyLeft;
    kirbyFull = RobotMap::kirbyKirbyFull;
    kirbyKlaw = RobotMap::kirbyKirbyKlaw;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Kirby::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Kirby::Periodic() {
    // Put code here to be run every loop

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//Stop intake
void Kirby::KirbyStop()
{
	kirbyRight.get()->Set(0.0);
	kirbyLeft.get()->Set(0.0);
}

//Set intake to a speed
void Kirby::SetKirby(double speed)
{
	kirbyRight.get()->Set(speed);
	kirbyLeft.get()->Set(-speed);
}

//Set intake claw
void Kirby::SetKirbyKlaw(bool on){
	kirbyKlaw.get()->Set(on);

}

//Check if intake sensor is tripped
bool Kirby::GetSwitch(){
	return kirbyFull.get()->Get();
}

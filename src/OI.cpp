// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/Z_Command.h"
#include "Commands/Z_CommandGroup.h"
#include "Commands/Z_SetpointCommand.h"
#include "Commands/Z_TimedCommand.h"
#include "Commands/DeployIronCross.h"
#include "Commands/DeployTRexArms.h"
#include "Commands/Shift.h"
#include "Commands/SetKirbyKlaw.h"
#include "Commands/SetElbow.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    operatorJS.reset(new frc::Joystick(1));
    
    driver.reset(new frc::Joystick(0));

    

    // SmartDashboard Buttons
    //frc::SmartDashboard::PutData("Z_TimedCommand", new Z_TimedCommand());
    frc::SmartDashboard::PutData("Z_CommandGroup", new Z_CommandGroup());
    //frc::SmartDashboard::PutData("Z_SetpointCommand", new Z_SetpointCommand());
    frc::SmartDashboard::PutData("Z_Command", new Z_Command());


	operatorStart.reset(new JoystickButton(operatorJS.get(), 8));
	operatorSelect.reset(new JoystickButton(operatorJS.get(), 7));
	operatorRightBumper.reset(new JoystickButton(operatorJS.get(), 6));
	operatorLeftBumper.reset(new JoystickButton(operatorJS.get(), 5));
	operatorY.reset(new JoystickButton(operatorJS.get(), 4));
	operatorX.reset(new JoystickButton(operatorJS.get(), 3));
	operatorB.reset(new JoystickButton(operatorJS.get(), 2));
	operatorA.reset(new JoystickButton(operatorJS.get(), 1));

	driverStart.reset(new JoystickButton(driver.get(), 8));
	driverSelect.reset(new JoystickButton(driver.get(), 7));
	driverRightBumper.reset(new JoystickButton(driver.get(), 6));
	driverLeftBumper.reset(new JoystickButton(driver.get(), 5));
	driverY.reset(new JoystickButton(driver.get(), 4));
	driverX.reset(new JoystickButton(driver.get(), 3));
	driverB.reset(new JoystickButton(driver.get(), 2));
	driverA.reset(new JoystickButton(driver.get(), 1));

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriver() {
   return driver;
}

std::shared_ptr<frc::Joystick> OI::getOperatorJS() {
   return operatorJS;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

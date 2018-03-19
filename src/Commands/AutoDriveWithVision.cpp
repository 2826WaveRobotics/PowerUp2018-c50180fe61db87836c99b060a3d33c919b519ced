// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoDriveWithVision.h"
#include <cmath>
#include <iostream>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveWithVision::AutoDriveWithVision(double power, double heading, double timeout): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::drivePID.get());

	m_power = power;
	m_heading = heading;

	if(timeout != 0)
	{
		SetTimeout(timeout);
	}


    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveWithVision::Initialize() {
	Robot::drivePID->SetPIDs(c_straightP, c_straightI, c_straightD);
	//Robot::drivePID.get()->ZeroYaw();
	Robot::drivePID.get()->SetDirection(m_heading);
	Robot::drivePID.get()->UpdateLimelight();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveWithVision::Execute() {
	Robot::drivePID->AdjustWithVision(m_power, m_heading);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveWithVision::IsFinished() {
	if(Robot::drivePID.get()->IsTargetFound()){
		return true;
	}
	else if(IsTimedOut()){
		return true;
	}
	else{
		return false;
	}
}

// Called once after isFinished returns true
void AutoDriveWithVision::End() {
	Robot::drivePID->ArcadeDrive(0, 0);
	Robot::drivePID.get()->ZeroEncoders();
	//Robot::drivePID.get()->ZeroYaw();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveWithVision::Interrupted() {

}
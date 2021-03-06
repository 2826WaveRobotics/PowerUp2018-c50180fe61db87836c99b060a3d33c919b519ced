// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "SetElevator.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

SetElevator::SetElevator(double position): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

	m_position = position;
	m_currentPosition = 0;

}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void SetElevator::Initialize() {
	Robot::elevator.get()->SetHeight(m_position);
}

// Called repeatedly when this Command is scheduled to run
void SetElevator::Execute() {
	m_currentPosition = Robot::elevator.get()->GetHeight();
}

// Make this return true when this Command no longer needs to run execute()
bool SetElevator::IsFinished() {
	if((m_currentPosition > (m_position-5)) && (m_currentPosition < (m_position+5))){
		return true;
	}
	else{
		return false;
	}
}

// Called once after isFinished returns true
void SetElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevator::Interrupted() {

}

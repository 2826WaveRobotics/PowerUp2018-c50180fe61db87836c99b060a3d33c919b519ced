// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoDrive.h"
#include <cmath>
#include <iostream>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDrive::AutoDrive(double distance, double power, double heading, bool stopWithCube): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::drivePID.get());

	m_distance = distance;
	m_power = power;
	m_distanceTraveled = 0;
	m_stopWithCube = stopWithCube;
	m_heading = heading;

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
	Robot::drivePID->SetPIDs(c_straightP, c_straightI, c_straightD);
	Robot::drivePID.get()->ZeroEncoders();
	//Robot::drivePID.get()->ZeroYaw();
	Robot::elevator.get()->SetElevatorSpeed(0);
	Robot::drivePID.get()->SetDirection(m_heading);
//	Robot::drivePID->DriveStraight(1, 0);
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {

	Robot::drivePID->DriveStraight(m_power, m_heading);
	double rightDist = Robot::drivePID->GetRightEncoder();
	double leftDist = Robot::drivePID->GetLeftEncoder()*(-1);

	if(rightDist < 0 ){
		m_distanceTraveled =  (rightDist+leftDist)/2*(-1);
	}
	else if (rightDist > 0){
		m_distanceTraveled = ((rightDist+leftDist)/2)*(-1);
	}
	else{
		m_distanceTraveled = 0;
	}


	std::cout << "Right: " << rightDist << " Left:" << leftDist <<
			" Distance Traveled: " << m_distanceTraveled <<
			" Set Distance: " << m_distance
			<< " Gyro: " << Robot::drivePID.get()->GetYaw() << std::endl;

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	if(m_stopWithCube){
		if(Robot::kirby.get()->GetSwitch()){
			return true;
		}
	}
	else{
		if((m_power > 0) && (m_distanceTraveled > m_distance)){
			Robot::drivePID->SetSidePower(-1,1);
			return true;
		}
		else if((m_power < 0) && (m_distanceTraveled < m_distance)){
			Robot::drivePID->SetSidePower(-1,1);
			return true;
		}

		else if(m_power == 0){
			Robot::drivePID->SetSidePower(-1,1);
			return true;
		}
		else{
			return false;
		}
	}

}

// Called once after isFinished returns true
void AutoDrive::End() {
	Robot::drivePID->ArcadeDrive(0, 0);
	Robot::drivePID.get()->ZeroEncoders();
	//Robot::drivePID.get()->ZeroYaw();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {

}

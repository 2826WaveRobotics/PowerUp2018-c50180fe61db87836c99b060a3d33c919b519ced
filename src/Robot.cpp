// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Commands/AutoCurve.h"
#include "Commands/AutoDrive.h"
#include "Commands/TestCurve.h"
#include "Commands/AutoRotate.h"
#include "Commands/SetElbow.h"
#include "Commands/Z_Command.h"
#include "Commands/SetKirbyKlaw.h"

#include <iostream>
#include "Commands/LeftSwitchExchangeAuto.h"
#include "Commands/RightSwitchExchangeAuto.h"
#include "Commands/LeftSwitchSideAuto.h"
#include "Commands/RightSwitchSideAuto.h"
#include "Commands/RightSwitchTimedAuto.h"
#include "Commands/LeftSwitchTimedAuto.h"
#include "Commands/LeftScaleAuto.h"
#include "Commands/RightScaleAuto.h"
#include "Commands/AutoDriveTimed.h"
#include "Commands/AutoDistance.h"

using namespace nt;

namespace
{
  enum
  {
    p_doNothing= 0,
    p_driveStraight,
    p_switchCube,
    p_scale,
    p_switchTimed
  };
}


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drive> Robot::drive;
std::shared_ptr<Kirby> Robot::kirby;
std::shared_ptr<IronCross> Robot::ironCross;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Elbow> Robot::elbow;
std::shared_ptr<DrivePID> Robot::drivePID;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<CompressorSubsystem> Robot::compressorSubsystem;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();

	//Initialize subsystems
    kirby.reset(new Kirby());
    ironCross.reset(new IronCross());
    elevator.reset(new Elevator());
    elbow.reset(new Elbow());
    drivePID.reset(new DrivePID());
    compressorSubsystem.reset(new CompressorSubsystem());

   	m_gyro = new AHRS(SPI::Port::kMXP, 100);

	oi.reset(new OI());

	//Use preferences table to select robot location and auto mode
	prefs = Preferences::GetInstance();
	//0 = center, 1 = left, 2 = right
	m_location = prefs->GetDouble("Location", 0.0);
	m_autoType = prefs->GetDouble("Auto Type",  p_doNothing);

}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	compressorSubsystem->StopCompressor();
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	//Misc printouts
//	std::cout << " Arm Encoder : " << elbow.get()->GetAngle() << "  Elevator Encoder: "<< elevator.get()->GetHeight() << " Drive Right:  "
//			<< drivePID.get()->GetRightEncoder() << "  Drive Left:  " << drivePID.get()->GetLeftEncoder() << "  Arm Sensor:  "
//			<< kirby.get()->GetSwitch() << "  Elevator Sensor:  " << elevator.get()->IsSensorTripped() << std::endl;

//	std::cout << "Elevator Encoder: " << elevator.get()->GetHeight() <<  "  Elevator Sensor:  " << elevator.get()->IsSensorTripped()
//			<< "  Raw Elevator Sensor: " << RobotMap::elevatorElevatorZero.get()->Get() << std::endl;

	//std::cout << " Gyro: " << drivePID.get()->GetYaw() << std::endl;;

	Wait(.001);
}

void Robot::AutonomousInit() {
	std::string gameData;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");

	//Select auto type based on preferences table and game data
	if(m_autoType == p_doNothing){
	     autonomousCommand = new Z_Command();
	}
	else if(m_autoType == p_driveStraight){
	    autonomousCommand = new AutoDistance(-50, -0.5, 0, 4);
	}

	else if(gameData[0] == 'L') {
		if (gameData[1] == 'L') //LLL
		{
			if(m_autoType == p_switchCube){
				table->PutNumber("pipeline", 1);
				autonomousCommand = new LeftSwitchExchangeAuto();
			}

			if((m_location == 1) &&(m_autoType == p_scale)){
				autonomousCommand = new LeftScaleAuto ();
			}
			else if((m_location == 2) &&(m_autoType == p_scale)){
				autonomousCommand = new AutoDistance(-50, -0.5, 0, 4);
			}

			if(m_autoType == p_switchTimed){
				autonomousCommand = new LeftSwitchTimedAuto();
			}

		}
		else //LRL
		{
			if(m_autoType == p_switchCube){
				table->PutNumber("pipeline", 1);
				autonomousCommand = new LeftSwitchExchangeAuto();
			}

			if ((m_location == 1) && ( m_autoType == p_scale)){
				autonomousCommand = new LeftSwitchSideAuto();
			}
			else if((m_location == 2) && (m_autoType == p_scale)){
				autonomousCommand = new RightScaleAuto();
			}

			if(m_autoType == p_switchTimed){
				autonomousCommand = new LeftSwitchTimedAuto();
			}

		}
	}
	else if (gameData[0] == 'R'){
		if (gameData[1] == 'R') //RRR
		{
			if( m_autoType == p_switchCube ){
				table->PutNumber("pipeline", 0);
				autonomousCommand = new RightSwitchExchangeAuto ();
			}

			if((m_location == 1) &&(m_autoType == p_scale)){
				autonomousCommand = new AutoDrive(150, 0.8, 0);
			}
			else if((m_location == 2) &&( m_autoType == p_scale)){
				autonomousCommand = new RightScaleAuto();
			}

			if( m_autoType == p_switchTimed){
				autonomousCommand = new RightSwitchTimedAuto ();
			}

		}
		else //RLR
		{
			if( m_autoType == p_switchCube ){
				table->PutNumber("pipeline", 0);
				autonomousCommand = new RightSwitchExchangeAuto();
			}

			if((m_location == 1) &&( m_autoType == p_scale)){
				autonomousCommand = new LeftScaleAuto();
			}
			else if((m_location == 2) &&(m_autoType == p_scale)){
				autonomousCommand = new RightSwitchSideAuto();
			}

			if( m_autoType == p_switchTimed){
				autonomousCommand = new RightSwitchTimedAuto();
			}

		}
	}
	else
	{
		autonomousCommand = new AutoDistance(-50, -0.5, 0, 4);
	}

	if (autonomousCommand != nullptr){
		autonomousCommand->Start();
	}

	drivePID.get()->ZeroEncoders();
	drivePID.get()->ZeroYaw();
	elbow.get()->ZeroDegrees();

	compressorSubsystem->StartCompressor();

}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();

}

void Robot::TeleopInit() {

	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();

	//elbow.get()->ZeroDegrees();
	drivePID.get()->ZeroYaw();
	elevator.get()->ZeroHeight();
	compressorSubsystem->StartCompressor();
	drivePID.get()->UpdateLimelight();
	drivePID.get()->SetPIDs(-0.2, 0, 0);

}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	//Drive and Shift To Climb
	bool shiftOn  = oi.get()->getDriver()->GetRawButton(8); //Shift into climb gear
	bool shiftOff = oi.get()->getDriver()->GetRawButton(7); //Shift into drive gear
	bool isShifted = RobotMap::drivePIDShifter->Get();

	double driverY = oi.get()->getDriver()->GetRawAxis(1); //Drive forward and back
	double driverX = -(oi.get()->getDriver()->GetRawAxis(4)); //Turn
	bool visionOR = oi.get()->getDriver()->GetRawButton(5); //Drive if vision is acting up
	bool visionAlign = oi.get()->getDriver()->GetRawButton(1); //Turn to cube with vision

	if(fabs(driverY) < 0.15){
		driverY = 0;
	}
	if(fabs(driverX) < 0.15){
		driverX = 0;
	}

	if(shiftOn){
		drivePID.get()->Shift(true);
	}
	else if(shiftOff){
			drivePID.get()->Shift(false);
		}
	else if(isShifted){
		if(fabs(driverY) > 0.15){ // Only can climb by pressing joystick down
			drivePID.get()->ArcadeDrive(fabs(driverY), 0);
		}
		else{
			drivePID.get()->ArcadeDrive(0, 0);
		}
	}
	else if(visionOR){
		drivePID.get()->ArcadeDrive(driverY, driverX);
	}
	else if(visionAlign){
		drivePID.get()->DriveTurning(driverY);
		double outputX = drivePID.get()->OutputX();
		if(outputX == 0){
			oi.get()->getDriver()->SetRumble(Joystick::kLeftRumble, 0);
		}
		else if((outputX > -3) && (outputX < 3)){
			oi.get()->getDriver()->SetRumble(Joystick::kLeftRumble, 1);
		}
		else{
			oi.get()->getDriver()->SetRumble(Joystick::kLeftRumble, 0);
		}
	}
	else{
		drivePID.get()->ArcadeDrive(driverY, driverX);
		oi.get()->getDriver()->SetRumble(Joystick::kLeftRumble, 0);
	}

	//Elevator
	int trackpad = oi.get()->getOperatorJS()->GetPOV(0); //Use trackpad to set elevator positions
	//Up: 0 Right: 20  Down: 70  Left: 40

	double elevatorSpeed = (-1)*oi.get()->getOperatorJS()->GetRawAxis(5); //Control elevator position
	double elevatorHeight = elevator.get()->GetHeight();
	elevator.get()->SensorTriggered();

	std::cout << "  Height:  " << elevator.get()->GetHeight() << std::endl;

	if(trackpad != (-1)){
		if(trackpad==0){
			elevator.get()->SetHeight(0);
		}
		if(trackpad==90){
			elevator.get()->SetHeight(20);
		}
		if(trackpad==180){
			elevator.get()->SetHeight(70);
		}
		if(trackpad==270){
			elevator.get()->SetHeight(40);
		}
	}
	else if(((elevatorSpeed > -0.15) && (elevatorSpeed < 0)) || (( elevatorSpeed  < 0.15) && (elevatorSpeed > 0))){
		elevator.get()->SetElevatorSpeed(0);
	}
	else if(RobotMap::drivePIDShifter->Get()){
		elevator.get()->SetElevatorSpeed(0);
	}
	else{
		if((elevatorHeight < 71.5) && (elevatorSpeed > 0.15)){
			elevator.get()->SetElevatorSpeed(elevatorSpeed);
		}
		if((elevatorHeight > 0) && (elevatorSpeed < -0.15)){
			elevator.get()->SetElevatorSpeed(elevatorSpeed);
		}
	}

	//Elbow
	double elbowSpeed = oi.get()->getOperatorJS()->GetRawAxis(1); //Control elbow position
	bool elbowOverride = oi.get()->getOperatorJS()->GetRawButton(7); //Override software stops
	double elbowPosition = elbow.get()->GetAngle();

	bool operatorY = oi.get()->getOperatorJS()->GetRawButton(4);
	bool operatorB = oi.get()->getOperatorJS()->GetRawButton(2);
	bool operatorA = oi.get()->getOperatorJS()->GetRawButton(1);
	bool operatorX = oi.get()->getOperatorJS()->GetRawButton(3);
	//Operator Y: 0, Operator B: 140, Operator A: 160, Operator X: 20

	if(elbowOverride){
		elbow.get()->ZeroDegrees();
		if(elbowSpeed < -0.15 || elbowSpeed > 0.15){
			elbow.get()->SetElbowSpeed(elbowSpeed);
		}
		else{
			elbow.get()->SetElbowSpeed(0);
		}
	}
	else if(operatorY || operatorB || operatorA || operatorX){
		if(operatorY){
			elbow.get()->SetAngle(0);
		}
		if(operatorB){
			elbow.get()->SetAngle(125);
		}
		if(operatorA){
			elbow.get()->SetAngle(155);
		}
		if(operatorX){
			elbow.get()->SetAngle(15);
		}
	}
	else{
		if(elbowPosition < 0){
			if(elbowSpeed > 0.15){
				elbow.get()->SetElbowSpeed(elbowSpeed);
			}
			else{
				elbow.get()->SetElbowSpeed(0);
			}
		}
		else if (elbowPosition > 160){
			if(elbowSpeed < -0.15){
				elbow.get()->SetElbowSpeed(elbowSpeed);
			}
			else{
				elbow.get()->SetElbowSpeed(0);
			}
		}
		else{
			if((elbowSpeed < -0.15) || (elbowSpeed > 0.15)){
				elbow.get()->SetElbowSpeed(elbowSpeed);
			}
			else{
				elbow.get()->SetElbowSpeed(0);
			}
		}
	}

	//Kirby
	double rightTrigger = oi.get()->getOperatorJS()->GetRawAxis(2); //Intake
	double leftTrigger =  oi.get()->getOperatorJS()->GetRawAxis(3); //Outtake
	double driverLTrigger = oi.get()->getDriver()->GetRawAxis(3);

	if(rightTrigger > 0.15 && leftTrigger < 0.15){
		kirby.get()->SetKirby(-rightTrigger);
	}
	else if (driverLTrigger > 0.15){
		kirby.get()->SetKirby(driverLTrigger);
	}
	else if (rightTrigger < 0.15 && leftTrigger > 0.15){
		kirby.get()->SetKirby(leftTrigger);
	}
	else{
		kirby.get()->KirbyStop();
	}

	//Keep kirby open for climb
	bool leftBumper = oi.get()->getOperatorJS()->GetRawButton(5);
	bool xButton = oi.get()->getOperatorJS()->GetRawButton(3);

	if(leftBumper == 1){
		m_intakeLock = false;
	}

	if(m_intakeLock == true){
		kirby.get()->SetKirbyKlaw(m_intakeLock);
	}
	else if(xButton == 1){
		m_intakeLock = true;
	}
	else{
		kirby.get()->SetKirbyKlaw(leftBumper);
	}

}

START_ROBOT_CLASS(Robot);


#include "DrivePID.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <iostream>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

namespace{
 const int c_CPR = 256;
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
DrivePID::DrivePID() : PIDSubsystem("DrivePID", c_straightP, c_straightI, c_straightD) {
    SetAbsoluteTolerance(0.2);
    //GetPIDController()->SetContinuous(false);
    //frc::LiveWindow::GetInstance()->AddActuator("DrivePID", "PIDSubsystem Controller", GetPIDController());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    left1 = RobotMap::drivePIDLeft1;
    left2 = RobotMap::drivePIDLeft2;
    left3 = RobotMap::drivePIDLeft3;
    leftDriveGroup = RobotMap::drivePIDLeftDriveGroup;
    right1 = RobotMap::drivePIDRight1;
    right2 = RobotMap::drivePIDRight2;
    right3 = RobotMap::drivePIDRight3;
    rightDriveGroup = RobotMap::drivePIDRightDriveGroup;
    diffDrive = RobotMap::drivePIDDiffDrive;
//    leftEncoder = RobotMap::drivePIDLeftEncoder;
//    rightEncoder = RobotMap::drivePIDRightEncoder;
    shifter = RobotMap::drivePIDShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    right1->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 50);
    right1->ConfigPeakOutputReverse(-100, 50);
    right1->ConfigPeakOutputForward(100, 50);
    right1->SetSafetyEnabled(false);
    right1->SetStatusFramePeriod(Status_2_Feedback0_, 10, 20);

    diffDrive->SetSafetyEnabled(false);

    right2->SetSafetyEnabled(false);
    right3->SetSafetyEnabled(false);

    left1->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 50);
    left1->ConfigPeakOutputReverse(-100, 50);
    left1->ConfigPeakOutputForward(100, 50);
    left1->SetSafetyEnabled(false);
    left1->SetStatusFramePeriod(Status_2_Feedback0_, 10, 20);

    left2->SetSafetyEnabled(false);
    left3->SetSafetyEnabled(false);

    gyro = new AHRS(SPI::Port::kMXP, 100);

    GetPIDController()->SetContinuous(true);
    GetPIDController()->SetInputRange(-180, 180);
    GetPIDController()->SetOutputRange(-1, 1);
    GetPIDController()->SetAbsoluteTolerance(.5);

    // Use these to get going:
    // SetSetpoint() -  Sets where the PID controller should move the system
    //                  to
    // Enable() - Enables the PID controller.

    GetPIDController()->Disable();
}

double DrivePID::ReturnPIDInput() {
    // Return your input value for the PID loop
    return GetYaw();
}

void DrivePID::UsePIDOutput(double output) {
    // Use output to drive your system, like a motor

    //rightDriveGroup->PIDWrite(output);
    //leftDriveGroup->PIDWrite(output);

}

double DrivePID::GetPIDOutput(){
	return GetPIDController()->Get();
}

void DrivePID::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}

void DrivePID::ArcadeDrive(double forward, double turn) {
	GetPIDController()->Disable();
	diffDrive.get()->ArcadeDrive(forward, turn);

}

void DrivePID::SetSidePower(double left, double right){
	diffDrive.get()->TankDrive(left, right);
}

void DrivePID::DriveCurve(double power, double heading) {
	SetDirection(heading);
	double correction = GetPIDController()->Get();

	std::cout << "Correction: " << correction << std::endl;
	if(heading > 0){
		diffDrive.get()->CurvatureDrive(power-correction, heading, false);
	}
	else if(heading < 0){
		diffDrive.get()->CurvatureDrive(power+correction, heading, false);
	}
	else{
		diffDrive.get()->CurvatureDrive(power-correction, heading, false);
	}
}

void DrivePID::DriveStraight(double power, double heading) {

	SetDirection(heading);
	double correction = GetPIDOutput();

	std::cout << "Correction: " << correction << std::endl;
	if(power < 0){
		if(heading > 0){
			diffDrive.get()->TankDrive(power-correction, power);
		}
		else if(heading < 0){
			diffDrive.get()->TankDrive(power, power+correction);
		}
		else{
			diffDrive.get()->TankDrive(power, power);
		}
	}
	else{
		if(heading > 0){
			diffDrive.get()->TankDrive(power, power+correction);
			std::cout << " Positive power and heading:  " << power << std::endl;
		}
		else if(heading < 0){
			diffDrive.get()->TankDrive(power-correction, power);
		}
		else{
			diffDrive.get()->TankDrive(power, power);
		}
	}

}
void DrivePID::Rotate(double move, double rotate, double heading) {

	double angle = fabs(GetYaw());
	double correction;
	if(GetPIDOutput() == 0){
		correction = 0;
	}
	else if (GetPIDOutput() > 0){
		correction = 1-GetPIDOutput();
	}
	else{
		correction = -1-GetPIDOutput();
	}

	if((heading > 70) && (fabs(angle-heading) > 30)){
		correction = correction*1.4;
	}


	std::cout << " PID Output: " << GetPIDController()->Get() <<  " Correction: " << correction << std::endl;
	if(correction > 1.00){
		correction = 1.00;
	}
	else if(correction < -1.00){
		correction = -1.00;
	}
	//std::cout << "Correction: " << correction << std::endl;
	SetSidePower(correction, -correction);
}

void DrivePID::Shift(bool state) {
	shifter.get()->Set(state);
	std::cout << " ---------------------DRIVE SHIFT _______________________   " << state<<  std::endl;

}

double DrivePID::GetRightEncoder() {
	double encoderCount = right1->GetSensorCollection().GetQuadraturePosition();
	double distance = encoderCount/c_CPR*6.05*3.1415/4;

	return distance;
}

double DrivePID::GetLeftEncoder() {
	double encoderCount = left1->GetSensorCollection().GetQuadraturePosition();
	double distance = encoderCount/c_CPR*6.05*3.1415/4;

	return distance;
}

void DrivePID::ZeroEncoders(){
	right1->GetSensorCollection().SetQuadraturePosition(0, 50);
	left1->GetSensorCollection().SetQuadraturePosition(0, 50);
}

float DrivePID::GetYaw(){
		return gyro->GetYaw();
}

void DrivePID::ZeroYaw(){
	gyro->ZeroYaw();
}

void DrivePID::SetPIDs(double kP, double kI, double kD) {
	GetPIDController()->SetPID(kP, kI, kD);
}

void DrivePID::SetDirection(double heading){
	if(GetPIDController()->GetSetpoint() != heading)
	{
		GetPIDController()->Disable();
		GetPIDController()->Reset();

		GetPIDController()->SetSetpoint(heading); //we are now facing the same way the entire time
		GetPIDController()->Enable();
	}
}

void DrivePID::UpdateLimelight(){

	std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");

	m_targetX = table->GetNumber("tx", 0);
	m_targetY = table->GetNumber("ty", 0);
	m_area = table->GetNumber("ta", 0);
	m_skew = table->GetNumber("ts", 0);

	std::cout << "x: " << m_targetX << "  y: " << m_targetY << "  a:" << m_area << "  s: " << m_skew << std::endl;
}

void DrivePID::AdjustWithVision(double power, double heading){
	UpdateLimelight();

	double newPower;
	double newHeading;


	if(m_targetX > 5){
		std::cout << " Target is too far right" << std::endl;
		newHeading = heading-m_targetX;
	}
	else if (m_targetX < -5){
		std::cout << " Target is too far left" << std::endl;
		newHeading = heading-m_targetX;
	}
	else{
		newHeading = heading;
	}

	if (m_targetY > 5){
		std::cout << "Too far away" <<std::endl;
		newPower = power+(m_targetY/100);
	}
	else if(m_targetY < -5){
		std::cout << "Too close" << std::endl;
		newPower = power-(m_targetY/100);
	}
	else{
		newPower = power;
	}

	DriveStraight(newPower, newHeading);
}

bool DrivePID::IsTargetFound(){
	UpdateLimelight();
	if((m_targetX < 5) && (m_targetX > -5) && (m_targetY < 5) && (m_targetY > -5)){
		return true;
	}
	else{
		return false;
	}
}

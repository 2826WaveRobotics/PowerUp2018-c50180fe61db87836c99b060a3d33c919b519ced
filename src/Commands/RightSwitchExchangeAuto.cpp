// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "RightSwitchExchangeAuto.h"
#include "AutoDrive.h"
#include "AutoDriveTimed.h"
#include "AutoCurve.h"
#include "SetKirby.h"
#include "WaveWait.h"
#include "AutoRotate.h"
#include "SetElbow.h"
#include "SetElevator.h"
#include "SetKirbyKlaw.h"
#include "SetKirby.h"
#include "AutoDriveWithVision.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

RightSwitchExchangeAuto::RightSwitchExchangeAuto() {

	//Drive forward to switch
	AddSequential (new AutoCurve(-0.5, 28));
	AddSequential(new SetElbow(140));
	AddParallel(new SetElevator(40));
	AddSequential(new AutoDrive(-55, -0.8, 28));

	//Prepare and place cube
	AddSequential(new AutoDriveTimed(-0.3, 0, 1));
	AddSequential(new WaveWait(0.25));
	AddSequential(new SetKirbyKlaw(true));
	AddSequential(new WaveWait(0.25));

	//Back up and drive to cube
	AddSequential(new AutoRotate(40));
	AddSequential(new SetElbow(160));
	AddSequential(new AutoDrive(20, 0.8, 40));
	AddSequential(new SetElevator(0));
	AddSequential(new WaveWait(0.25));
	AddSequential(new AutoDrive(20, 0.4, -5));
	AddSequential(new AutoRotate(0));
//	AddSequential(new AutoDrive(10, 0.4, -5));
//	AddSequential(new WaveWait(.25));
//	AddSequential(new AutoDriveWithVision(-20, -0.4, 3));
	//AddSequential(new AutoRotate(0));
//	AddParallel(new SetKirby(0.8, 0.5));
//
//	//Acquire Cube
//	AddSequential(new SetElevator(-5));
//	AddParallel(new SetKirby(0.8, 0.5));
//	AddSequential(new AutoDrive(-25, -0.8, 0, true));
//	AddParallel(new SetKirby(0.8, 0.5));
//	AddSequential(new SetKirby(0.8, 0.5));
//	AddSequential(new SetKirbyKlaw(false));
//	AddParallel(new SetKirby(0.8, 0.5));
//
//	//Drive to switch and prepare to place cube
//	AddSequential(new AutoDrive(20, 0.5, 0));
//	AddParallel(new SetElevator(20));
//	AddSequential(new AutoRotate(30));
//	AddSequential(new AutoDrive(-35, -0.8, 30));
//	//AddParallel(new SetElbow(145));
//	AddSequential(new WaveWait(0.5));
//	AddSequential(new AutoRotate(0));
//
//	//Place cube
//	AddSequential(new AutoDriveTimed(-0.3, 0, .7));
//	AddSequential(new SetKirbyKlaw(true));

 }

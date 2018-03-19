// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "RightScaleAuto.h"
#include "AutoDrive.h"
#include "AutoCurve.h"
#include "SetKirby.h"
#include "WaveWait.h"
#include "AutoRotate.h"
#include "SetElbow.h"
#include "SetKirbyKlaw.h"
#include "SetKirby.h"
#include "SetElevator.h"
#include "AutoDriveWithVision.h"
#include "AutoDriveTimed.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

RightScaleAuto::RightScaleAuto() {

	//Drive forward to scale
	AddSequential(new AutoDrive(-200, -0.8, 0));
	AddParallel(new SetElbow(160));
	AddSequential(new AutoDriveTimed(1, 0, .25 ));
	AddSequential(new AutoCurve(-0.3, -50));
	AddParallel(new SetElevator(5));
	AddSequential(new AutoDrive(-10, -0.8, 90));

	//Place cube
	AddSequential(new SetKirbyKlaw(true));

 }

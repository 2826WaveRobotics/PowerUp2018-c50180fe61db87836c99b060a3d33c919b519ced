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
#include "AutoDistance.h"
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

	//Drive and prepare for scale
	AddSequential(new AutoDistance(-286, -0.8, 0));
	AddParallel(new SetElbow(70));
	AddSequential(new SetElevator(70));
	AddSequential(new WaveWait(0.25));
	AddSequential(new AutoRotate(-55));
	AddSequential(new SetElbow(60));
	AddSequential(new WaveWait(.25));

	//Place cube
	AddSequential(new SetKirby(-0.5, 1));
	AddSequential(new WaveWait(1));

	//Back away
	AddSequential(new AutoDistance(24, 0.7, -55));
	//AddSequential(new WaveWait(.25));
	AddSequential(new SetElevator(0));
 }

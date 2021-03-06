// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "RightSwitchSideAuto2.h"
#include "AutoDistance.h"
#include "AutoCurve.h"
#include "SetKirby.h"
#include "WaveWait.h"
#include "AutoDrive.h"
#include "AutoRotate.h"
#include "SetElbow.h"
#include "SetKirbyKlaw.h"
#include "SetKirby.h"
#include "SetElevator.h"
#include "AutoDriveWithVision.h"
#include "AutoDriveTimed.h"
#include "SetElevator.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

RightSwitchSideAuto2::RightSwitchSideAuto2() {

	//Drive and prepare for scale
	AddParallel(new SetElevator(35));
	AddParallel(new SetElbow(160));
	AddSequential(new AutoDistance(-167, -0.8, 0));
	AddSequential(new AutoRotate(-70));
	AddSequential(new AutoDriveTimed(-0.5, -90, 0.75));

	//Place cube
	AddSequential(new SetKirbyKlaw(true));

	//Back away
	AddSequential(new AutoDistance(15, 0.5, -90));
	AddSequential(new AutoRotate(-170));
	AddParallel(new SetElevator(0));
	AddSequential(new AutoDistance(110, 0.8, -170));
	AddSequential(new AutoRotate(-160));
	AddSequential(new AutoDrive(-40, -.5, -160, true));


	AddParallel(new SetKirby(0.8, 0.5));
	AddSequential(new SetKirbyKlaw(false));
	AddSequential(new SetKirby(0.8, 0.75));
	AddSequential(new AutoDistance(10, 0.5, -178));

	AddSequential(new SetElevator(35));
	AddSequential(new AutoDriveTimed(-0.5, -178, 1));
	AddSequential(new SetKirbyKlaw(true));
	AddSequential(new WaveWait(0.25));

	AddSequential(new AutoDistance(50, 0.8, -178));
	AddSequential(new AutoRotate(-140));
	AddParallel(new SetElevator(0));
	AddSequential(new AutoDrive(-40, -.4, -140, true));

	AddParallel(new SetKirby(0.5, 0.5));
	AddSequential(new SetKirbyKlaw(false));
	AddSequential(new SetKirby(0.5, 0.75));

	AddSequential(new SetElevator(35));

 }

// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef KIRBY_H
#define KIRBY_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "ctre/phoenix.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Kirby: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> kirbyRight;
	std::shared_ptr<WPI_TalonSRX> kirbyLeft;
	std::shared_ptr<frc::DigitalInput> kirbyFull;
	std::shared_ptr<frc::Solenoid> kirbyKlaw;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	Kirby();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void KirbyStop();
	void SetKirby(double speed);
	void SetKirbyKlaw(bool on);
	bool GetSwitch();

};

#endif

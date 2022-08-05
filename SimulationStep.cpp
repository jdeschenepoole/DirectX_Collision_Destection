// SimulationStep.cpp
// This will update the world (i.e. the objects)
// Note that this is *separate* from the 
//    Render() function....

#include "global.h"

void SimulationStep()
{
	CHRTimer simTimer;
	simTimer.Reset();
	simTimer.Start();


	// Determine how many seconds have gone by
	//	since the last call to this function...
	::g_TheTimer.Stop();

	float deltaSeconds = ::g_TheTimer.GetElapsedSeconds();

	const float MIN_TIMESTEP = 0.001f;
	if ( deltaSeconds > MIN_TIMESTEP )
	{
		deltaSeconds = MIN_TIMESTEP;
	}

	::g_TheTimer.Reset();
	::g_TheTimer.Start();

	// *********************************************
	// Animates all Objects
	// *********************************************
	::g_vecObjects[1].moveObject(deltaSeconds);


	// *****************************************************
	// Moves the Camera to remain behind the Primary Object
	// *****************************************************
	::g_eye.x += ::g_vecObjects[1].Velocity.x * deltaSeconds;
	::g_eye.y += ::g_vecObjects[1].Velocity.y * deltaSeconds;
	::g_eye.z += ::g_vecObjects[1].Velocity.z * deltaSeconds;
	::g_target.x += ::g_vecObjects[1].Velocity.x * deltaSeconds;
	::g_target.y += ::g_vecObjects[1].Velocity.y * deltaSeconds;
	::g_target.z += ::g_vecObjects[1].Velocity.z * deltaSeconds;


	// End
	simTimer.Stop();
	float timeSpend = simTimer.GetElapsedSeconds();
	int ImASexyBreakPoint = 0;
}
#include "checkpoint.h"



CheckPoint::CheckPoint()
{

}

CheckPoint::CheckPoint(Vector<float> positions[5])
{
	//loop through each position
	for (int i = 0; i < 5; i++)
	{
		ma_fPositions[i] = positions[i]; //!< Set the position to be the position passed over
	}
	iIndex = 0; //!<set the index to 0
	m_position = ma_fPositions[iIndex]; //!< Set the current position to be the first position
	oBounds = OBB(10, 5, -90, m_position); //!< Create an OBB for the object
	iLapsCompleted = 0; //!< Set there to be no laps completed
}

void CheckPoint::move(float &timeStep)
{
	
	iIndex++; //!< Increment the index
	//If all positions have been used
	if (iIndex == 5)
	{
		iIndex = 0; //!< Reset the index
		iLapsCompleted++; //!< Add one to the laps completed
	}
	m_position = ma_fPositions[iIndex]; //!< Set the position to the new location
	oBounds.MoveBoundingBox(m_position); //!< Move the bounding box to the new position
	
}

int CheckPoint::GetLapsCompleted()
{
	return iLapsCompleted; //!< Return the number of laps completed
}

bool CheckPoint::lapsComplete()
{
	//If 3 laps are completed then all laps are completed and game can end 
	if (iLapsCompleted == 3)
	{
		return true;
	}
	return false;
}
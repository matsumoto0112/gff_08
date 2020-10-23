#pragma once

#include <strix/client/ingame/interpolation/Common.h>
#include <strix/client/ingame/interpolation/MovementSnapshot.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  A list of movement snapshots representing points along a path traveled over time
 */
class MovementPath {
public:
    typedef std::list<std::unique_ptr<MovementSnapshot> > MovementList;

    MovementPath()
    {
    }

    /**
     *	 Construct a movement path
     *	 @param	maxStorePoints	The maximum number of Movement snapshots to store
     *	 @param	numStoreOldPathPoints	The number of old points to add on reset
     */
    MovementPath(int maxStorePoints, int numStoreOldPathPoints)
    {
	 m_maxStorePoints = maxStorePoints;
	 m_numStoreOldPathPoints = numStoreOldPathPoints;
    }

    MovementPath(const MovementPath &rhs)
    {
	 for(const std::unique_ptr<MovementSnapshot> &m : rhs.m_list) {
	     m_list.push_back(std::make_unique<MovementSnapshot>(*m));
	 }

	 m_currentPathPointIndex = rhs.m_currentPathPointIndex;
	 m_maxStorePoints = rhs.m_maxStorePoints;
	 m_numStoreOldPathPoints = rhs.m_numStoreOldPathPoints;
    }

    /**
     *  Get the maximum number of snapshots to store
     *  @returns	The maximum number
     */
    int GetMaxStorePoints() const 
    {
	 return m_maxStorePoints;
    }

    /**
     *  Set the maximum number of snapshots to store
     *  @param	maxStorePoints	The maximum number
     */
    void SetMaxStorePoints(int maxStorePoints) 
    {
	 m_maxStorePoints = maxStorePoints;
    }

    /**
     *  Get the number of start points to add on reset
     *  @returns	The number of points
     */
    int GetNumStoreOldPathPoints() const 
    {
	 return m_numStoreOldPathPoints;
    }

    /**
     *  Set the number of start points to add on reset
     *  @param	numStoreOldPathPoints	The number of points
     */
    void SetNumStoreOldPathPoints(int numStoreOldPathPoints) 
    {
	 m_numStoreOldPathPoints = numStoreOldPathPoints;
    }

    /**
     *  Get the underlying list of movement snapshots
     *  @returns	The list of snapshots
     */
    const MovementList &GetList() const
    {
	 return m_list;
    }

    /**
     *  Find if there is another movement snapshot in the path
     *  @param	offset	The offset from the current index into the path
     *  @returns	True if a snapshot exists, false if this is off the end of the path
     */
    bool IsAvailable(int offset) const 
    {
	 int index = m_currentPathPointIndex + offset;
	 return (index >= 0 && index < static_cast<int>(m_list.size()));
    }

    /**
     *  Get a movement snapshot from the path
     *  @param	offset	The offset from the current path index to get the snapshot from
     *  @returns	The movement snapshot at current index + offset, or null if this is out of range
     */
    const MovementSnapshot *Get(int offset) const;

    /**
     *	 Add a movement snapshot to the path. Will remove from the beginning of the path to make 
     *	 room if this increases the length of the path beyond the max length
     *	 @param	movement	The movement to add
     */
    void Add(const MovementSnapshot &movement);

    /**
     *  Clear the path, and add NumStoreOldPathPoints copies of the start point given
     *  @param	startPoint	The start point to add to the now empty path
     */
    void Reset(const MovementSnapshot &startPoint);

    /**
     *  Checks if the next snapshot in the movement path exists. If the next movement
     *  snapshot is beyond the number of NumStoreOldPathPoints, this call deletes the
     *  snapshot at the beginning of the path
     *  @returns	True if the next snapshot exists 
     */
    bool Next();
	
private:
	MovementList m_list;
    int m_currentPathPointIndex = 0;
    int m_maxStorePoints = 5;
    int m_numStoreOldPathPoints = 2;
};

} } } }
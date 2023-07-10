//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) 2003 - 2014 by Christian Gloor
//

#ifndef _ped_agent_h_
#define _ped_agent_h_ 1

#ifdef WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include "pedsim_original/ped_vector.h"

#include <deque>
#include <set>
#include <vector>

using namespace std;

namespace Ped
{
    class Tscene;
    class Twaypoint;

    /// \example example.cpp

    /// This is the main class of the library. It contains the Tagent, which eventually will move through the
    /// Tscene and interact with Tobstacle and other Tagent. You can use it as it is, and access the agent's
    /// coordinates using the getx() etc methods. Or, if you want to change the way the agent behaves, you can
    /// derive a new class from it, and overwrite the methods you want to change. This is also a convenient way
    /// to get access to internal variables not available though public methods, like the individual forces that
    /// affect the agent.
    /// \author  chgloor
    /// \date    2003-12-26
    class LIBEXPORT Tagent
    {

    public:
        Tagent();
        virtual ~Tagent();

        virtual void computeForces();
        virtual void move(double stepSizeIn);
        virtual Tvector desiredForce();
        virtual Tvector socialForce();
        virtual Tvector obstacleForce();
        virtual Tvector lookaheadForce(Tvector desired);
        virtual Tvector myForce(Tvector desired);

        void setPosition(double px, double py, double pz);
        void setVelocity(double vx, double vy, double vz)
        {
            v.x = vx;
            v.y = vy;
            v.z = vz;
        }
        void setType(int t) { this->type = t; };
        void setFollow(int id);
        void setVmax(double vmax);
        void setRadius(double radius) { agentRadius = radius; }

        int getFollow() const;

        int getid() const { return id; };
        int gettype() const { return type; };
        double getvmax() const { return vmax; };
        double getradius() const { return agentRadius; };

        // these getter should replace the ones later (returning the individual vector values)
        const Tvector &getPosition() const { return p; }
        const Tvector &getVelocity() const { return v; }
        const Tvector &getAcceleration() const { return a; }

        double getx() const { return p.x; };
        double gety() const { return p.y; };
        double getz() const { return p.z; };
        double getax() const { return a.x; };
        double getay() const { return a.y; };
        double getaz() const { return a.z; };
        double getvx() const { return v.x; };
        double getvy() const { return v.y; };
        double getvz() const { return v.z; };

        void setfactorsocialforce(double f);
        void setfactorobstacleforce(double f);
        void setfactordesiredforce(double f);
        void setfactorlookaheadforce(double f);

        void assignScene(Tscene *s);
        void addWaypoint(Twaypoint *wp);
        bool removeWaypoint(const Twaypoint *wp);
        void clearWaypoints();
        void removeAgentFromNeighbors(const Tagent *agentIn);

    protected:
        int id;    ///< agent number
        Tvector p; ///< current position of the agent
        Tvector v; ///< velocity of the agent
        Tvector a; ///< current acceleration of the agent
        int type;
        double vmax; ///< individual max velocity per agent
        int follow;

        Ped::Tvector desiredDirection;

        Ped::Tscene *scene;

        deque<Twaypoint *> waypoints; ///< coordinates of the next destinations
        Twaypoint *destination;       ///< coordinates of the next destination
        Twaypoint *lastdestination;   ///< coordinates of the last destination
        bool hasreacheddestination;   ///< true if it has reached its destination

        bool mlLookAhead;

        double factordesiredforce;
        double factorsocialforce;
        double factorobstacleforce;
        double factorlookaheadforce;

        double obstacleForceSigma;

        Ped::Tvector desiredforce;
        Ped::Tvector socialforce;
        Ped::Tvector obstacleforce;
        Ped::Tvector lookaheadforce;
        Ped::Tvector myforce;

        double relaxationTime;

        double agentRadius;

        set<const Ped::Tagent *> neighbors;

        long timestep;
    };
}
#endif

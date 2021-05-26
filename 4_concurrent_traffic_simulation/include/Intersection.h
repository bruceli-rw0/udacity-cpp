#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <future>
#include "TrafficObject.h"
#include "TrafficLight.h"

// forward declarations to avoid include cycle
class Street;
class Vehicle;

// auxiliary class to queue and dequeue waiting vehicles in a thread-safe manner
class WaitingVehicles
{
public:
    // getters / setters
    int getSize();

    // typical behaviour methods
    void pushBack(shared_ptr<Vehicle> vehicle, std::promise<void> &&promise);
    void permitEntryToFirstInQueue();

private:
    vector<shared_ptr<Vehicle>> _vehicles;      // list of all vehicles waiting to enter this intersection
    vector<std::promise<void>> _promises;       // list of associated promises
    std::mutex _mutex;
};

class Intersection : public TrafficObject
{
public:
    // constructor / desctructor
    Intersection();

    // getters / setters
    void setIsBlocked(bool isBlocked);

    // typical behaviour methods
    void addVehicleToQueue(shared_ptr<Vehicle> vehicle);
    void addStreet(shared_ptr<Street> street);
    vector<shared_ptr<Street>> queryStreets(shared_ptr<Street> incoming); // return pointer to current list of all outgoing streets
    void simulate();
    void vehicleHasLeft(shared_ptr<Vehicle> vehicle);
    bool trafficLightIsGreen();

private:
    // typical behaviour methods
    void processVehicleQueue();

    // private members
    vector<shared_ptr<Street>> _streets;    // list of all streets connected to this intersection
    WaitingVehicles _waitingVehicles;       // list of all vehicles and their associated promises waiting to enter the intersection
    bool _isBlocked;                        // flag indicating wether the intersection is blocked by a vehicle
    TrafficLight _trafficLight;
};

#endif
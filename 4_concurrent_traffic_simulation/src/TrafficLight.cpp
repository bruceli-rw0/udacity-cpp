#include <iostream>
#include <chrono>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> _lock_guard(_mutex);
    _queue.clear();
    _queue.emplace_back(std::move(msg));
    _cv.notify_one();
}

template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> _unique_lock(_mutex);
    _cv.wait(_unique_lock, [this]() { return !_queue.empty(); });

    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg;
}

/* Implementation of class "TrafficLight" */

std::random_device TrafficLight::device;
std::default_random_engine TrafficLight::generator(device());

TrafficLight::TrafficLight() : _currentPhase(TrafficLightPhase::red) {}

void TrafficLight::waitForGreen()
{
    while (1)
    {
        TrafficLightPhase msg = _msgQueue.receive();
        if (msg == TrafficLightPhase::green)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase() const 
{ 
    return _currentPhase; 
}

void TrafficLight::simulate()
{ 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now(); 
    std::chrono::high_resolution_clock::time_point t2;
    std::uniform_int_distribution<int> distribution(4000,6000); // random number between 4000-6000 millisecond
    auto randDuration = distribution(generator);
    while (1)
    {   
        // measure time passed since the last phase started
        t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if (randDuration <= duration)
        {
            // update traffic light phase
            _currentPhase = (_currentPhase == TrafficLightPhase::green) ? TrafficLightPhase::red : TrafficLightPhase::green;

            // send update to message queue
            _msgQueue.send(std::move(_currentPhase));
            
            // reset phase starting time
            t1 = std::chrono::high_resolution_clock::now();

            // genreate new duration
            randDuration = distribution(generator);
        }
        // wait for 1ms between two cycles
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

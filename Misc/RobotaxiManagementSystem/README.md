# Robotaxi Management System Design

## Problem Statement

Company DoWeCheatThemAndHow LLC would like to revolutionize the taxi dispatching industry and wants to create a new
dispatching software.The dispatching software must keep accurate track of the taxi fleet, their location, activity,
and passenger manifest(including location of the passengers, travel time, and wait time).

For the “passenger requests a ride” use case:

Passenger makes a request for a ride by calling the dispatcher and requests a ride, providing their current location and
desired destination. Dispatcher enters the information into the Software The first available taxi is assigned the job to
pick up and deliver the passenger The assigned taxi’s location is monitored throughout the entire job, in route to pick
up, pick up, in route to drop-off, and drop-off.

## Requirement

Requirements directly from the problem statement:

* R1 : The system shall be able to track the location and activity of all taxis in the fleet.
* R2 : The system shall be able to track the manifest of all passengers requesting a ride.
* R3 : The system shall be able to track the travel time of the taxi.
* R4 : The system shall be able to track the wait time of the passenger.
* R5 : The dispatcher shall be able to enter the passenger’s request for a ride.
* R6 : The dispatcher shall be able to assign the first available taxi to the passenger’s request.
* R7 : The system shall be able to track the location of the taxi throughout four stages of the job.
* R8 : The passenger shall be able to request a ride by calling the dispatcher.

Hidden requirements:

* R1 : The system shall have the access to a global 3rd party map.
* R2 : The system shall time stamp the request.
* R3 : The system shall queue up the passengers' requests.
* R4 : There is a notification system for the passenger to know the taxi is on the way.

Other potential requirements to consider for scalability:

* R1 : The system shall be able to prioritize assigning taxis to passengers based on the passenger’s location.
* R2 : The system shall be able to handle tons of passenger requests at the same time.
* R3 : The passenger shall have the ability to cancel the ride request.

## System

Robotaxi Management System

## Actors

### Primary actor

* Passenger

### Secondary actors

* Dispatcher
* Robotaxi
* System

# Use Case

## Actor Level Use Cases

### Passenger

* Call to request a ride : call the dispatcher to request a ride with current and destination locations.
* Call to cancel a ride (optional): call the dispatcher to cancel the previously requested ride.

### Dispatcher

* Enter the passenger request: enter the passenger request for a ride with current and destination locations.
* Remove the passenger request (optional): cancel the previously requested ride.

### Robotaxi

* Accept job: accept the job assigned by the system.
* In route to pick-up: drive to the passenger's current location.
* Pick up: pick-up the passenger at the current location.
* In route to drop-off: drive to the passenger's destination location.
* Drop off: drop off the passenger at the destination location.
* Quit job: quit the job after the passenger is dropped off or the request is cancelled when in route to pick-up.
* Roaming: drive around the city when there is no job assigned.

### System

* Assign a job: assign the first available taxi after the dispatcher puts in the passenger's request.
* Cancel a job (option): cancel the previously requested ride.
* Track taxi location: track the location of the taxi throughout the four stages of the job.
* Track taxi travel time: track the travel time of the taxi.
* Track passenger wait time: track the wait time of the passenger.

# Relationships

## Associations

| Functionality                 | Passenger | Dispatcher | Fleet System | Robotaxi |
|-------------------------------|:---------:|:----------:|:------------:|:--------:|
| **Call to request a ride**    |     ✅     |     ✅      |              |          |
| **Call to cancel a ride**     |     ✅     |     ✅      |              |          |
| **Enter passenger request**   |     ✅     |            |      ✅       |          |
| **Remove passenger request**  |     ✅     |            |      ✅       |          |
| **Assign a job**              |           |            |      ✅       |    ✅     |
| **Cancel a job**              |           |            |      ✅       |    ✅     |
| **Track taxi location**       |           |            |      ✅       |    ✅     |
| **Track taxi travel time**    |           |            |      ✅       |    ✅     |
| **Track passenger wait time** |           |            |      ✅       |    ✅     |
| **Accept job**                |           |            |      ✅       |    ✅     |
| **Quit job**                  |           |            |      ✅       |    ✅     |
| **In route to pick-up**       |           |            |      ✅       |    ✅     |
| **Pick up**                   |           |            |      ✅       |    ✅     |
| **In route to drop-off**      |           |            |      ✅       |    ✅     |
| **Drop off**                  |           |            |      ✅       |    ✅     |
| **Roaming**                   |           |            |      ✅       |    ✅     |

## Include

## Extend

# Use Case Diagram

Use the context diagram in the C4 design methodology to show the relationship between the actors and the system.

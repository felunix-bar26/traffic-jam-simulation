# Traffic Jam Simulation in C

## Description

This project is a traffic jam simulation written in C using raylib. The simulation demonstrates how traffic jams can form depending on the number of cars on the street, their desired speed, and their reaction time.

The cars spawn on the top-left street and drive towards the right. When a car reaches the right end of the street, it is moved to the left end of the street below and continues driving to the right. This creates a continuous loop of streets.

Cars spawn every 1.3 seconds by default. Each car has a desired speed of 120 km/h by default. To make the simulation more realistic, every car gets a slightly different desired speed and reaction time.

The reaction time represents the delay between a change in the traffic situation and the driver's reaction to it. For example, when a car in front starts braking, the following car does not react immediately. Instead, it waits for its individual reaction time before calculating whether it needs to brake or accelerate.

The simulation is intended to demonstrate how different traffic conditions can influence the formation of traffic jams. By changing the number of cars, the desired speed, and the spawn time, you can experiment with different traffic situations and observe how the traffic flow changes.

<img width="1503" height="952" alt="Screenshot From 2026-08-12 20-03-40" src="https://github.com/user-attachments/assets/62a828f6-8377-46f3-a1d0-39632c0ca1cc" />

## Installation

### Clone this repository

```shell
git clone
```

### Compile the program

Execute the following command to compile the program:

```shell
gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main
```

This project uses [raylib](https://www.raylib.com/) for graphics.

## Usage

### Start the program

Execute the following command to start the simulation:

```shell
./main
```

### Setting Car Parameters

The simulation allows you to change the reaction time, desired speed, and spawn time of the cars. You can also restart the simulation.

* **Left and right arrow keys:** Increase or decrease the reaction time.
* **Up and down arrow keys:** Increase or decrease the desired speed of the cars.
* **Z and T keys:** Increase or decrease the spawn time.
* **R key:** Restart the simulation.

Each car has a slightly different desired speed. This is intended to make the traffic more realistic, since not every driver wants to drive at exactly the same speed.

The reaction time also varies between cars. The default reaction time is 0.7 seconds, with a maximum additional variation of 0.5 seconds.

By changing these parameters, you can experiment with different traffic conditions and observe how they affect traffic flow and traffic-jam formation.

## License

[MIT](https://choosealicense.com/licenses/mit/)

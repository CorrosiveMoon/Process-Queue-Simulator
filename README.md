# Queue Simulation Program

This C++ program simulates a multi-queue system for processing tasks over a defined duration. It is designed to demonstrate a basic queuing algorithm and provides insights into task processing times and wait times within the system.

## Features

- User-configurable parameters, including the number of queues, arrival probability, maximum execution time of tasks, simulation duration, and random number seed.
- Queues are managed in an array, and tasks are assigned to the shortest queue.
- Simulation tracks task arrival, execution, and wait times.
- Generates statistics such as total processed tasks, average wait time, longest wait time, and remaining tasks in the queues at the end of the simulation.

## Usage

1. Compile the program using a C++ compiler (e.g., `g++ queue_simulation.cpp -o queue_simulation`).
2. Run the executable (`./queue_simulation`) and provide input for simulation parameters.
3. Observe the simulation's progress as it processes tasks over the specified duration.
4. Review the generated statistics to understand task processing efficiency.

## Configuration

The program allows you to configure the following simulation parameters:

- Number of queues: Specify the number of queues for task processing (up to 10).
- Arrival probability: Set the probability that a process arrives in one tick as a percentage (%).
- Maximum execution time: Define the maximum execution time of a process in ticks.
- Duration of the simulation: Specify the total duration of the simulation in ticks.
- Random number seed: Enter a random number seed for reproducible simulations.

## Example

Here's an example of how to run the program:

```bash
Enter the number of queues (up to 10): 3
Enter the probability that a process arrives in one tick (%): 30
Enter the maximum execution time of a process in ticks: 5
Enter the duration of the simulation in ticks: 100
Enter a random number seed: 42
Statistics
The program provides the following statistics at the end of the simulation:

Total processed tasks.
Average wait time (in ticks).
Longest wait time (in ticks).
Remaining processes in the queues after the simulation.
Contributions
Contributions and improvements to the code are welcome. Feel free to fork the repository, make changes, and submit pull requests.

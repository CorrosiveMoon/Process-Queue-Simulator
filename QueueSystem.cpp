#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * The struct Process represents a process with arrival time, execution time, and start processing time
 * attributes.
 * @property {int} arrival_time - The arrival_time property represents the time at which a process
 * arrives in the system. It indicates when the process enters the system and is ready to be executed.
 * @property {int} execution_time - The execution_time property represents the amount of time it takes
 * for a process to complete its execution. It is typically measured in units of time, such as
 * milliseconds or seconds.
 * @property {int} start_processing_time - The "start_processing_time" property is used to track when a
 * process starts being processed. It is used to keep track of the time at which a process begins its
 * execution.
 */
struct Process {
    int arrival_time;
    int execution_time;
    int start_processing_time; 
};

/**
 * This C++ program simulates a multi-queue system where processes arrive randomly and are processed
 * based on their execution time.
 * 
 * @return The main function is returning an integer value of 0.
 */
int main() {
    int num_pairs, probability, max_execution_time, duration, seed;

    // Input simulation parameters
    cout << "Enter the number of queues (up to 10): ";
    cin >> num_pairs;

    if (num_pairs < 1 || num_pairs > 10) {
        cout << "Invalid input for the number of queues." << endl;
        return 1;
    }

    cout << "Enter the probability that a process arrives in one tick (%): ";
    cin >> probability;

    if (probability < 0 || probability > 100) {
        cout << "Invalid input for probability." << endl;
        return 1;
    }

    cout << "Enter the maximum execution time of a process in ticks: ";
    cin >> max_execution_time;

    if (max_execution_time < 1) {
        cout << "Invalid input for maximum execution time." << endl;
        return 1;
    }

    cout << "Enter the duration of the simulation in ticks: ";
    cin >> duration;

    if (duration < 1) {
        cout << "Invalid input for simulation duration." << endl;
        return 1;
    }

    cout << "Enter a random number seed: ";
    cin >> seed;

    srand(seed);
// Array of queues
    queue<Process> queues[10]; 

    int tick;
    int totalProcessed = 0;
    int totalWaitTime = 0;
    int longestWaitTime = 0;

    for (tick = 1; tick <= duration; tick++) {
        //Loop that processes arrivals
        if (rand() % 100 < probability) {
            Process new_process;
            new_process.arrival_time = tick;
            new_process.execution_time = rand() % max_execution_time + 1;
            new_process.start_processing_time = -1; 

            int shortest_queue = 0;
            for (int i = 1; i < num_pairs; i++) {
                if (queues[i].size() < queues[shortest_queue].size()) {
                    shortest_queue = i;
                }
            }

            queues[shortest_queue].push(new_process);
        }

        //Loop that processes the queues
        for (int i = 0; i < num_pairs; i++) {
            if (!queues[i].empty()) {
                Process &front_process = queues[i].front();

                //Setting start_processing_time when the process reaches the front
                if (front_process.start_processing_time == -1) {
                    front_process.start_processing_time = tick;
                }

                //Decrementing the execution time
                front_process.execution_time--;

                //Checking if the process is completed
                if (front_process.execution_time == 0) {
                    int waitTime = front_process.start_processing_time - front_process.arrival_time;
                    totalWaitTime += waitTime;
                    longestWaitTime = max(longestWaitTime, waitTime);
                    queues[i].pop();
                    totalProcessed++;
                }
            }
        }

        //Output of the system at this tick
        cout << "Tick " << tick << ": ";
        for (int i = 0; i < num_pairs; i++) {
            cout << "Queue " << i + 1 << ": " << queues[i].size() << " ";
        }
        cout << endl;
    }

    //Calculating remaining processes in the queues after the end of the simulation
    int remainingProcesses = 0;
    for (int i = 0; i < num_pairs; i++) {
        remainingProcesses += queues[i].size();
    }

    //Displaying statistics
    cout << totalProcessed << " processes were processed with an average wait time of ";
    if (totalProcessed > 0) {
        cout << static_cast<double>(totalWaitTime) / totalProcessed << " ticks." << endl;
    } else {
        cout << "0 ticks." << endl;
    }
    cout << "The longest time a process waited was " << longestWaitTime << " ticks." << endl;
    cout << remainingProcesses << " processes remain in the queues after the end of the simulation." << endl;

    return 0;
}

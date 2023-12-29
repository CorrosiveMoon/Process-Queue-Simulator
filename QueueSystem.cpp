#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Process {
    int arrival_time;
    int execution_time;
    int start_processing_time; // To track when the process starts being processed
};

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

    queue<Process> queues[10]; // Array of queues

    int tick;
    int totalProcessed = 0;
    int totalWaitTime = 0;
    int longestWaitTime = 0;

    for (tick = 1; tick <= duration; tick++) {
        // Process arrivals
        if (rand() % 100 < probability) {
            Process new_process;
            new_process.arrival_time = tick;
            new_process.execution_time = rand() % max_execution_time + 1;
            new_process.start_processing_time = -1; // Initialize to -1

            int shortest_queue = 0;
            for (int i = 1; i < num_pairs; i++) {
                if (queues[i].size() < queues[shortest_queue].size()) {
                    shortest_queue = i;
                }
            }

            queues[shortest_queue].push(new_process);
        }

        // Process the queues
        for (int i = 0; i < num_pairs; i++) {
            if (!queues[i].empty()) {
                Process &front_process = queues[i].front();

                // Set start_processing_time when the process reaches the front
                if (front_process.start_processing_time == -1) {
                    front_process.start_processing_time = tick;
                }

                // Decrement the execution time
                front_process.execution_time--;

                // Check if the process is completed
                if (front_process.execution_time == 0) {
                    int waitTime = front_process.start_processing_time - front_process.arrival_time;
                    totalWaitTime += waitTime;
                    longestWaitTime = max(longestWaitTime, waitTime);
                    queues[i].pop();
                    totalProcessed++;
                }
            }
        }

        // Output snapshot of the system at this tick
        cout << "Tick " << tick << ": ";
        for (int i = 0; i < num_pairs; i++) {
            cout << "Queue " << i + 1 << ": " << queues[i].size() << " ";
        }
        cout << endl;
    }

    // Calculate remaining processes in the queues after the end of the simulation
    int remainingProcesses = 0;
    for (int i = 0; i < num_pairs; i++) {
        remainingProcesses += queues[i].size();
    }

    // Display statistics
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

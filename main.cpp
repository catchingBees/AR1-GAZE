#include <iostream>
#include <chrono>
#include <thread>
#include "../include/core/LockFreeQueue.h"
#include "../include/core/SpatialGrid.h"
#include "../include/network/P2PNode.h"

struct SensorData {
    Vector3 position;
    float thermal_reading;
};

int main() {
    std::cout << "[AR1-GAZE CORE] Initializing Visor Systems..." << std::endl;

    LockFreeQueue<SensorData, 1024> sensor_queue;
    SpatialGrid spatial_map;
    P2PNode mesh_network(1);

    mesh_network.start();
    std::cout << "[SYSTEM] P2P Mesh Node Online." << std::endl;

    std::atomic<bool> system_running{ true };
    std::thread sensor_thread([&]() {
        while (system_running) {
            SensorData incoming_data = { {10.0f, 0.0f, -5.0f}, 450.0f };
            sensor_queue.push(incoming_data);
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        });

    std::cout << "[SYSTEM] Entering Main Execution Loop." << std::endl;
    int tick_count = 0;

    while (system_running && tick_count < 100) {
        SensorData latest_data;
        while (sensor_queue.pop(latest_data)) {
            Breadcrumb new_crumb;
            new_crumb.node_id = 1;
            new_crumb.position = latest_data.position;
            new_crumb.max_temperature = latest_data.thermal_reading;

            spatial_map.addBreadcrumb(new_crumb);
            std::vector<Breadcrumb> to_send = { new_crumb };
            mesh_network.broadcastBreadcrumbs(to_send);
        }
        tick_count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }

    system_running = false;
    if (sensor_thread.joinable()) {
        sensor_thread.join();
    }
    mesh_network.stop();

    std::cout << "[SYSTEM] Visor Offline. Graceful shutdown complete." << std::endl;
    return 0;
}
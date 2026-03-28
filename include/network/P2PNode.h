#pragma once
#include "../core/SpatialGrid.h"
#include <vector>
#include <thread>
#include <atomic>
#include <iostream>

class P2PNode {
private:
    std::atomic<bool> running_{ false };
    std::thread network_thread_;
    uint32_t local_node_id_;

    // The background loop that listens for other visors
    void listenLoop() {
        while (running_) {
            // In production, this polls the UDP socket or radio hardware.
            // When data arrives, it decodes it and updates the shared memory.

            // Pausing slightly to prevent maxing out the CPU core
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

public:
    P2PNode(uint32_t node_id) : local_node_id_(node_id) {}

    // Spin up the network thread
    void start() {
        running_ = true;
        network_thread_ = std::thread(&P2PNode::listenLoop, this);
    }

    // Safely shut down the network
    void stop() {
        running_ = false;
        if (network_thread_.joinable()) {
            network_thread_.join();
        }
    }

    // Blast the 10-foot breadcrumbs out to the team
    void broadcastBreadcrumbs(const std::vector<Breadcrumb>& new_crumbs) {
        // We will print the telemetry to the console so we can see the engine working
        for (const auto& crumb : new_crumbs) {
            std::cout << "[TELEMETRY] Visor " << local_node_id_
                << " mapped thermal threat: " << crumb.max_temperature
                << "F at (" << crumb.position.x << ", " << crumb.position.y << ", " << crumb.position.z << ")"
                << std::endl;
        }
    }
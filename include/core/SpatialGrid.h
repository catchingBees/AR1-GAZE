#pragma once
#include <cstdint>
#include <vector>

// Minimalist 3D coordinate system
struct Vector3 {
    float x, y, z;
};

// The core data packet for the AR breadcrumbs
struct Breadcrumb {
    uint64_t timestamp;
    uint32_t node_id;      // Unique ID of the visor that dropped this
    Vector3 position;      // The 3D coordinates in the physical space
    float max_temperature; // The decluttered, highest-threat temperature reading

    // Default constructor required for initializing our lock-free buffers
    Breadcrumb() : timestamp(0), node_id(0), position{ 0.0f, 0.0f, 0.0f }, max_temperature(0.0f) {}
};

// The manager class that will hold the map
class SpatialGrid {
private:
    std::vector<Breadcrumb> breadcrumbs_;

public:
    // Drop a new breadcrumb into the local map
    void addBreadcrumb(const Breadcrumb& b) {
        breadcrumbs_.push_back(b);
    }

    // Retrieve the map to draw on the visor display or send over the network
    const std::vector<Breadcrumb>& getBreadcrumbs() const {
        return breadcrumbs_;
    }
};
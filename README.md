# AR1-GAZE : Core Engine

**Ignis Gaze** *High-Fidelity Augmented Reality for Fireground Operations*

AR1-GAZE is a bare-metal, zero-allocation C++ rendering and telemetry engine designed for high-stakes, ultra-low-latency environments. Built specifically to handle high-frequency thermal sensor ingest and spatial mapping without compromising display frame rates.

## Core Architecture

The system is designed with a strict separation of concerns, utilizing a multi-threaded architecture to ensure the rendering pipeline is never blocked by network I/O or sensor polling.

* **Lock-Free Sensor Ingest (`LockFreeQueue`):** Cache-aligned, zero-allocation ring buffer allowing asynchronous hardware threads to stream thermal and spatial data directly to the engine core without mutex locking.
* **Spatial Memory (`SpatialGrid`):** Minimalist 3D coordinate mapping system for tracking physical breadcrumbs and critical thermal threat thresholds.
* **P2P Mesh Network (`P2PNode`):** Dedicated background thread for broadcasting and receiving serialized tactical telemetry between operational visors.
* **Vulkan Render Pipeline (`VulkanEngine`):** *(In Development)* Direct-to-GPU rendering for clinical, high-contrast data overlays.

## Tech Stack
* **Language:** Modern C++ (C++20)
* **Graphics API:** Vulkan SDK
* **Build System:** CMake
* **Environment:** Visual Studio / MSVC

## Build Instructions

This project utilizes CMake for cross-platform compilation and dependency management.

1. Clone the repository:
   ```bash
   git clone https://github.com/catchingBees/AR1-GAZE.git
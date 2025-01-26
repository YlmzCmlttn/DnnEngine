# DnnEngine

DnnEngine is a modular C++ framework for building deep learning applications, focusing on object detection and image processing. It integrates modern C++ design patterns with OpenCV to provide a flexible and extensible development environment.

## Features

- **Deep Neural Networks (DNN):**
  - Support for loading and running models using OpenCV's DNN module.
  - Support for loading and running models using different Inference Engines like TensorRT and OpenVINO
  - Dynamic creation of DNN instances with a flexible factory pattern.

- **Event-Driven Architecture:**
  - Centralized application control with event callback mechanisms.

- **Builder Pattern for Parameters:**
  - Flexible parameter construction for DNN and object detection settings.

- **Visualization:**
  - Windowing for rendering and user interaction can be implement different API like GLFW.

- **Modern C++ Design:**
  - Smart pointers (`std::unique_ptr`) for memory safety.
  - Type-safe parameter handling with `std::variant`.

## Project Structure

- **src/**: Contains the implementation files for the framework.
  - `Core`: Main application logic.
  - `Dnn`: Neural network operations and factory.
  - `Window`: OpenCV-based visualization components.
  - `Detection`: Object detection functionality.

- **include/**: Header files for all modules, ensuring modularity and extensibility.

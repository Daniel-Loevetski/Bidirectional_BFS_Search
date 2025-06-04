# Graphics Maze Solver

A C++ OpenGL-based application that visualizes bidirectional breadth-first search (BFS) for solving a maze. Users can interact with the program to start and visualize the maze-solving process.

---

## Description

This project implements a graphical maze solver using bidirectional BFS. The maze is represented as a 2D grid, and the application visualizes the frontiers expanding from both the start and target positions until they meet. The path is then highlighted. The program uses OpenGL with FreeGLUT and GLEW for rendering and user interaction.

---

## Features

- **Bidirectional BFS**: Efficient maze-solving algorithm that searches from both the start and goal simultaneously.  
- **Visualization**: Real-time rendering of the maze grid, visited cells, and final path using OpenGL.  
- **Interactive Menu**: Right-click to open menu and select "Bidirectional BFS" to start the search.

---

## Repository Structure

```
Graphics/
├── Graphics.sln
├── Graphics.vcxproj
├── .vs/
├── .vscode/
├── Debug/                    # Visual Studio debug configuration folder
├── main.cpp                  # Main application entry point and logic
├── Cell.cpp                  # Cell class implementation for BFS nodes
├── Cell.h                    # Cell class definition
├── freeglut.h                # FreeGLUT header (bundled)
├── freeglut_ext.h            # FreeGLUT extension header
├── freeglut_std.h            # FreeGLUT standard header
├── glew.h                    # GLEW header (bundled)
├── wglew.h                   # WGL extension header for GLEW
├── glut.h                    # GLUT header (bundled)
└── glxew.h                   # GLX extension header for GLEW
```

---

## Prerequisites

- **Operating System**: Windows  
- **Development Environment**: Microsoft Visual Studio (2017 or later recommended)  
- **Libraries**:
  - **FreeGLUT** (included as headers and libraries in the project)  
  - **GLEW** (included as headers and libraries in the project)  
  - **OpenGL** (available via GPU drivers)

---

## Build Instructions

1. **Open the Solution**  
   - Launch Visual Studio.  
   - Open `Graphics.sln` from the project root.

2. **Configure Project**  
   - Ensure the configuration is set to `Debug` and the platform to `x64`.  
   - Verify that the include directories for FreeGLUT and GLEW are set correctly (the project uses relative paths to bundled headers).  
   - Verify that the linker settings include the bundled `.lib` files (e.g., `freeglut.lib`, `glew32.lib`).

3. **Build the Solution**  
   - In Visual Studio, select **Build > Build Solution** (or press `Ctrl+Shift+B`).  
   - Verify that `Graphics.exe` is generated under `Graphics/x64/Debug/`.

---

## Run Instructions

1. **Launch the Executable**  
   - Navigate to `Graphics/x64/Debug/` and run `Graphics.exe` (or press `F5` in Visual Studio to run directly).

2. **Interact with the Program**  
   - The window displays a maze grid.  
   - Right-click within the window to open the context menu.  
   - Select **"Bidirectional BFS"** to start the maze-solving visualization.  
   - The algorithm will animate frontiers from the start (top-left) and target (bottom-right) cells until they meet.  
   - The found path will be highlighted in a distinct color.

3. **Close the Application**  
   - Close the window or press the close button to exit.

---

## Maze Configuration

- The maze grid is defined internally in `main.cpp`.  
- Walls, paths, start, and target cells are represented using integer constants.  
- Modify the grid size and wall placements directly in `main.cpp` if desired.  
- Rebuild the project after any changes to `main.cpp` to see updates.

---

## Code Overview

- **main.cpp**  
  - Contains the `main()` function, OpenGL initialization, rendering functions (`display`, `idle`), and BFS logic.  
  - Implements event callbacks and menu for user interaction.

- **Cell.h / Cell.cpp**  
  - Defines the `Cell` class representing a maze cell for BFS, including row/column indices, parent pointer, and visitation status.  
  - Used for tracking BFS frontiers and reconstructing the final path.

- **Bundled Headers / Libs**  
  - **FreeGLUT**: Provides windowing and input handling (`freeglut.h`, `freeglut_ext.h`, `freeglut_std.h`, and `glut.h`).  
  - **GLEW**: Manages OpenGL extensions (`glew.h`, `wglew.h`, `glxew.h`).

---

## Dependencies

- **FreeGLUT**: Included in the project. No external installation required.  
- **GLEW**: Included in the project. No external installation required.  
- **OpenGL**: Provided by your GPU drivers. Ensure your graphics drivers are up to date.

---

## Customization

- **Grid Size & Maze Layout**  
  - Edit the `rows` and `cols` variables in `main.cpp` to change grid dimensions.  
  - Adjust the `maze` 2D array to alter wall positions (`WALL`), start (`START`), and target (`TARGET`) cells.

- **Algorithm Logic**  
  - The `BidirectionalBFS()` function in `main.cpp` implements the core search.  
  - Modify visitation IDs, frontier expansion rules, or visualization colors as needed.

---

## Acknowledgements

- Developed as part of a computer graphics assignment.  
- Utilizes FreeGLUT and GLEW for OpenGL context creation and extension management.  

---

*Enjoy exploring bidirectional BFS visualization!*

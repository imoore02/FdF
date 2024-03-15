# fdf
A graphics program that renders 3D wireframe models from elevation maps onto a 2D grid, providing a visual representation of terrain.

# Key Features

* <b>Input Data:</b> Fdf takes as input a file containing a map of integer values representing heights. Each integer corresponds to a point in a grid, and the value determines the height of that point. These values are used to create a 3D wireframe mesh.

*  <b>Graphics Rendering:</b> Using a graphical library like MiniLibX or SDL, Fdf renders the wireframe mesh on the screen. Each point in the grid is represented by a pixel, and lines are drawn between adjacent points to create the wireframe effect.

*  <b>3D Projection:</b> Fdf employs 3D projection techniques to convert the 3D coordinates of the points into 2D coordinates for display on the screen. This allows the program to simulate the appearance of a 3D object.

*  <b>User Interaction:</b> Depending on the implementation, Fdf may allow users to interact with the displayed wireframe. This could include features like zooming, rotating, or translating the object to view it from different angles.


https://github.com/imoore02/fdf/assets/100339482/27ed2f60-e119-4a3d-95a3-4a42d05c2ee0

# Usage

Clone this repository and run make. Then run the executable with any of the maps available in the maps folder.
```bash
./fdf maps/42.fdf
./fdf maps/mars.fdf
```

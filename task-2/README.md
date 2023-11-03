# Composing a Scene & Drawing a Leaf 

In the 2nd task, we have taken the fundamentals learned in Task 1 and applied them to create a more complex scene. This scene includes a house and various elements like sun, tree and cloud-like spiral shape. We also introduced the detailed drawing of a leaf.

## 1. Composing a Scene

We have used a **transformer-core** shape as out starting point for the house structure. In addition, we have used the coils as our cloud. It's worth mentioning that we have constructed this shape using the least number of triangles using `GL_TRIANGLE_STRIP`.

<div align="center">
  <div style="margin: 10px;">
    <img src="https://github.com/Zoz-HF/GFX-Tasks/blob/main/task-2/img/core.png?raw=true" alt="System and biomedical engineering" width="400">
  </div>
</div>

Then, we have used the circle equation to shape our sunny element in the scene. We have drawn such element using `GL_TRIANGLE_FAN`.
<div align="center">
  <div style="margin: 20px;">
    <img src="https://github.com/Zoz-HF/GFX-Tasks/blob/main/task-2/img/sun.jpg?raw=true" alt="System and biomedical engineering" width="400";>
  </div>
</div>

After mixing theses shapes and with the help of our artistic nature, we could come up with such scene:

<div align="center">
  <div style="display: inline-block; margin-right: 20px;">
    <img src="https://github.com/Zoz-HF/GFX-Tasks/blob/main/task-2/img/Home_Scene.png?raw=true" alt="System and biomedical engineering" width="400">
  </div>
</div>

> **Note**: Each shape of these ones is a stand-alone program, so in order to print the outcome of each sub-program, make sure to comment the rest programs, in order to avoid conflicts due to multiple defining of `main` fucntion 
## 1. Drawing a Leaf
This shape was a bit challenging for beginners due to its curvature nature, where we had to define multiple different curves with different radius to add as much as realistic to the drawing. 
<div align="center">
  <div style="display: inline-block; margin-right: 20px;">
    <img src="https://github.com/Zoz-HF/GFX-Tasks/blob/main/task-2/img/Screenshot%202023-11-02%20190151.png?raw=true" alt="System and biomedical engineering" width="200">
  </div>
</div>

## Acknowledgments

This code is provided as a basic example of using OpenGL for drawing shapes. Feel free to modify and expand upon it for your own projects.

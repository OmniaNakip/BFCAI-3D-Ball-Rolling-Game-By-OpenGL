# 🛠️ OpenGL & C++ Skills and Notes

This file compiles all the essential functions and coding standards required to build our 3D game, categorized according to the course materials. It serves as a quick reference for the team to ensure consistency.

## 1. Code Style & OpenGL Architecture
* **Event-Driven Programming:** Our code does not run linearly. Instead, it relies on "Events." We register callback functions (like `glutDisplayFunc`), and the OpenGL API calls them when necessary.
* **Naming Conventions:** OpenGL functions are easily identifiable by their prefixes and suffixes:
  * `gl` prefix: Belongs to the core Graphics Library.
  * `glu` prefix: Belongs to GL Utilities (e.g., camera setup).
  * `glut` prefix: Belongs to GL Utility Toolkit (manages windows and inputs).
  * Suffixes specify data types: `f` for `float`, `i` for `integer`, and `v` for `vector/pointer` (e.g., `glVertex3f` vs `glVertex3fv`).

## 2. Window Management & Setup (Section 1 & 2)
These functions are typically used inside `main()` to set up the environment before entering the game loop.
* `glutInit(&argc, argv)`: Initializes the GLUT library.
* `glutInitDisplayMode(...)`: Configures the display mode. Use `GLUT_SINGLE | GLUT_RGB` for basic tasks, but we must use `GLUT_DOUBLE` for smooth 3D animation.
* `glutInitWindowSize(w, h)` & `glutInitWindowPosition(x, y)`: Sets the window dimensions and screen position.
* `glutCreateWindow("Title")`: Creates the application window.
* `glutMainLoop()`: Enters the infinite event processing loop.

## 3. 2D & 3D Drawing Primitives (Section 2)
These functions are responsible for rendering and must be called inside the Display Callback function.
* `glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`: Clears the screen and depth buffer at the beginning of each frame.
* `glLoadIdentity()`: Resets the current matrix (resets the coordinate system).
* `glBegin(GL_TRIANGLES)` & `glEnd()`: Opens and closes a drawing block. You pass the primitive type like `GL_POINTS`, `GL_LINES`, `GL_QUADS`, or `GL_POLYGON`.
* `glVertex2f(x, y)` / `glVertex3f(x, y, z)`: Specifies the coordinates of the vertices.
* `glFlush()`: Forces execution of OpenGL commands to display the buffer.

## 4. Animation, Coloring & Transformations (Section 3)
* **Animation:**
  * We use Double Buffering (`GLUT_DOUBLE`) to prevent screen flickering. We draw on the Back Buffer while the Front Buffer is displayed.
  * `glutSwapBuffers()`: Swaps the front and back buffers after rendering is complete.
  * `glutTimerFunc(ms, timer, 0)` & `glutPostRedisplay()`: Used to trigger frame updates and redraw the scene continuously for the Game Loop.
* **Coloring & Shading:**
  * `glClearColor(r, g, b, a)`: Sets the background color (values from 0.0 to 1.0).
  * `glColor3f(r, g, b)`: Sets the current drawing color.
  * `glShadeModel(GL_SMOOTH)`: Enables smooth color blending across polygons (default behavior, better than Flat shading).
* **Transformations:**
  * `glTranslatef(x, y, z)`: Moves the coordinate system to place objects in the world.
  * `glRotatef(angle, x, y, z)` & `glScalef(x, y, z)`: Rotates and scales objects.
  * *Crucial Note:* Transformation functions must be called *outside* the `glBegin()` and `glEnd()` block.

## 5. Handling Inputs (Section 4)
Used to control the player and navigate menus.
* `glutKeyboardFunc(keyboard)`: Handles standard ASCII keys (letters, numbers, spacebar, ESC).
* `glutSpecialFunc(specialKeys)`: Handles special keys (arrow keys, F1-F12).
* `glutMouseFunc(mouse)`: Detects mouse clicks and their state (Left/Right/Middle, Up/Down).
* `glutMotionFunc(motion)`: Tracks mouse movement while a button is held down.

## 6. 3D Environment, Matrices & Cameras (Section 5 & Matrices)
Moving from 2D to 3D requires handling matrices and the camera perspective.
* **Matrix Modes:**
  * `glMatrixMode(GL_PROJECTION)`: Used when setting up the camera lens/perspective.
  * `glMatrixMode(GL_MODELVIEW)`: Used when manipulating objects (moving, rotating) in the world.
* **Projection Setup:**
  * `gluOrtho2D(...)`: Orthographic projection (ignores depth/Z-axis, good for 2D UI or menus).
  * `gluPerspective(fovy, aspect, zNear, zFar)`: Perspective projection (realistic 3D where distant objects appear smaller).
* **Camera Setup:**
  * `gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)`: Acts as the camera. Sets where the camera is located, what it is looking at, and which way is "up".
* `glEnable(GL_DEPTH_TEST)`: Absolutely essential for 3D. It enables the Z-buffer so OpenGL knows which objects are in front and which are hidden behind others.

## 7. Advanced: Lighting, Textures & Collision
* **Lighting:**
  * Requires enabling the lighting system: `glEnable(GL_LIGHTING)` and turning on specific lights like `glEnable(GL_LIGHT0)`.
  * `glLightfv(...)` & `glMaterialfv(...)`: Used to define light properties (Ambient, Diffuse, Specular) and how object surfaces react to that light.
* **Textures:**
  * Used to wrap 2D images (like brick walls or roads) onto 3D geometry.
  * Core workflow: Generate an ID (`glGenTextures`), bind it (`glBindTexture`), and load the image data (`glTexImage2D`). Use texture coordinates (`glTexCoord2f`) to map the image to vertices.
* **Collision Detection (Physics Rules):**
  * Do not perform collision checks on complex 3D meshes (too heavy for performance).
  * Use **AABB (Axis-Aligned Bounding Box)** for box-like objects (checking if X and Y boundaries overlap).
  * Use **Circle-AABB Collision** for the player/ball by checking the distance from the circle's center to the closest point on the AABB edge using the `Radius`.
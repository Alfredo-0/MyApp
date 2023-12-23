# MyApp


At this moment the project has a basic abstraction of Vertex Buffer and Vertex Array. It handle simple Textures and very soon it will be able to load .OBJ files.

I am working in my own Math library for the game engine or GUI. There is still too many things to do. The next step after creating the Math Library and handleling with complex models is learning about lightening and more advanced topics of Shaders. 

# Dec 21:

A first Math header file is done. The header file allows to insert matrices as uniforms. I can make affine transformations, yet I have to put explicitly by own. That is cumbersome and propts a lot of bugs. The next step is to implement methods that simplifies those transformations. 

To load meshes/models is required to learn the open source library ASSIMP. At this moment my project requires a lot work before incurring in complex models. It will be better to implement normals, cameras, shadows, and lighting.

There are some resources online related to printing curves and surfaces, after reading complex models. That is the next step.

# Dec 23: 

A rendered Cube that rotates using Quaternions is done. I implemented a simple structure to handle with 4x4 matrices and quaterions to create spatial rotations. Next time, I will try to render a textured Cube.



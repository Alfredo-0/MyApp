//
//  OBJLoader.hpp
//  OpenGl
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/*
        float points[] = {
          //Coord              //Colors          //Textures
           0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 0.0f, //0
          -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, //1.0f, 0.0f, //1
           0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //1.0f, 1.0f, //2
          -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 1.0f, //3
           0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 0.0f, //4
          -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //1.0f, 0.0f, //5
           0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //1.0f, 1.0f, //6
          -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f  //,0.0f, 1.0f //7
        };

        unsigned int ind[] = {
          0, 2, 1,
          1, 2, 3,
          0, 4, 6,
          0, 6, 2,
          1, 4, 0,
          1, 5, 4,
          1, 3, 7,
          1, 7, 5,
          2, 6, 3,
          3, 6, 7,
          5, 6, 4,
          5, 7, 6
        };


        mat4f Mat;
        Quaternion rot(0.0, {0.0, 0.0, 0.0}); 
        Mat.RotateT(rot);

        mat4f t;
        t.TranslationT(0.0, 0.0, 4.0);
        mat4f y;
        y.TranslationT(0.0, 1.0, 0.0);

        float ar = (float)WIDTH / (float)HEIGHT;
        float Near = 0.0f;
        float Far = 10.0f;
        float Range = Near - Far;

        mat4f Proj(
                    1/ar, 0.0f, 0.0f,             0.0f,
                    0.0f, 1.0f, 0.0f,             0.0f,
                    0.0f, 0.0f, (Far+Near)/Range, 2.0*Far*Near/Range,
                    0.0f, 0.0f, 1.0f,             0.0f
        );

        VertexArray myVAO;
        VertexBuffer Square(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(3); //Coord
        layout.Push<float>(3); //Colors
        //layout.Push<float>(2); //TexCoord

        myVAO.AddBuffer(Square, layout);
        myVAO.Bind();

        IndexBuffer myIB(ind, 3*12);
        
        Shader shader("shader/vertex.shader", "shader/fragment.shader");
        shader.Bind();

        Renderer render;



        vec3f direction(0.0, 0.0, 0.0);
      float angle = 0;




                render.Draw(myVAO, myIB, shader);

          
          Quaternion rot(angle, direction); 
          Mat.RotateT(rot);
          shader.SetUniformMatrix4fv("t", Proj*t*Mat);
            
*/
//
//  OBJLoader.hpp
//  OpenGl
//
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Math.hpp"

void load_obj(const std::string& filename, std::vector<float> &data, std::vector<vec3f> &vertices, std::vector<vec2f> &texCoord, std::vector<short int> &elements){
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
    }

    while(getline(file, line)){
        if(line.substr(0,2)== "v "){
            std::istringstream s(line.substr(2));
            vec3f v;
            s >> v.x; s >> v.y; s >> v.z;   
            vertices.push_back(v);
            //std::cout<<v.x<<" "<<v.y<<" "<<v.z<<"\n";
        }

        else if (line.substr(0,3) == "vt "){
            std::istringstream s(line.substr(3));
            vec2f vt;
            s >> vt.x; s >> vt.y;   
            texCoord.push_back(vt);
            
        }

        else if (line.substr(0,2) == "f "){
            std::istringstream s(line.substr(2));
            short int a1,b1, a2, b2, a3, b3;
            char c;
            s >> a1; s>>c; s >> b1; 
            s >> a2; s>>c; s >> b2; 
            s >> a3; s>>c; s >> b3;

            elements.push_back(--a1); elements.push_back(--b1);
            elements.push_back(--a2); elements.push_back(--b2);
            elements.push_back(--a3); elements.push_back(--b3);
        }
        
    }
    for (int i = 0; i < elements.size(); i+=2){
            short int ia = elements[i];   //Position
            short int ib = elements[i+1]; //texCoord 

            data.push_back(vertices[ia].x);
            data.push_back(vertices[ia].y);
            data.push_back(vertices[ia].z);
            data.push_back(texCoord[ib].x);
            data.push_back(texCoord[ib].y);      
        }

    file.close();
}

        /*
        std::vector<float> cube;
        std::vector<short int> indices;
        std::vector<vec3f> vertices;
        std::vector<vec2f> texCoord;
        load_obj("/home/alfredourrea/Documents/MyApp/res/Cube.mtl.obj", cube, vertices, texCoord, indices);
        
        float cubea[cube.size()];

        unsigned int ind1[indices.size()];
        for (int i = 0; i<indices.size(); i++)
          ind1[i] = i;

        for (int i = 0; i< cube.size(); i++){
          cubea[i] = cube[i];
          //std::cout<<cubea[i]<<"\n";
        }
        */
       /*
        VertexArray myVAO1;
        VertexBuffer Cube(cubea, sizeof(cubea));

        VertexLayout layout1;
        layout1.Push<float>(3); //Position
        layout1.Push<float>(2); //TexCoord
        //layout.Push<float>(2); //TexCoord

        myVAO1.AddBuffer(Cube, layout1);
        myVAO1.Bind();

        IndexBuffer myIB1(ind1, indices.size());

        
        

        Texture texture("textures/texture.jpg");
        texture.Bind(0);

        shader.SetUniform1i("u_Texture", 0);
        //shader.SetUniformMatrix4fv("t", translation);
*/
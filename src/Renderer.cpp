#include "Renderer.hpp"

void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout<<"[OpenGL Error] ("<<error<<"):"<<function<<file<<":"<<line<<std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& IB, const Shader& shader) const{
    shader.Bind();
    //shader.SetUniform4f("u_Color", 0.f, 0.f, 0.f, 0.f);
    VAO.Bind();
    IB.Bind();

    glDrawElements(GL_TRIANGLES, IB.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const{
    glClear(GL_COLOR_BUFFER_BIT);
}
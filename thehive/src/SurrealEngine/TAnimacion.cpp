#include "TAnimacion.hpp"

TAnimacion::TAnimacion(){}
TAnimacion::~TAnimacion(){}


TAnimacion::TAnimacion(std::vector<ZMeshData> &poses_){
    auto manager = Singleton<AssetManager>::Instance();
    poses = poses_;
    shader = manager->getShader("AnimationShader");
    it = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);
    glEnableVertexAttribArray(8);

    glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
    glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
    glVertexAttribFormat(2, 2, GL_FLOAT, false, 0);
    glVertexAttribFormat(3, 3, GL_FLOAT, false, 0);
    glVertexAttribFormat(4, 3, GL_FLOAT, false, 12);
    glVertexAttribFormat(5, 3, GL_FLOAT, false, 0);
    glVertexAttribFormat(6, 3, GL_FLOAT, false, 12);
    glVertexAttribFormat(7, 3, GL_FLOAT, false, 0);
    glVertexAttribFormat(8, 3, GL_FLOAT, false, 12);

    glVertexAttribBinding(0, 0);
    glVertexAttribBinding(1, 0);
    glVertexAttribBinding(2, 1);
    glVertexAttribBinding(3, 2);
    glVertexAttribBinding(4, 2);
    glVertexAttribBinding(5, 3);
    glVertexAttribBinding(6, 3);
    glVertexAttribBinding(7, 4);
    glVertexAttribBinding(8, 4);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  poses[0].IndexBuffer);
    glBindVertexArray(0);

    size = poses[0].IndexSize;
}

void TAnimacion::Interpolate(){

}

// Se quedan vacios
void TAnimacion::beginDraw(const uint8_t &T_ID){
    if(T_ID == 2){

        // MODELO
        shader->Bind();
        zmat->Bind();
        GLuint M = shader->getUniformLocation("M");
        glUniformMatrix4fv(M,1,GL_FALSE,&modelMatrix[0][0]);

        // MODELO*VISTA*PERSPECTIVA
        glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
        GLuint MVP = shader->getUniformLocation("MVP");
        glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

        glBindVertexArray(VAO);
        // LA FINALE
        glBindVertexBuffer(0, poses[0].VBOs[0], 0, 24);
        glBindVertexBuffer(1, poses[0].VBOs[1], 0, 8);
        glBindVertexBuffer(2, poses[0].VBOs[2], 0, 24);
        glBindVertexBuffer(3, poses[1].VBOs[0], 0, 24);
        glBindVertexBuffer(4, poses[1].VBOs[1], 0, 24);

        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, nullptr);
    }
}
void TAnimacion::endDraw(const uint8_t &T_ID){
    
}

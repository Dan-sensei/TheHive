#include "Fade.hpp"

#include <GL/glew.h>
#include "AssetManager.hpp"

Fade::Fade()
:Accumulator(0), TARGET_TIME(0), UPD(nullptr)
{
    float RENDER_QUAD[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,
         1.0f, -1.0f,
    };

    glGenVertexArrays(1, &QUAD);

        glBindVertexArray(QUAD);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);

        glVertexAttribBinding(0, 0);

        glBindVertexBuffer(0, VBO, 0, 8);

    glBindVertexArray(0);

    SHADER = Singleton<AssetManager>::Instance()->getShader("Plano");
}

Fade::Fade(const Fade &orig)
:QUAD(orig.QUAD), VBO(orig.VBO)
{}

Fade::~Fade(){
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &QUAD);
}


void Fade::setFadeIn(float TIME){
    UPD = &Fade::UpdateFadeIn;
    Accumulator = TIME;
    clock.Restart();
    TARGET_TIME = TIME;
}

void Fade::setFadeOut(float TIME){
    UPD = &Fade::UpdateFadeOut;
    Accumulator = 0;
    clock.Restart();
    TARGET_TIME = TIME;
}

float Fade::UpdateFadeIn(){
    Accumulator -= clock.Restart().Seconds();
    return Accumulator / TARGET_TIME;
}

float Fade::UpdateFadeOut(){
    Accumulator += clock.Restart().Seconds();
    return Accumulator / TARGET_TIME;
}


bool Fade::Draw(){
    bool END = false;
    if(!UPD) return true;

    float ALPHA = (this->*UPD)();
    if(UPD == &Fade::UpdateFadeIn && Accumulator < 0){
        ALPHA = 0;
        END = true;
    }
    else if(Accumulator > TARGET_TIME){
        ALPHA = 1;
        END = true;
    }

    SHADER->Bind();

    glUniform1f(1, -1);  // ZINDEX
    glUniform3f(2, 0, 0, 0);
    glUniform1f(3, ALPHA);

    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    return END;
}

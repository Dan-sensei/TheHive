#include "ZPlayer.hpp"

#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>
#include <Omicron/OpenGEnum.hpp>

ZPlayer::ZPlayer() {

    float RENDER_QUAD[] = {
        -1.0f,  1.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &QUAD);

        glGenBuffers(1, &QUAD_POS_UV);
        glBindVertexArray(QUAD);
        glBindBuffer(GL_ARRAY_BUFFER, QUAD_POS_UV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 8);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, QUAD_POS_UV, 0, 16);

    glBindVertexArray(0);

    glGenTextures(1, &VideoBuffer);
    glBindTexture(GL_TEXTURE_2D, VideoBuffer);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 1280, 720);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Engine = Singleton<Omicron>::Instance();
}

ZPlayer::~ZPlayer(){

}

void ZPlayer::PlayVideo(const std::string &PathToVideo, const std::string &PathToAudio) {

  Sound = Singleton<SoundSystem>::Instance();

  s_video = new SonidoNormal();
  Sound->createSound(PathToAudio, s_video);

    // ZVideo.open(PathToVideo);
    //
    // if (!ZVideo.isOpened()) {
    //     std::cout  << "No se pudo abrir el vídeo " << PathToVideo << std::endl;
    //     return;
    // }
    //
    // Singleton<AssetManager>::Instance()->getShader("Video")->Bind();

    // double I_FPS = 1/ZVideo.get(5);
    // ZVideo >> ZFrame;
    // THE_CLOCK.Restart();
    // double Accumulator = 0;
    // s_video->play();
    // do{
    //
    //     Engine->BeginDraw();
    //
    //     Accumulator += THE_CLOCK.Restart().Seconds();
    //     if(Accumulator > I_FPS){
    //         Accumulator -= I_FPS;
    //         glTextureSubImage2D(VideoBuffer, 0,0,0, 1280, 720, GL_BGR, GL_UNSIGNED_BYTE, ZFrame.ptr());
    //         ZVideo >> ZFrame;
    //         Sound->update();
    //     }
    //
    //     glActiveTexture(GL_TEXTURE0);
    //     glBindTexture(GL_TEXTURE_2D, VideoBuffer);
    //     glUniform1i(5, 0);
    //
    //     glBindVertexArray(QUAD);
    //     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //     glBindVertexArray(0);
    //
    //     Engine->PollEvents();
    //     Engine->EndDraw();
    //
    // } while(!ZFrame.empty() && !Engine->key(gg::X, true));

    // s_video->stop();

    // ZVideo.release();
    delete s_video;
}

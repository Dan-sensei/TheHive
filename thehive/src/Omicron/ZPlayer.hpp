#ifndef _ZPLAYER_H
#define _ZPLAYER_H

#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <Omicron/Clock.hpp>
#include <Omicron/Omicron.hpp>

class ZPlayer {
    public:
        ZPlayer();
        ~ZPlayer();

        void PlayVideo(const std::string &PathToVideo);

    private:
        ZPlayer(const ZPlayer &origin) = delete;

        cv::VideoCapture ZVideo;
        cv::Mat ZFrame;

        gg::Clock THE_CLOCK;

        unsigned int QUAD;
        unsigned int QUAD_POS_UV;
        unsigned int VideoBuffer;

        Omicron* Engine;
};

#endif
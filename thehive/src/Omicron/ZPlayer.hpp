// #ifndef _ZPLAYER_H
// #define _ZPLAYER_H
//
// #define CL_HPP_ENABLE_EXCEPTIONS
// #define CL_HPP_TARGET_OPENCL_VERSION 200
//
// // #include <CL/cl2.hpp>
// #include <opencv4/opencv2/videoio.hpp>
// #include <opencv4/opencv2/opencv.hpp>
// #include <Omicron/Clock.hpp>
// #include <Omicron/Omicron.hpp>
// #include <FMOD/SoundSystem.hpp>
// #include <FMOD/SonidoNormal.hpp>
//
// class ZPlayer {
//     public:
//         ZPlayer();
//         ~ZPlayer();
//
//         void PlayVideo(const std::string &PathToVideo, const std::string &PathToAudio);
//
//     private:
//         ZPlayer(const ZPlayer &origin) = delete;
//
//         cv::VideoCapture ZVideo;
//         cv::Mat ZFrame;
//
//         gg::Clock THE_CLOCK;
//
//         unsigned int QUAD;
//         unsigned int QUAD_POS_UV;
//         unsigned int VideoBuffer;
//
//         Omicron* Engine;
//
//         SoundSystem *Sound;
//
//         SoundEvent* s_video;
// };
//
// #endif

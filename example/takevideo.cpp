#include <lccv.hpp>
#include <libcamera_app.hpp>
#include <opencv2/opencv.hpp>

int main() {
    uint32_t num_cams = LibcameraApp::GetNumberCameras();
    std::cout << "Found " << num_cams << " cameras." << std::endl;

    uint32_t height = 720;
    uint32_t width = 1280;
    uint32_t fps = 30;
    std::cout<<"Sample program for LCCV video capture"<<std::endl;
    std::cout<<"Press ESC to stop."<<std::endl;
    cv::TickMeter timer;
    cv::Mat image = cv::Mat(height, width, CV_8UC3);
    cv::Mat image2 = cv::Mat(height, width, CV_8UC3);
    lccv::PiCamera cam;
    cam.options->video_width=width;
    cam.options->video_height=height;
    cam.options->framerate=fps;
    cam.options->verbose=true;
    cv::namedWindow("Video",cv::WINDOW_NORMAL);
    cam.startVideo();

    int ch=0;
    std::cout << std::fixed << std::setprecision(1);

    while(ch!=27){
        timer.start();
        if (!cam.getVideoFrame(image,1000)){
            std::cout<<"Timeout error"<<std::endl;
            continue;
        }
        else
        {
            cv::imshow("Video",image);
        }
        timer.stop();

        if (image.empty()) break;

        // cv::Rect selection = cv::selectROI("Video", image, true);

        if (timer.getCounter() % fps == 0)
        {
            std::cout << "AVG TIME: " << timer.getAvgTimeMilli() << " ms." << std::endl;
        }
        ch = cv::waitKey(1000 / fps);
    }

    cam.stopVideo();
    cv::destroyAllWindows();
}

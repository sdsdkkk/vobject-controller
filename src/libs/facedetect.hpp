#include <opencv2/opencv.hpp>
#include <iostream>

void detectFace(cv::Mat image);

int videoCapture() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            std::cerr << "Error reading frame" << std::endl;
            break;
        }

        detectFace(frame);
        cv::imshow("Camface", frame);
        if (cv::waitKey(1) == 27) break; // Press ESC to exit
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

void detectFace(cv::Mat image) {
    cv::Mat grayscaleImage;

    cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("opencv/haarcascade_frontalface_alt.xml")) {
        std::cerr << "Error: Haar Cascade loading failed" << std::endl;
        return;
    }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(grayscaleImage, faces, 1.1, 3, 0, cv::Size(30, 30));

    for (const auto& face : faces) {
      cv::rectangle(image, face, cv::Scalar(255, 0, 0), 2);
    }
}

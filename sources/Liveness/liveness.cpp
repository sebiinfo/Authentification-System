#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char* argv[])
{

    // This code takes the camera capture and tells weather the input is
    //  a live input of a person or not by computing th optimal flow
    // however this has been written separately as a main and the next steps
    // are to integrate it with the rest of the project and particularly
    // understand where does this fit in the general architecture of the project


    // Read the video from the default camera
    cv::VideoCapture cap(0);

    // Check if the camera is opened
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    //  width and height of the frames
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // VideoWriter object for the output video
    cv::VideoWriter video("out.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));

    // Check VideoWriter object
    if(!video.isOpened())
    {
        std::cout << "Error opening video writer" << std::endl;
        return -1;
    }

    // window to display the frames
    cv::namedWindow("Frame", cv::WINDOW_NORMAL);

    // face detector haarcascades
    cv::CascadeClassifier face_detector;
    face_detector.load("haarcascade_frontalface_default.xml");

    // initialization
    cv::Mat frame, gray, prev_gray, flow, cflow;
    std::vector<cv::Point2f> points[2];
    std::vector<cv::Rect> faces;
    bool is_face_present = false;

    while(true)
    {
        cap >> frame;
        if(frame.empty())
            break;

        // converstion to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // detect faces 
        face_detector.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

        // verify if a face is present in the frame
        if(!faces.empty())
        {
            is_face_present = true;

            // set up the points for the optical flow
            points[0].clear();
            for(auto & face : faces)
            {
                points[0].emplace_back(face.x + face.width/2, face.y + face.height/2);
            }

            // compute the optical flow
            if(prev_gray.empty())
                gray.copyTo(prev_gray);
            cv::calcOpticalFlowPyrLK(prev_gray, gray, points[0], points[1], cv::noArray(), cv::noArray(), cv::Size(31,31));
            // compute the flow magnitude
            std::vector<double> flow_magnitude;
            for(size_t i = 0; i < points[1].size(); i++)
            {
                double dx = points[1][i].x - points[0][i].x;
                double dy = points[1][i].y - points[0][i].y;
                flow_magnitude.push_back(sqrt(dx*dx + dy*dy));
            }

            // compute the average flow magnitude
            double avg_flow_magnitude = 0.0;
            for(double i : flow_magnitude)
            {
                avg_flow_magnitude += i;
            }
            avg_flow_magnitude /= flow_magnitude.size();

         
            std::cout << "Average flow magnitude: " << avg_flow_magnitude << std::endl;

            // check if the average flow magnitude is above threshold
            if(avg_flow_magnitude > 5.0)
            {
                std::cout << "LIVE" << std::endl;
            }
            else
            {
                std::cout << "FAKE" << std::endl;
            }

            // draw flow
            cflow = frame.clone();
            for(size_t i = 0; i < points[1].size(); i++)
            {
                cv::line(cflow, points[0][i], points[1][i], cv::Scalar(0,255,0), 2);
                cv::circle(cflow, points[1][i], 2, cv::Scalar(0,255,0), -1);
            }
        }
        else
        {
            is_face_present = false;
        }

        
        cv::imshow("Frame", cflow);
        
        video.write(cflow);
        
        cv::swap(prev_gray, gray);
        
        if(cv::waitKey(1) == 27)
            break;
    }
    }


    // release the video capture and writer objects
    cap.release();
    video.release();

    cv::destroyAllWindows();

    return 0;
}

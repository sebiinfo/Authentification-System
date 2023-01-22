#include "model.hpp"
#include "../Localization/localizer_cascade.hpp"
#include "../Classification/classifier.hpp"
#include "../Classification/decisiontree.hpp"
#include "../Classification/knn.hpp"
#include "../Localization/localizer.hpp"
#include "../Vectorization/fisher.hpp"
#include "../Vectorization/vectorizer.hpp"
#include <cassert>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

static void debug_print(cv::Mat temp)
{
    std::cout << "temp.dims = " << temp.dims << " temp.size = [";
    for (int i = 0; i < temp.dims; ++i)
    {
        if (i)
            std::cout << " X ";
        std::cout << temp.size[i];
    }
    std::cout << "] temp.channels = " << temp.channels() << std::endl;
}

static int calculate_score(cv::Mat &image, cv::Rect &face)
{
    int x = abs(face.x + face.x + face.height - image.rows);
    int y = abs(face.y + face.y + face.width - image.cols);
    return face.width * face.height * 4 - pow(x, 2) - pow(y, 2);
}

Model::Model(int num_people, int num_feature, int width, int height,
             std::string localizer, std::string vectorizer,
             std::string classifier)
{
    this->num_people = num_people;
    this->num_feature = num_feature;
    this->width = width;
    this->height = height;

	if (localizer == "Basic" || localizer == "conformity" || localizer == "Conformity" || localizer=="Fancy" || localizer=="fancy")
    {
//		this->localizer = new Cascade_Localizer(localizer);
		this->localizer = new Cascade_Localizer(localizer, width, height, 10);
    }
    else
    {
        assert(false);
    }

    if (vectorizer == "Fisher")
    {
        this->vectorizer = new Fisher(num_people, num_feature);
    }
    else
    {
        assert(false);
    }

    // if (classifier == "KNN") {this->classifier = new KNN(num_people, num_feature);}
    // else {assert(false);}
    // KNN constructor has 4 arguments. For the moment leave this commented.

    this->load_train_images();
    debug_print(train_images[0]);

    std::cout << "\n";

    std::cout << "Training the Vectorizer" << std::endl;
    if (vectorizer == "Fisher")
    {
        this->vectorizer =
            new Fisher(num_people, num_feature, train_images, train_labels);
    }
    else
    {
        assert(false);
    }
    //    std::cout<<"training labels are \n";
    //    for (auto i: train_labels){
    //        std::cout<<i<<" ";
    //    }

    std::cout << "Training the Classifier" << std::endl;

    if (classifier == "KNN")
    {
        this->classifier =
            new KNN(num_people, num_feature, train_images, train_labels);
    }
    else if (classifier == "DecisionTree")
    {
        this->classifier = new DecisionTree(num_people, num_feature,
                                            train_images, train_labels);
    }
    else
    {
        assert(false);
    }
    // KNN constructor has 4 arguments. For the moment leave this commented.
    //    std::cout<<"trained labels are \n";
    //    for (auto i: this->classifier->labels){
    //        std::cout<<i<<" ";
    //    }

    //    this->vectorizer->train(train_images, train_labels);

    //    this->classifier->train(train_images, train_labels);
}

Model::~Model()
{
	delete localizer;
    delete vectorizer;
    delete classifier;
}

std::vector<int> Model::predict(cv::Mat &image, std::vector<cv::Rect> &faces)
{
	//std::vector<cv::Mat> in_faces = localizer->Transform(image);
    std::vector<cv::Mat> in_faces;
    in_faces.push_back(image);
    std::vector<int> output;
    for (int i = 0; i < in_faces.size(); i++)
    {
        // std::cout << "\n\n\nVectorizing\n";
        cv::Mat numerical_reps = vectorizer->vectorize(in_faces[i]);
        // std::cout << "Numerical rep is\n" << numerical_reps << std::endl;
        // debug_print(numerical_reps);
        // std::cout << "Classifying\n";
        output.push_back(classifier->classify(numerical_reps));
    }
    // std::cout << "Finished\n";
    return output;
}

//int Model::predict_most_likely(cv::Mat &image)
//{
//    std::vector<cv::Rect> faces;
//    std::vector<int> temp = predict(image, faces);
//    if (temp.size() == 0)
//    {
//        return -1;
//    }
//    else
//    {
//        int score = -1e9;
//        int output = -1;
//        for (int i = 0; i < temp.size(); i++)
//        {
//            if (calculate_score(image, faces[i]) > score)
//            {
//                output = i;
//                score = calculate_score(image, faces[i]);
//            }
//        }
//        return temp[output];
//    }
//    // in future we need to use the rect and consider which face is the main
//    // one.
//}

void Model::load_train_images()
{
    std::cout << "Loading Training Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++)
    {
        base_filename =
            "./resources/yalefaces/train/" + std::to_string(label) + "/";
        for (int i = 1; i <= 9; i++)
        {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            cv::Mat image = cv::imread(filename);
			cv::Mat flat_image = image.reshape(1, 1);
			train_images.push_back(flat_image);
            train_labels.push_back(label);
        }
    }
    std::cout << "Finished Loading" << std::endl;
}

//The work for this code was shared equaly by Cezara Petrui(cezarapetrui19) and Alexandru Serban (alexserban2002)

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include "eigenvalue_decomposition.cpp"
#include <opencv2/core/base.hpp>

class LinearDiscriminantAnalysis {
    /* The class has as the attributes the eigenvectors and eigenvalues of the lda,
     * eigenvectss and respectively eigenvals, the number of features of the lda,
     * num_components and a bool dataAsRow, which is true if each row represents a
     * sample and each column represents a feature
     */

    public:

        LinearDiscriminantAnalysis();

        LinearDiscriminantAnalysis(int num_components);

        LinearDiscriminantAnalysis(cv::InputArrayOfArrays images, cv::InputArray labels, int num_components);

        ~LinearDiscriminantAnalysis();

        void compute(cv::InputArrayOfArrays images, cv::InputArray labels);
        //computes the discriminants for data in images and labels

        cv::Mat get_eigenvects();

        cv::Mat get_eigenvals();

        cv::Mat project(cv::InputArrayOfArrays images);

        //projects samples into the space
        static cv::Mat subspaceProject(cv::InputArray space, cv::InputArray mean, cv::InputArray images);


    protected:

        //performs the Linear Discriminant Analysis
        void lda (cv::InputArrayOfArrays images, cv::InputArray labels);

        cv::Mat eigenvals;
        cv::Mat eigenvects;
        int num_components;
        bool dataAsRow=true;
};

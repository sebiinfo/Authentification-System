//The work for this code was shared equalyl with my colleague Alexandru Serban (alexserban2002)

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include "eigenvalue_decomposition.cpp"
#include <opencv2/core/base.hpp>

cv::Mat eigenvectors;
cv::Mat eigenvalues;

static void sortMatrixColumnsByIndices(cv::InputArray input, cv::InputArray indices, cv::OutputArray output){
    cv::Mat input_1=input.getMat();
    std::vector<int> indices_1=indices.getMat();
    output.create(input_1.rows,input_1.cols,input_1.type());
    cv::Mat output_1 = output.getMat();
    for (size_t i=0; i<indices_1.size();i++){
        cv::Mat col_init = input_1.col(indices_1[i]);
        cv::Mat col_sorted = output_1.col((int) i);
        col_init.copyTo(col_sorted);
    }
}

static cv::Mat sortMatrixColumnsByIndices(cv::InputArray input, cv::InputArray indices){
    cv::Mat output;
    sortMatrixColumnsByIndices(input,indices,output);
    return output;
}



void lda(cv::InputArray images, cv::InputArray labels, int num_components){
    cv::Mat images_1=images.getMat();
    std::vector<int> labels_1=labels.getMat();
    cv::Mat data;
    images_1.convertTo(data,CV_64FC1);
    std::vector<int> index_labels(labels_1.size());
    std::vector<std::pair<int,int>> labels_copy;
    for (int i=0;i<(int)labels_1.size();i++){
        labels_copy.push_back({labels_1[i],i});
    }
    std::sort(labels_copy.begin(),labels_copy.end());
    int category = 0;
    for (int i=0;i<(int)labels_copy.size();i++){
        if (i==0 || labels_copy[i].first!=labels_copy[i-1].first){
            category++;
        }
        index_labels[labels_copy[i].second]=category-1;
    }
    int num_rows=data.rows;
    int num_cols=data.cols;
    if ((num_components>category-1) || (num_components<=0)){
        num_components=category-1;
    }
    cv::Mat avgTotal = cv::Mat::zeros(1,num_cols,data.type());
    std::vector<cv::Mat> avgClass(category);
    std::vector<int> num_class(category);
    for(int i=0;i<category;i++){
        num_class[i]=0;
        avgClass[i]=cv::Mat::zeros(1,num_cols,data.type());
    }
    for (int i=0;i<num_rows;i++){
        cv::Mat row_i=data.row(i);
        int category_index = index_labels[i];
        add(avgTotal,row_i,avgTotal);
        add(avgClass[category_index],row_i,avgClass[category_index]);
        num_class[category_index]++;
    }
    avgTotal.convertTo(avgTotal,avgTotal.type(),1.0 / static_cast<double> (num_rows));
    for (int i=0;i<num_rows;i++){
        cv::Mat row_i=data.row(i);
        int category_index = index_labels[i];
        subtract(row_i,avgClass[category_index],row_i);
    }
    cv::Mat scatter_within= cv::Mat::zeros(num_cols,num_cols,data.type());
    mulTransposed(data,scatter_within,true);
    cv::Mat scatter_between= cv::Mat::zeros(num_cols,num_cols,data.type());
    for (int i=0;i<category;i++){
        cv::Mat dif;
        subtract(avgClass[i],avgTotal,dif);
        mulTransposed(dif,dif,true);
        add(scatter_between,dif,scatter_between);
    }
    cv::Mat scatter_within_inverse= scatter_within.inv();
    cv::Mat solve_matrix;
    gemm(scatter_within_inverse,scatter_between,1.0,cv::Mat(),0.0,solve_matrix);
    cv::EigenvalueDecomposition decomp(solve_matrix);
    eigenvalues=decomp.eigenvalues().reshape(1,1);
    eigenvectors=decomp.eigenvectors();
    std::vector<int> indices_sorted = argsort(eigenvalues,false);
    eigenvalues=sortMatrixColumnsByIndices(eigenvalues,indices_sorted);
    eigenvectors=sortMatrixColumnsByIndices(eigenvectors,indices_sorted);
    eigenvalues=cv::Mat(eigenvalues,cv::Range::all(),cv::Range(0,num_components));
    eigenvectors=cv::Mat(eigenvectors,cv::Range::all(),cv::Range(0,num_components));
}


static cv::Mat asRowMatrix(cv::InputArrayOfArrays images, int array_type, double alpha=1, double beta=0){
    size_t number_of_samples=images.total();
    if (number_of_samples==0){
        return cv::Mat();
    }
    size_t dim_reshaped=images.getMat(0).total();
    cv::Mat data((int)number_of_samples,(int) dim_reshaped,array_type);
    for (int i=0;i<(int)number_of_samples;i++){
        cv::Mat row_i=data.row(i);
        if (images.getMat(i).isContinuous()){
            images.getMat(i).reshape(1,1).convertTo(row_i,array_type,alpha,beta);
        }
        else{
            images.getMat(i).clone().reshape(1,1).convertTo(row_i,array_type,alpha,beta);
        }
    }
    return data;
}


void compute(cv::InputArray images, cv::InputArray labels,int num_components){
    if (images.kind()==cv::_InputArray::MAT){
        lda(images.getMat(),labels,num_components);
    }
    else{
        lda(asRowMatrix(images,CV_64FC1),labels,num_components);
    }
}


cv::Mat subspaceProject(cv::InputArray weight, cv::InputArray mean, cv::InputArray images){
    cv::Mat weight_1=weight.getMat();
    cv::Mat mean_1=mean.getMat();
    cv::Mat images_1=images.getMat();
    int number_rows=images_1.rows;
    int number_cols=images_1.cols;
    cv::Mat X,Y;
    images_1.convertTo(X,weight_1.type());
    if (!mean.empty()){
        for (int i=0;i<number_rows;i++){
            cv::Mat row_i=X.row(i);
            subtract(row_i,mean_1.reshape(1,1),row_i);
        }
    }
    gemm(X,weight_1,1.0,cv::Mat(),0.0,Y);
    return Y;
}


cv::Mat project(cv::InputArray images){
    //bool dataAsRow=true;
    //cv::
    //if (_dataAsRow){ // true if each row represents a sample and each column represents a feature
    return subspaceProject(eigenvectors,cv::Mat(),images);
   // }
    //else{
    //return subspaceProject(eigenvectors, cv::Mat(), images.getMat().t());
//}

}

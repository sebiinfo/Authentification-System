//
// Created by sebastian_simon on 01/12/2022.
//

#ifndef AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
#define AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#endif //AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#include <iostream>
#include <vector>

struct datavect{
    int coordinate,id;
};

class Data{
public:
    std::vector<std::vector<double>> get_data() {return dataset;}

private:
    int dimension, nr_vect;
    std::vector<std::vector<double>> dataset;

};
double dist_vect(double l[]){};
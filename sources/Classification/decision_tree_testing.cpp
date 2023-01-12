#include "decision_tree_testing.hpp"
Testing_Node::Testing_Node (int num_people, int dim): num_people{num_people}, dim{dim} {
   this->labels = RandomFunctions::generate_random_id(dim);
   this->num_reps = RandomFunctions::generate_faces(num_people, dim);
}

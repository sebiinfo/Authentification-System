
#include "decision_tree_testing.hpp"

#include <iostream>

Testing_Node::Testing_Node(int num_people, int dim)
    : num_people{num_people}, dim{dim} {
   this->labels = RandomFunctions::generate_random_id(dim);
   this->num_reps = RandomFunctions::generate_faces(num_people, dim);
   node_instance = Node(num_people, dim, num_reps, labels);
}

void Testing_Node::test_get_best_split() {}

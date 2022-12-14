# Authentication System

## Functionalities

The aim of this project is to develop a Facial Recognition system that can distingish the 
members of this group from anyone else.

It will have a Desktop App which accesses the camera of the computer and try to detect your face. 
As a fallback it will have a usual login system with username and password.

## Deadlines and deliverables

- Install OpenCV - 4/12/22
- Complete sketch of UI desktop application - 4/12/22

## Software Architecture

- This project will heavily depend on the OpenCV library for the Algorithm and QT for the Graphical Interface.

### Internal Guidelines

- The implementation of all features should be split in the `sources` folder. This folder should be subdivided in folders of name `feature-name` which should contain the `.cpp` and `.hpp` files used to implement this, and only this, specific feature.
- DO NOT USE `using namespace std/cv`.
- Prefereably opt for snake_case and descriptive names while naming variables.

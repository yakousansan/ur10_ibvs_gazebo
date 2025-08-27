#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/algorithm/kinematics.hpp"
 
#include <iostream>
 
 
int main(int argc, char ** argv)
{
  using namespace pinocchio;
    
  // 加载URDF文件
  const std::string urdf_filename =std::string("/home/p/ws_demo2/src/ur_description/urdf/ur10.urdf");
  // Load the urdf model
  Model model;
  pinocchio::urdf::buildModel(urdf_filename, model);
  std::cout << "model name: " << model.name << std::endl;
  // Create data required by the algorithms
  Data data(model);
 
  // Sample a random configuration
  Eigen::VectorXd q(6);
  q << 0, -1.57,1.57,-1.57,-1.57,1.57;
  for (JointIndex idx= 1; idx < model.njoints; ++idx){
    std::cout << "Joint"<<idx<<":"<<model.name[idx] << std::endl;
  }

  // Perform the forward kinematics over the kinematic tree
  forwardKinematics(model, data, q);
   JointIndex end_effector_id = model.njoints - 1;
   std::cout << "End effector " << model.names[end_effector_id] << ") position: "
            << data.oMi[end_effector_id].translation().transpose() << std::endl;

  // Print out the placement of each joint of the kinematic tree
  for (JointIndex joint_id = 0; joint_id < (JointIndex)model.njoints; ++joint_id)
    std::cout << std::setw(24) << std::left << model.names[joint_id] << ": " << std::fixed
              << std::setprecision(2) << data.oMi[joint_id].translation().transpose() << std::endl;
}

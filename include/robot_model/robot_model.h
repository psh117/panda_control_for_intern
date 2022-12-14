#pragma once

// Copyright (c) 2018-2022 Seoul National University - Suhan Park (psh117@snu.ac.kr) @ DYROS 
// Use of this source code is governed by the Apache-2.0 license, see LICENSE

#include <memory>
#include <Eigen/Dense>

class RobotModel
{
public:
  RobotModel() {}

  virtual Eigen::MatrixXd getJacobianMatrix(const Eigen::Ref<const Eigen::VectorXd> &q) const = 0;
  virtual Eigen::MatrixXd getJacobianMatrix(const Eigen::Ref<const Eigen::VectorXd> &q, const Eigen::Ref<const Eigen::Vector3d> & tool_tf) const = 0;
  virtual Eigen::Vector3d getTranslation(const Eigen::Ref<const Eigen::VectorXd> &q) const = 0;
  virtual Eigen::Vector3d getTranslation(const Eigen::Ref<const Eigen::VectorXd> &q, const Eigen::Ref<const Eigen::Vector3d> & tool_tf) const = 0;
  virtual Eigen::Matrix3d getRotation(const Eigen::Ref<const Eigen::VectorXd> &q) const = 0;
  virtual Eigen::Isometry3d getTransform(const Eigen::Ref<const Eigen::VectorXd> &q) const = 0; 
  virtual Eigen::Isometry3d getTransform(const Eigen::Ref<const Eigen::VectorXd> &q, const Eigen::Ref<const Eigen::Vector3d> & tool_tf) const = 0;
  virtual Eigen::MatrixXd getJointLimit() const = 0;
  virtual Eigen::VectorXd getInitialConfiguration() const = 0;

  virtual int getDof() = 0;

  Eigen::Vector3d getPhi(const Eigen::Matrix3d a, const Eigen::Matrix3d b)
  {
    Eigen::Vector3d phi;
    Eigen::Vector3d s[3], v[3], w[3];

    for (int i = 0; i < 3; i++) {
      v[i] = a.block<3, 1>(0, i);
      w[i] = b.block<3, 1>(0, i);
      s[i] = v[i].cross(w[i]);
    }
    phi = s[0] + s[1] + s[2];
    phi = -0.5* phi;

    return phi;
  }
};

typedef std::shared_ptr<RobotModel> RobotModelPtr;

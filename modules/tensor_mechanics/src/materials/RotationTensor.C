#include "RotationTensor.h"
#include "libmesh/libmesh.h"

RotationTensor::RotationTensor(const RealVectorValue & Euler_angles)
{
  update(Euler_angles);
}

void
RotationTensor::update(const RealVectorValue & Euler_angles)
{
  Real phi_1 = Euler_angles(0)*(libMesh::pi/180.0);
  Real Phi = Euler_angles(1)*(libMesh::pi/180.0);
  Real phi_2 = Euler_angles(2)*(libMesh::pi/180.0);

  Real c1 = std::cos(phi_1);
  Real c2 = std::cos(Phi);
  Real c3 = std::cos(phi_2);

  Real s1 = std::sin(phi_1);
  Real s2 = std::sin(Phi);
  Real s3 = std::sin(phi_2);

//doing a Z1, X2, Z3 rotation
  //RealTensorValue is formed row-wise

  _coords[0] = c1*c3 - c2*s1*s3; //R11
  _coords[3] = -c1*s3 - c2*c3*s1; //R12
  _coords[6] = s1*s2; //R13

  _coords[1] = c3*s1 + c1*c2*s3; //R21
  _coords[4] = c1*c2*c3 - s1*s3; //R22
  _coords[7] = -c1*s2; //R23

  _coords[2] = s2*s3; //R31
  _coords[5] = c3*s2; //R32
  _coords[8] = c2; //R33
}

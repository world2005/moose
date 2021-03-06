#include "CrystalPlasticityRotationOutAux.h"

template<>
InputParameters validParams<CrystalPlasticityRotationOutAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<std::string>("rotout_file_name","rot.out","Name of rotation output file: Default rot.out");
  params.addParam<int>("output_frequency",1,"Frequency of Output");
  return params;
}

CrystalPlasticityRotationOutAux::CrystalPlasticityRotationOutAux( const std::string & name, InputParameters parameters ) :
  AuxKernel( name, parameters ),
  _rotout_file_name(getParam<std::string>("rotout_file_name")),
  _out_freq(getParam<int>("output_frequency")),
  _update_rot( getMaterialProperty<RankTwoTensor>("update_rot"))
{}

Real
CrystalPlasticityRotationOutAux::computeValue()
{
  std::ofstream fileout;


  if(_t_step % _out_freq == 0)
    {
      fileout.open(_rotout_file_name.c_str(),std::ofstream::out | std::ofstream::app);
      fileout << _t_step <<" " << _dt <<" "<< _JxW[_qp]<<" "<<_update_rot[_qp](0,0)<<" "<<_update_rot[_qp](0,1)<<" "<<_update_rot[_qp](0,2)<<" "<<_update_rot[_qp](1,0)<<" "<<_update_rot[_qp](1,1)<<" "<<_update_rot[_qp](1,2)<<" "<<_update_rot[_qp](2,0)<<" "<<_update_rot[_qp](2,1)<<" "<<_update_rot[_qp](2,2)<<"\n";
    }
  return 0;
}

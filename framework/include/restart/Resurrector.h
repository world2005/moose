/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef RESURRECTOR_H
#define RESURRECTOR_H

#include "Moose.h"
#include "CheckpointOutput.h"
#include "MaterialPropertyIO.h"
#include "RestartableDataIO.h"

#include <string>
#include <list>

class FEProblem;

/**
 * Class for doing restart.
 *
 * It takes care of writing and reading the restart files.
 */
class Resurrector
{
public:
  Resurrector(FEProblem & fe_problem);
  virtual ~Resurrector();

  /**
   * Set the file base name from which we will restart
   * @param file_base The file base name of a restart file
   */
  void setRestartFile(const std::string & file_base);

  /**
   * Perform a restart from a file
   */
  void restartFromFile();

  void restartStatefulMaterialProps();

  void restartRestartableData();

  /**
   * Set the number of restart file to store
   * @param num_files Number of files to keep around
   */
  void setNumRestartFiles(unsigned int num_files);

  /**
   * Gets the number of restart files to save
   * @return the number of files to keep around
   */
  unsigned int getNumRestartFiles();

  /**
   * Write out a restart file and rotate already written ones
   */
  void write();

protected:

  /// Reference to a FEProblem being restarted
  FEProblem & _fe_problem;

  /// name of the file that we restart from
  std::string _restart_file_base;

  /// number of checkpoint files to keep around
  unsigned int _num_checkpoint_files;
  /// Checkpoint writer
  CheckpointOutput _checkpoint;
  /// Stateful material property output
  MaterialPropertyIO _mat;
  /// Restartable Data
  RestartableDataIO _restartable;

  /// list of file names we keep around
  std::list<std::string> _restart_file_names;

  static const std::string MAT_PROP_EXT;
  static const std::string RESTARTABLE_DATA_EXT;
};

#endif /* RESURRECTOR_H */

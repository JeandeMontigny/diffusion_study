// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef DIFFUSION_STUDY_H_
#define DIFFUSION_STUDY_H_

#include "biodynamo.h"
#include "my_cell.h"
#include "cell_bm.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {

  auto set_param = [&](Param* param) {
    // Create an artificial bounds for the simulation space
    param->bound_space_ = true;
    param->min_bound_ = 0;
    param->max_bound_ = 1300;
    param->run_mechanical_interactions_ = true;
  };

  Simulation simulation(argc, argv, set_param);

  // Define initial model - in this example: single cell at origin
  auto* rm = simulation.GetResourceManager();
  auto* param = simulation.GetParam();
  auto* scheduler = simulation.GetScheduler();

  MyCell* cell = new MyCell({40, 40, 40});
  cell->SetDiameter(8);
  cell->SetInternalClock(0);
  cell->AddBiologyModule(new Substance_secretion_BM());
  rm->push_back(cell);

  // MyCell* cell2 = new MyCell({120, 50, 50});
  // cell2->SetDiameter(8);
  // cell2->SetInternalClock(0);
  // cell2->AddBiologyModule(new Substance_secretion_BM());
  // rm->push_back(cell2);

  int spacing = 4;
  int resolution = param->max_bound_/spacing;
  // ratio diffusion_coef/spacing/spacing = 0.125
  double diffusion_coef = 0.125*spacing*spacing;
  double decay_const = 0.015625*spacing;

  ModelInitializer::DefineSubstance(dg_0_, "substance", diffusion_coef, decay_const, resolution);

  ofstream diffu_center_output;
  diffu_center_output.open("diffu_cell_center"+to_string(diffusion_coef)+"_"+to_string(decay_const)+"_"+spacing+".txt");

  // Run simulation for one timestep
  for (int step = 0; step < 100; step++) {
    scheduler->Simulate(1);
    DiffusionGrid* dg = nullptr;

    dg = rm->GetDiffusionGrid("substance");
    double cell_center_concentration = dg->GetConcentration({40, 40, 40});
    diffu_center_output << step << " " << cell_center_concentration << "\n";
  }

  ofstream diffu_longi_output;
  diffu_longi_output.open("longitudinal_"+to_string(diffusion_coef)+"_"
                          +to_string(decay_const)+"_"+spacing+".txt");
  DiffusionGrid* dg = nullptr;
  dg = rm->GetDiffusionGrid("substance");
  double max_conc = 0;
  for (double dist = 0; dist < 80; dist = dist+0.5) {
    double concentration = dg->GetConcentration({dist, 40, 40});
    if (concentration > max_conc) { max_conc = concentration; }
    diffu_longi_output << dist << " " << concentration << "\n";
  }
  diffu_center_output.close();
  diffu_longi_output.close();

  std::cout << "max concentration: " << max_conc << std::endl;

  std::cout << "done" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_STUDY_H_

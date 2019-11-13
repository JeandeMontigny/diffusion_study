#ifndef CELL_BM_
#define CELL_BM_

#include "biodynamo.h"
#include "my_cell.h"

namespace bdm {

 enum Substances { dg_0_ };

 // Define cell behavior for substance secretion
 struct Substance_secretion_BM : public BaseBiologyModule {
   BDM_STATELESS_BM_HEADER(Substance_secretion_BM, BaseBiologyModule, 1);

 public:
   Substance_secretion_BM() : BaseBiologyModule(gAllEventIds) {}

   void Run(SimObject* so) override {
     if (auto* cell = dynamic_cast<MyCell*>(so)) {
       auto* rm = Simulation::GetActive()->GetResourceManager();

       DiffusionGrid* dg = nullptr;
       // use corresponding diffusion grid

       dg = rm->GetDiffusionGrid("substance");
       auto& secretion_position = cell->GetPosition();
       dg->IncreaseConcentrationBy(secretion_position, 1);
     }
   } // end Run()
 }; // end biologyModule Substance_secretion_BM


 // Define cell behavior for dendrites creation
 struct Internal_clock_BM : public BaseBiologyModule {
   BDM_STATELESS_BM_HEADER(Internal_clock_BM, BaseBiologyModule, 1);

 public:
   Internal_clock_BM() : BaseBiologyModule(gAllEventIds) {}

   void Run(SimObject* so) override {
     if (auto* cell = dynamic_cast<MyCell*>(so)) {
       // update cell internal clock
       cell->SetInternalClock(cell->GetInternalClock() + 1);
     } // end if MyCell
   } // end Run()
 }; // end biologyModule Internal_clock_BM


} // end namespace bdm

#endif

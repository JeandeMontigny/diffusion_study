#ifndef MY_CELL_H_
#define MY_CELL_H_

namespace bdm {

  // Define custom cell MyCell extending Cell
  class MyCell : public Cell {
    BDM_SIM_OBJECT_HEADER(MyCell, Cell, 1, internal_clock_);

   public:
    MyCell() : Base() {}

    virtual ~MyCell() {}

    MyCell(const Double3& position) : Base(position) {}

    /// Default event constructor
    MyCell(const Event& event, SimObject* other, uint64_t new_oid = 0)
        : Base(event, other, new_oid) {}

    void SetInternalClock(int t) { internal_clock_ = t; }
    int GetInternalClock() const { return internal_clock_; }

   private:
     int internal_clock_ = 0;
  }; // end MyCell definition
} // end namespace bdm

#endif

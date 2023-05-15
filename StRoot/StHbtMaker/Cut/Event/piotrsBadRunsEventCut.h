#ifndef PIOTRSBADRUNSEVENTCUT_H
#define PIOTRSBADRUNSEVENTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsBadRunsEventCut : public StHbtEventCut {
  public:
   piotrsBadRunsEventCut();
   virtual ~piotrsBadRunsEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsBadRunsEventCut* Clone();

  private:
   bool isOnList(int, const Int_t*, int);

   static const Int_t n_bad_run_numbers[7];
   static const Int_t bad_run_list_7GeV[328];
   static const Int_t bad_run_list_11GeV[27];
   static const Int_t bad_run_list_19GeV[134];
   static const Int_t bad_run_list_27GeV[34];
   static const Int_t bad_run_list_39GeV[38];
   static const Int_t bad_run_list_62GeV[105];
   static const Int_t bad_run_list_200GeV[219];

   ClassDef(piotrsBadRunsEventCut, 0)
};

#endif

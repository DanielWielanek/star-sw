TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// Top/cal/org_ped_bsmdp_h Allocated rows: 1  Used rows: 1  Row size: 24 bytes
//  Table: emc_calib_header_st[0]--> emc_calib_header_st[0]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_emc_calib_header")) return 0;
emc_calib_header_st row;
St_emc_calib_header *tableSet = new St_emc_calib_header("org_ped_bsmdp_h",1);
//
memset(&row,0,tableSet->GetRowSize());
    row.date	 = 1667329024; // date ;
    row.time	 = 2071134331; // time ;
    row.flag	 =         -1; // flag ;
    row.func	 =          0; // function selection ;
    row.det	 =          4; // see emc_def.h ;
    row.nmodule	 =        120; // see emc_def.h ;
    row.neta	 =         10; // see emc_def.h ;
    row.nsub	 =         15; // see emc_def.h ;
tableSet->AddAt(&row,0);
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}

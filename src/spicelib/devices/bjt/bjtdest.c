/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/*
 * This routine deletes all BJTs from the circuit and frees
 * all storage they were using.
 */

#include "ngspice/ngspice.h"
#include "bjtdefs.h"
#include "ngspice/suffix.h"


void
BJTdestroy(GENmodel **inModel)
{
    BJTmodel *mod = *(BJTmodel**) inModel;

    while (mod) {
        BJTmodel *next_mod = BJTnextModel(mod);
        BJTinstance *inst = BJTinstances(mod);
        while (inst) {
            BJTinstance *next_inst = BJTnextInstance(inst);
            FREE(inst->BJTsens);
            GENinstanceFree(GENinstanceOf(inst));
            inst = next_inst;
        }
        GENmodelFree(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}

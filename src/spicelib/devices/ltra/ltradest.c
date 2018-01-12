/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1990 Jaijeet S. Roychowdhury
**********/

#include "ngspice/ngspice.h"
#include "ltradefs.h"
#include "ngspice/suffix.h"


void
LTRAdestroy(GENmodel **inModel)
{
    LTRAmodel *mod = *(LTRAmodel **) inModel;

    while (mod) {
        LTRAmodel *next_mod = LTRAnextModel(mod);
        LTRAinstance *inst = LTRAinstances(mod);
        while (inst) {
            LTRAinstance *next_inst = LTRAnextInstance(inst);
            GENinstanceFree(GENinstanceOf(inst));
            inst = next_inst;
        }
        GENmodelFree(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}

/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 S. Hwang
**********/

#include "ngspice/ngspice.h"
#include "mesdefs.h"
#include "ngspice/suffix.h"


void
MESdestroy(GENmodel **inModel)
{
    MESmodel *mod = *(MESmodel**) inModel;

    while (mod) {
        MESmodel *next_mod = MESnextModel(mod);
        MESinstance *inst = MESinstances(mod);
        while (inst) {
            MESinstance *next_inst = MESnextInstance(inst);
            GENinstanceFree(GENinstanceOf(inst));
            inst = next_inst;
        }
        GENmodelFree(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}

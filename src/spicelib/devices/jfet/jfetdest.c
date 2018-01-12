/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "ngspice/ngspice.h"
#include "jfetdefs.h"
#include "ngspice/suffix.h"


void
JFETdestroy(GENmodel **inModel)
{
    JFETmodel *mod = *(JFETmodel**) inModel;

    while (mod) {
        JFETmodel *next_mod = JFETnextModel(mod);
        JFETinstance *inst = JFETinstances(mod);
        while (inst) {
            JFETinstance *next_inst = JFETnextInstance(inst);
            GENinstanceFree(GENinstanceOf(inst));
            inst = next_inst;
        }
        GENmodelFree(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}

/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1998 Samuel Fung, Dennis Sinitsky and Stephen Tang
File: b3soipddest.c          98/5/01
Modified by Paolo Nenzi 2002
**********/

/*
 * Revision 2.2.3  02/3/5  Pin Su
 * BSIMPD2.2.3 release
 */

#include "ngspice/ngspice.h"
#include "b3soipddef.h"
#include "ngspice/suffix.h"


void
B3SOIPDdestroy(GENmodel **inModel)
{
    B3SOIPDmodel *mod = *(B3SOIPDmodel**) inModel;

    while (mod) {
        B3SOIPDmodel *next_mod = B3SOIPDnextModel(mod);
        B3SOIPDinstance *inst = B3SOIPDinstances(mod);
        while (inst) {
            B3SOIPDinstance *next_inst = B3SOIPDnextInstance(inst);
            GENinstanceFree(GENinstanceOf(inst));
            inst = next_inst;
        }
        GENmodelFree(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}

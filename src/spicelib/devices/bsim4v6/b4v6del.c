/**** BSIM4.6.2 Released by Wenwei Yang 07/31/2008 ****/

/**********
 * Copyright 2006 Regents of the University of California. All rights reserved.
 * File: b4del.c of BSIM4.6.2.
 * Author: 2000 Weidong Liu
 * Authors: 2001- Xuemei Xi, Mohan Dunga, Ali Niknejad, Chenming Hu.
 * Authors: 2006- Mohan Dunga, Ali Niknejad, Chenming Hu
 * Authors: 2007- Mohan Dunga, Wenwei Yang, Ali Niknejad, Chenming Hu
 * Project Director: Prof. Chenming Hu.
 **********/

#include "ngspice/ngspice.h"
#include "bsim4v6def.h"
#include "ngspice/sperror.h"
#include "ngspice/gendefs.h"
#include "ngspice/suffix.h"


int
BSIM4v6delete(GENmodel *model, IFuid name, GENinstance **kill)
{
    for (; model; model = model->GENnextModel) {
        GENinstance **prev = &(model->GENinstances);
        GENinstance *here = *prev;
        for (; here; here = *prev) {
            if (here->GENname == name || (kill && here == *kill)) {
                *prev = here->GENnextInstance;
                GENinstanceFree(here);
                return OK;
            }
            prev = &(here->GENnextInstance);
        }
    }

    return E_NODEV;
}

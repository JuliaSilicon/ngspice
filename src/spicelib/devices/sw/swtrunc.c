/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: 2000 AlansFixes
**********/

#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"
#include "swdefs.h"


int
SWtrunc(GENmodel *inModel, CKTcircuit *ckt, double *timeStep)
{
    SWmodel *model = (SWmodel *) inModel;
    SWinstance *here;
    double   lastChange, maxChange, maxStep, ref;
    const double reltime = 100 * DBL_EPSILON;

    for (; model; model = SWnextModel(model))
        for (here = SWinstances(model); here; here = SWnextInstance(here)) {
            lastChange =
                ckt->CKTstate0[here->SWctrlvalue] -
                ckt->CKTstate1[here->SWctrlvalue];
            if (ckt->CKTstate0[here->SWswitchstate] < 0) {
                ref = model->SWvThreshold + fabs(model->SWvHysteresis);
                if (ckt->CKTstate0[here->SWctrlvalue] < ref && lastChange > 0) {
                    maxChange =
                        (ref - ckt->CKTstate0[here->SWctrlvalue]) * 0.75;
                    maxStep = maxChange / lastChange * ckt->CKTdeltaOld[0];
                    if (maxStep < ckt->CKTtime * reltime)
                        maxStep = ckt->CKTtime * reltime;
                    if (maxStep < ckt->CKTdelmin)
                        maxStep = ckt->CKTdelmin;
                    if (*timeStep > maxStep)
                        *timeStep = maxStep;
                }
            } else {
                ref = model->SWvThreshold - fabs(model->SWvHysteresis);
                if (ckt->CKTstate0[here->SWctrlvalue] > ref && lastChange < 0) {
                    maxChange =
                        (ref - ckt->CKTstate0[here->SWctrlvalue]) * 0.75;
                    maxStep = maxChange / lastChange * ckt->CKTdeltaOld[0];
                    if (maxStep < ckt->CKTtime * reltime)
                        maxStep = ckt->CKTtime * reltime;
                    if (maxStep < ckt->CKTdelmin)
                        maxStep = ckt->CKTdelmin;
                    if (*timeStep > maxStep)
                        *timeStep = maxStep;
                }
            }
        }

    return OK;
}

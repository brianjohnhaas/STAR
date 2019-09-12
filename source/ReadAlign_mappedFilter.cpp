#include "ReadAlign.h"
#include <iostream>

void ReadAlign::mappedFilter() {//filter mapped read, add to stats
    unmapType=-1;//mark as mapped
    if ( nW==0 ) {//no good windows
        statsRA.unmappedOther++;
        unmapType=0;
    } else if ( (trBest->maxScore < P.outFilterScoreMin) || (trBest->maxScore < (intScore) (P.outFilterScoreMinOverLread*(Lread-1))) \
              || (trBest->nMatch < P.outFilterMatchNmin)  || (trBest->nMatch < (uint) (P.outFilterMatchNminOverLread*(Lread-1))) ) {//too short
        statsRA.unmappedShort++;
        
        if (trBest->maxScore < P.outFilterScoreMin) {
            unmapType=1;
            cout << "1_filtered: maxScore(" << trBest->maxScore << ") < outFilterScoreMin(" << P.outFilterScoreMin << ")" << endl;

        } else if (trBest->maxScore < (intScore) (P.outFilterScoreMinOverLread*(Lread-1)) ) {
            unmapType=2;
            cout << "2_filtered: maxScore(" << trBest->maxScore << ") < outFilterScoreMinOverLread*(Lread-1) (" << P.outFilterScoreMinOverLread*(Lread-1) << ")" << endl;
            
        } else if (trBest->nMatch < P.outFilterMatchNmin) {
            unmapType=3;
            cout << "3_filtered: nMatch(" << trBest->nMatch  << ") < outFilterMatchNmin(" << P.outFilterMatchNmin << ")" << endl;

        } else if (trBest->nMatch < (uint) (P.outFilterMatchNminOverLread*(Lread-1)) ) {
            unmapType=4;
            cout << "4_filtered: nMatch(" <<  trBest->nMatch  << ") < outFilterMatchNminOverLread*(Lread-1) (" << P.outFilterMatchNminOverLread*(Lread-1) << ")" << endl;
            
        }
        

    } else if ( (trBest->nMM > outFilterMismatchNmaxTotal) || (double(trBest->nMM)/double(trBest->rLength)>P.outFilterMismatchNoverLmax) ) {//too many mismatches
        statsRA.unmappedMismatch++;
        unmapType=5;
        cout << "5_filtered: nMM( " << trBest->nMM << ") > outFilterMismatchNmaxTotal(" << outFilterMismatchNmaxTotal << ") " << endl;


    } else if (nTr > P.outFilterMultimapNmax){//too multi
        statsRA.unmappedMulti++;
        unmapType=6;
        cout << "6_filtered: outFilterMultimapNmax(" << nTr << ") > outFilterMultimapNmax(" << P.outFilterMultimapNmax << ") " << endl;
        
    };
    
    return;
};

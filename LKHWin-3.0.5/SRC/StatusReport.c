#include "LKH.h"
#include "segment.h"

extern Node* potential_intersects[4];

void StatusReport(GainType Cost, double EntryTime, char *Suffix)
{
    if (Penalty) {
        printff("Cost = " GainFormat "_" GainFormat, CurrentPenalty, Cost);
        if (Optimum != MINUS_INFINITY && Optimum != 0) {
            if (ProblemType != CCVRP && ProblemType != TRP &&
                ProblemType != MLP &&
                MTSPObjective != MINMAX && MTSPObjective != MINMAX_SIZE)
                printff(", Gap = %0.4f%%",
                        100.0 * (Cost - Optimum) / Optimum);
            else
                printff(", Gap = %0.4f%%",
                        100.0 * (CurrentPenalty - Optimum) / Optimum);
        }
        printff(", Time = %0.2f sec. %s",
                fabs(GetTime() - EntryTime), Suffix);
		if (ProblemType == PAREA && CurrentPenalty <= 10 && CurrentPenalty > 0) {
			printff("\n");
			printff("Intersection at (N%d, N%d) - (N%d, N%d)\n", potential_intersects[0]->Id, potential_intersects[1]->Id, potential_intersects[2]->Id, potential_intersects[3]->Id);
			printTourDEBUG1();
			//printTourDEBUG2();
		}
    } else {
        printff("Cost = " GainFormat, Cost);
        if (Optimum != MINUS_INFINITY && Optimum != 0)
            printff(", Gap = %0.4f%%", 100.0 * (Cost - Optimum) / Optimum);
        printff(", Time = %0.2f sec. %s%s",
                fabs(GetTime() - EntryTime), Suffix,
                Cost < Optimum ? "<" : Cost == Optimum ? "=" : "");
    }
    printff("\n");
}

int printTourDEBUG1() {
	puts("TOUR_LIST START\n");
	Node *First = &NodeSet[1], *N = First;
	do {
		printf("%d\n", N->Id-1);
	} while ((N = SUCC(SUCC(N))) != First);
	return 1;
}

int printTourDEBUG2() {
	puts("TOUR_CHECK START\n");
	printf("Dim %d; Saved %d", Dimension, DimensionSaved);
	for (int i = 1; i <= Dimension; i++) {
		printf("Node #%d\n", NodeSet[i].Id);
		printf("Coords: X %f; Y %f", NodeSet[i].X, NodeSet[i].Y);
		//printf("Suc: %d; Pred: %d\n", NodeSet[i].Suc->Id, NodeSet[i].Pred->Id);
		//printf("SUC: %d; PRED: %d\n", SUC(&NodeSet[i])->Id, PRED(&NodeSet[i])->Id);
		printf("SUCC: %d; PREDD: %d\n", SUCC(SUCC(&NodeSet[i]))->Id, PREDD(PREDD(&NodeSet[i]))->Id);
	}
	return 1;
}
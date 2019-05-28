#include "LKH.h"
#include "Segment.h"

long long int gcd(long long int a, long long int b) {
	long long int t;
	long long int max = a < b ? b : a;
	long long int min = a < b ? a : b;

	while (min) { t = min; min = max % min; max = t; }
	return max;
}

double compute_slopeD(const Node* N1, const Node* N2) {
	return (N1->Y - N2->Y) / (N1->X - N2->X);
}

double compute_interceptD(const Node * N1, const Node * N2) {
	return N1->Y - compute_slopeD(N1, N2) * N1->X;
}

double Y_CoordinateOfSegmentD(const Node * Norigin, const Node * Nend, double X) {
	if (Norigin->X == Nend->X) {
		return -1; //this should not happen
	}
	return compute_slopeD(Norigin, Nend)* X + compute_interceptD(Norigin, Nend);
}

void simplifyRational(Rational* r) {
	int g = gcd(r->Numerator, r->Denominator);
	if (g) {
		r->Denominator /= g;
		r->Numerator /= g;
	}
	else {
		r->Denominator = 1;
		r->Numerator = 0;
	}
	if (r->Denominator < 0) {
		r->Numerator = -r->Numerator;
		r->Denominator = -r->Denominator;
	}
}

double RtoDouble(Rational r) {
	return ((double) r.Numerator) / ((double) r.Denominator);
}

Rational construnctRat(long long int num, long long int den) {
	Rational r;
	r.Numerator = num;
	r.Denominator = den;
	simplifyRational(&r);
	return r;
}

int RstrictlylessR(Rational a, Rational b) {
	return a.Numerator * b.Denominator < a.Denominator * b.Numerator;
}

int RequalsR(Rational a, Rational b) {
	return a.Numerator* b.Denominator == a.Denominator * b.Numerator;
}

Rational RfromI(long long int a) {
	Rational r;
	r.Numerator = a;
	r.Denominator = 1;
	return r;
}

Rational RmultR(Rational a, Rational b) {
	Rational r;
	r.Numerator = a.Numerator * b.Numerator;
	r.Denominator = a.Denominator * b.Denominator;
	simplifyRational(&r);
	return r;
}

Rational ImultR(long long int a, Rational b) {
	Rational r;
	r.Numerator = b.Numerator * a;
	simplifyRational(&r);
	return r;
}

Rational RdivR(Rational a, Rational b) {
	Rational r;
	r.Numerator = a.Numerator * b.Denominator;
	r.Denominator = a.Denominator * b.Numerator;
	simplifyRational(&r);
	return r;
}

Rational RplusR(Rational a, Rational b) {
	Rational r;
	r.Numerator = a.Numerator * b.Denominator + b.Numerator * a.Denominator;
	r.Denominator = a.Denominator * b.Denominator;
	simplifyRational(&r);
	return r;
}

Rational IplusR(long long int a, Rational b) {
	Rational r;
	r.Numerator = a * b.Denominator + b.Numerator;
	r.Denominator = b.Denominator;
	simplifyRational(&r);
	return r;
}

Rational MinR(Rational a) {
	Rational r;
	r.Numerator = -a.Numerator;
	r.Denominator = a.Denominator;
	return r;
}

Rational RminR(Rational a, Rational b) {
	return RplusR(a, MinR(b));
}


Rational RationalSlope(const Node* N1, const Node* N2) {
	Rational r;
	if ((int)N1->X == (int)N2->X) {
		printf("WARNING: vertical line segment (N%d,N%d)", N1->Id,N2->Id);
		r.Numerator = 1;
		r.Denominator = 0;
		return r;
	}
	r.Numerator = (long long int) N1->Y - (long long int) N2->Y;
	r.Denominator = (long long int) N1->X - (long long int) N2->X;
	//printf("R %lld/%lld ~ %f \n", r.Numerator, r.Denominator, RtoDouble(r));
	simplifyRational(&r);
	//printf("R %lld/%lld ~ %f\n", r.Numerator, r.Denominator, RtoDouble(r));
	return r;
}


Rational RationalIntercept(const Node* a, const Node* b) {
	return RminR(RfromI((long long int) a->Y), RmultR(RfromI((long long int) a->X), RationalSlope(a,b)));
}

Rational RationalIntersectionPointX(Node* a1, Node* a2, Node* b1, Node* b2) {
	return RdivR(RminR(RationalIntercept(a1, a2), RationalIntercept(b1, b2)), 
				RminR(RationalSlope(b1,b2), RationalSlope(a1,a2)));
}

Rational RationalEvaluatePointOnLine(Rational x, Rational slope, Rational intercept) {
	return RplusR(RmultR(slope, x), intercept);
}

Rational RationalSegmentSweepIntersectY(const Node* a, Rational sweepX) {
	//printf("Intersect of (N%d,N%d)\n", a->Id, SUCC(SUCC(a))->Id);
	Rational rslope = RationalSlope(a, SUCC(SUCC(a)));
	//printf("Rslope %lld/%lld ~ %f ?= %f \n", rslope.Numerator, rslope.Denominator, RtoDouble(rslope), compute_slopeD(a, SUCC(SUCC(a))));
	Rational rintercept = RationalIntercept(a, SUCC(SUCC(a)));
	//printf("Rintercept %lld/%lld ~ %f ?= %f\n", rintercept.Numerator, rintercept.Denominator, RtoDouble(rintercept), compute_interceptD(a, SUCC(SUCC(a))));
	Rational res = RationalEvaluatePointOnLine(sweepX, rslope, rintercept);
	//printf("Rres %lld/%lld ~ %f ?= %f \n", res.Numerator, res.Denominator, RtoDouble(res), Y_CoordinateOfSegmentD(a, SUCC(SUCC(a)), RtoDouble(sweepX)));
	return res;
}


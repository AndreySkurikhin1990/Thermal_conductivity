#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <dos.h>
#include <iostream> 
#include <time.h>
using namespace std;
//-----
double *poisMasKoefItom(int, double *, int, char *);
double **vydelPol(int, int, double **, double **, int, int, char *, int, int);
double **opredTempHolGor(double *, double *, int, double, int, double **, int, int, double *, int, double, char *);
double epsisred(double, double *, double *, int, double *, double *, int, int, int, double);
double *opredKTPTverKarkNach(double *, double *, double, double, double, double, int, int, int, int, double *, double *, int, 
	double *, int, int, double *, double *, double *, int, char *, int, int, int, int);
double **napMasEKTPitomNac(double, double, double, double, int, int, char *, int, double, double, double, double *, int, double *, 
	double *, int, double *, double *, int, double *, double *, double *, int, double);
//-----
double **napMasEKTPitomNac(double wmgo, double wsio, double walo, double poritom, int vybves, int vybitom, char *snmi, int dmkoi, 
	double ys0, double tnosci, double dtosci, double *etei, int cem, double *tkusci, double *kusci, int dmkoosci, double *dkoscit, 
	double *dkoscim, int dkoscil, double *ktpvo, double *vte, double *Prvo, int dmkv, double dko)
{
	int cemdu=6, k=0, j=0, f=cemdu, cemi=cem, vfv=0, vsv=0, vpkf=0, isrp=0, fl=0, vrsh=0, vystsha=0;
	double tei0=273.15, *kektpi=new double[dmkoi], templa=11e2+tei0, tki=22.0+tei0, *stchsritom=NULL; 
	double *ektpi=new double[cemi], *kttki=NULL;
	if ((!kektpi) || (!ektpi)) { cout << snmi << endl; k=getchar(); exit(1); }
	kektpi=poisMasKoefItom(vybitom, kektpi, dmkoi, snmi);
	double hf=1e0, g=0.0, s=0.0, t=0.0, *po=NULL, nf=0.0, tn=0.0, e=1e-6;
	//-----
	double **mu=new double*[f], **muv=new double*[f];
	double *qobi=NULL, *tholi=NULL, *tgori=NULL;
	if ((!mu) || (!muv)) { cout << snmi << endl; k = getchar(); exit(1); }
	for (k=0; k<f; k++) { po=new double[cemi]; if (!po) { cout << snmi << endl; k=getchar(); exit(1); } muv[k]=po; } 
	for (k=0; k<cemi; k++) { t=etei[k]; s=0.0; g=0.0; 
	for (j=0; j<dmkoi; j++) { s=s+kektpi[j]*pow(t, g); g=g+hf; } ektpi[k]=s; } for (k=0; k<cem; k++) cout << "tem = " << etei[k] << "\tktp = " << ektpi[k] << "\t"; cout << endl;
	muv=opredTempHolGor(ektpi, etei, cemi, ys0, k, muv, f, cemi, etei, dmkoi, tki, snmi); //cem - ����� ������� efte
	k=0; j=1; mu=vydelPol(k, cemi, muv, mu, f, j, snmi, vybves, vybitom);
	k=0; tholi=mu[k]; k++; tgori=mu[k]; k++; qobi=mu[k]; 
	k++; ektpi=mu[k]; k++; etei=mu[k]; k++; po=mu[k];
	if (muv) delete[]muv; if (mu) delete[]mu; 
	k=0; nf=po[k]; t=e; k=0; while (t<nf) { t=t+hf; k++; } cemi=k; 
	if (kektpi) delete[]kektpi; 
	//-----
	stchsritom=new double[cemi]; if (!stchsritom) { cout << snmi << endl; k=getchar(); exit(1); }
	for (k=0; k<cemi; k++) { g=epsisred(etei[k], tkusci, kusci, dmkoosci, dkoscit, dkoscim, dkoscil, vybves, vybitom, dko); 
	stchsritom[k]=g; } for (k=0; k<cemi; k++) cout << "tem = " << etei[k] << "\tst_ch = " << stchsritom[k] << "\t"; cout << endl;
	kttki=opredKTPTverKarkNach(etei, ektpi, poritom, wsio, walo, wmgo, vfv, vsv, vpkf, isrp, kusci, tkusci, dmkoosci, stchsritom, 
		cemi, fl, ktpvo, vte, Prvo, dmkv, snmi, vybves, vrsh, vystsha, vybitom); for (k=0; k<cemi; k++) cout << "tem = " << etei[k] << "\tktp_tk_i = " << kttki[k] << "\t"; cout << endl;
	int c=8, q=1; po=new double[q];
	mu=new double*[c]; if ((!mu) || (!po)) { cout << snmi << endl; k=getchar(); exit(1); }
	k=0; po[k]=nf; 
	k=0; mu[k]=etei; 
	k++; mu[k]=ektpi; 
	k++; mu[k]=tgori; 
	k++; mu[k]=tholi; 
	k++; mu[k]=qobi; 
	k++; mu[k]=kttki;
	k++; mu[k]=stchsritom;
	k++; mu[k]=po; 
	return mu;
}
double *poisMasKoefItom(int no, double *kti, int n, char *snmi)
{
	int f=n, k=0, w=0, v=1; 
	double te0=273.15, t1=2e2, t2=38e1, kk=1e-2, te200=t1+te0, te380=t2+te0, *ktpit=NULL;
	if (!no) {
		double *kitom440 = new double[f]; ktpit = new double[f];
		if ((!kitom440) || (!ktpit)) { cout << snmi << endl; getchar(); exit(1); }
		for (k=0; k<f; k++) { ktpit[k]=0.0; kitom440[k]=0.0; }
		k=0; ktpit[k] = 9e0*kk; k++; ktpit[k] = 12e0*kk;
		kitom440[v] = (ktpit[v] - ktpit[w]) / (te380 - te200); 
		kitom440[w] = ktpit[w] - kitom440[v] * te200;
		for (k=0; k<f; k++) kti[k] = kitom440[k]; if (kitom440) delete[]kitom440;
	}
	else if (no == 1) {
		double *kitom620 = new double[f]; ktpit = new double[f];
		if ((!kitom620) || (!ktpit)) { cout << snmi << endl; getchar(); exit(1); } 
		for (k=0; k<f; k++) { ktpit[k]=0.0; kitom620[k]=0.0; }
		ktpit[w] = 12.0*1e-2; ktpit[v] = 139.0*1e-3; //�� �����������
		//ktpit[w] = 18.0*kk; ktpit[v] = 19.0*kk; //������ 2017 ����
		kitom620[v] = (ktpit[v] - ktpit[w]) / (te380 - te200); 
		kitom620[w] = ktpit[v] - kitom620[v] * te380;
		for (k=0; k<f; k++) kti[k] = kitom620[k]; if (kitom620) delete[]kitom620;
	}
	else if (no == 2) {
		double *kitom860 = new double[f]; ktpit = new double[f];
		if ((!kitom860) || (!ktpit)) { cout << snmi << endl; getchar(); exit(1); } 
		for (k=0; k<f; k++) { ktpit[k]=0.0; kitom860[k]=0.0; }
		ktpit[w] = 18.3*kk; ktpit[v] = 19.4*kk; //�� �����������
		//ktpit[w] = 26.0*kk; ktpit[v] = 37.0*kk; //������ 2017 ����
		kitom860[v] = (ktpit[v] - ktpit[w]) / (te380 - te200); 
		kitom860[w] = ktpit[v] - kitom860[v] * te380;
		for (k=0; k<f; k++) kti[k] = kitom860[k]; if (kitom860) delete[]kitom860;
	}
	else if (no == 3) {
		double *kitom1000 = new double[f]; ktpit = new double[f];
		if ((!kitom1000) || (!ktpit)) { cout << snmi << endl; getchar(); exit(1); } 
		for (k=0; k<f; k++) { ktpit[k]=0.0; kitom1000[k]=0.0; }
		ktpit[w] = 23.0*kk; ktpit[v] = 25.0*kk; //�� �����������
		//ktpit[w] = 42.0*kk; ktpit[v] = 52.0*kk; //������ 2017 ����
		kitom1000[v] = (ktpit[v] - ktpit[w]) / (te380 - te200); 
		kitom1000[w] = ktpit[v] - kitom1000[v] * te380;
		for (k=0; k<f; k++) kti[k] = kitom1000[k]; if (kitom1000) delete[]kitom1000;
	}
	else { cout << "Net takoy marki ITOM!" << endl; k = getchar(); exit(1); }
	if (ktpit) delete[]ktpit;
	return kti;
}
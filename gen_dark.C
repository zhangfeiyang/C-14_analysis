#include "rootheader.h"
double X[17739],Y[17739],Z[17739];
void get_position(float &x,float& y,float& z,int id){

    x = X[id];
    y = Y[id];
    z = Z[id];
};

int main()
{
    ifstream fin("Map2");
    double tmp;
    for(int i=0;i<17739;i++){
        fin>>tmp>>X[i]>>Y[i]>>Z[i];
    }


    double tau = 1e9/(17739*3e4);
 

    float GlobalPosX[10000];
    float GlobalPosY[10000];
    float GlobalPosZ[10000];
    float GlobalPosT[10000];

    int nWindows = 0;
    int nhits = 0;
	double hitTime = 0;
	float deltaT;
	float Rsquare;
	float RTsquare;

	TFile *f = new TFile("only_dark_hits.root","recreate");
	TTree *t = new TTree("t","");
    t->Branch("deltaT",&deltaT,"deltaT/F");
    t->Branch("Rsquare",&Rsquare,"Rsquare/F");
    t->Branch("RTsquare",&RTsquare,"RTsquare/F");
    t->Branch("nhits",&nhits,"nhits/I");


	TH1F *h = new TH1F("h","",200,0,200);
    for(int i=0;i<1e8;i++){
	if(hitTime > (nWindows+1)*200.0){
		float Xbar = TMath::Mean(nhits,GlobalPosX);
                float Ybar = TMath::Mean(nhits,GlobalPosY);
                float Zbar = TMath::Mean(nhits,GlobalPosZ);
                float Tbar = TMath::Mean(nhits,GlobalPosT) - nWindows*200 - 100;
                Rsquare = (Xbar*Xbar + Ybar*Ybar + Zbar*Zbar);
                RTsquare = (Xbar*Xbar + Ybar*Ybar + Zbar*Zbar + Tbar*Tbar);
		deltaT = 200.0/nhits;
		t->Fill();
		nWindows++;
		nhits = 0;
	}
        hitTime += gRandom->Exp(tau);
	GlobalPosT[nhits] = hitTime;
	h->Fill(hitTime);
        int pmtID = int(gRandom->Uniform(0,17739));
        get_position(GlobalPosX[nhits],GlobalPosY[nhits],GlobalPosZ[nhits],pmtID);
	nhits ++;
    }
	h->Write();
	t->Write();
	f->Close();

	
    return 0;
}

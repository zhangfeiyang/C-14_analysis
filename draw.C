void draw(int threshold=20,int rate=40){

	TChain *t = new TChain("t");
	t->Add(Form("../rootfile/final_%ikHz_%inhits_*.root",rate,threshold));
	t->Draw("RTsquare**0.25:nhits>>h1(100,0,400,100,0,150)","windowType==1");
	TH2F *h1 = (TH2F*)gDirectory->Get("h1");
	
	TFile *f = new TFile("../rootfile/only_dark_hits.root","read");
	TTree *t0 = (TTree*)f->Get("t");
	t0->Draw("RTsquare**0.25:nhits>>h0(100,0,400,100,0,150)");
	TH2F *h0 = (TH2F*)gDirectory->Get("h0");
	
	//h1->SetMarkerStyle(7);	
	h0->SetMarkerStyle(7);	
	h1->SetMarkerColor(kRed);

        h0->Draw("");
	h1->Draw("same");

	TF1 *fun1 = new TF1("fun1","9.075*sqrt(7.8 - ((x-106.4)/10.32)**2) +40.72",106.4,106.4+sqrt(7.8)*10.32*1.001);
	fun1->SetLineColor(kGreen);
	fun1->Draw("same");
	TF1 *fun2 = new TF1("fun2","-9.075*sqrt(7.8 - ((x-106.4)/10.32)**2) +40.72",106.4,106.4+sqrt(7.8)*10.32*1.001);
	fun2->SetLineColor(kGreen);
	fun2->Draw("same");
	int Entries = t->GetEntries("windowType==1");
	int cutEntries = t->GetEntries("((nhits-106.4)/10.32)**2 + ((RTsquare**0.25-40.72)/9.075)**2>7.8 && nhits>106.4 && windowType==1");
	cout <<"the efficiency is "<< cutEntries*1.0/Entries*100 <<"%\n";
}

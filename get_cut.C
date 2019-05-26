{
	TFile *f = new TFile("../rootfile/only_dark_hits.root","read");
        TTree *t = (TTree*)f->Get("t");
	
	int entries = t->GetEntries();
	int N = 100;
	for(int i=0;i<N;i++){
		float cut = 7.6 + 0.4/N*i;
		int aftercut = t->GetEntries(Form("((nhits-106.4)/10.32)**2 + ((RTsquare**0.25-40.72)/9.075)**2>%f && nhits>106.4",cut));
		cout << cut << "\t" << aftercut << "\t" << entries<< "\t" << aftercut*1.0/entries << "\n"; 
		
	}
}

#include <bits/stdc++.h>
using namespace std;
float mvalue[1010][2] = {0,}, wvalue[1010][2] = {0,};
double s[1010][1010] = {0,};
double B[1010][1010][2] = {0,};
double H[1010][1010][2] = {0,};
double R[1010][1010][2] = {0,};
double A[1010][1010][2] = {0,};
int main() {
	int n = 0;
	FILE *fp = fopen("test.txt", "r");
    fscanf(fp, "%d", &n);
	for(int i = 0; i<n; i++) {
		fscanf(fp, "%f %f", &mvalue[i][0], &mvalue[i][1]);
	}
	for(int i = 0; i<n; i++) {
		fscanf(fp, "%f %f", &wvalue[i][0], &wvalue[i][1]);
	}
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			s[i][j] = -pow(pow(mvalue[i][0]-wvalue[j][0], 2)+pow(mvalue[i][1]-wvalue[j][1], 2), 0.5);
		}
	}
	printf("?????%f\n", s[3][4]);
	int iter = 500;
	double lambda = 0.5;
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			B[i][j][0] = B[i][j][1] = 500;
			H[i][j][0] = H[i][j][1] = 500;
			R[i][j][0] = R[i][j][1] = 500;
			A[i][j][0] = A[i][j][1] = 500;
		}
	}
	for(int r = 0; r<iter; r++) {
		for(int i = 0; i<n; i++) {
			for(int j = 0; j<n; j++) {
				B[i][j][0] = lambda*B[i][j][0]+(1-lambda)*A[i][j][0];
				B[i][j][1] = lambda*B[i][j][0]+(1-lambda)*min(s[i][j], A[i][j][1]);
			}
		}
		
		for(int i = 0; i<n; i++) {
			for(int j = 0; j<n; j++) {
				R[i][j][0] = lambda*R[i][j][0]+(1-lambda)*H[i][j][0];
				R[i][j][1] = lambda*R[i][j][0]+(1-lambda)*min(s[i][j], H[i][j][1]);
			}
		}
		
		for(int i = 0; i<n; i++) {
			double min = 0, min2 = 0, min3 = 0;
			int mint = 0, min2t = 0;
			vector<pair<double, int>> sortimsi = {{B[i][0][0], 0}, {B[i][1][0], 1}, {B[i][2][0], 2}};
			sort(sortimsi.begin(), sortimsi.end());
			min = sortimsi[0].first; min2 = sortimsi[1].first; min3 = sortimsi[2].first;
			mint = sortimsi[0].second; min2t = sortimsi[1].second;
			for(int t = 3; t<n; t++) {
				if(min>B[i][t][0]) {
					min3 = min2;
					min2 = min;
					min = B[i][t][0];
					min2t = mint;
					mint = t;
				}
				else if(min2>B[i][t][0]) {
					min3 = min2;
					min2 = B[i][t][0];
					min2t = t;
				}
				else if(min3>B[i][t][0]){
					min3 = B[i][t][0];
				}
			}
			for(int j = 0; j<n; j++) {
				if(j==mint) H[i][j][1] = min2;
				else H[i][j][1] = min;
			}
			for(int j = 0; j<n; j++) {
				double max = -1e100;
				for(int t = 0; t<n; t++) {
					if(t==j) continue;
					double p = 0;
					if(t==mint) {
						if(j==min2t) {
							p = min3;
						}
						else {
							p = min2;
						}
					}
					else if(t==min2t) {
						if(j==mint) {
							p = min3;
						}
						else {
							p = min;
						}
					}
					else {
						if(j==mint) {
							p = min2;
						}
						else {
							p = min;
						}
					}
					p = B[i][t][1]>p?p:B[i][t][1];
					if(max<p) max = p;					
				}
				H[i][j][0] = max;
			}
		}
		
		for(int j = 0; j<n; j++) {
			double min = 0, min2 = 0, min3 = 0;
			int mint = 0, min2t = 0;
			vector<pair<double, int>> sortimsi = {{R[0][j][0], 0}, {R[1][j][0], 1}, {R[2][j][0], 2}};
			sort(sortimsi.begin(), sortimsi.end());
			min = sortimsi[0].first; min2 = sortimsi[1].first; min3 = sortimsi[2].first;
			mint = sortimsi[0].second; min2t = sortimsi[1].second;
			for(int t = 3; t<n; t++) {
				if(min>R[t][j][0]) {
					min3 = min2;
					min2 = min;
					min = R[t][j][0];
					min2t = mint;
					mint = t;
				}
				else if(min2>R[t][j][0]) {
					min3 = min2;
					min2 = R[t][j][0];
					min2t = t;
				}
				else if(min3>R[t][j][0]){
					min3 = R[t][j][0];
				}
			}
			for(int i = 0; i<n; i++) {
				if(i==mint) A[i][j][1] = min2;
				else A[i][j][1] = min;
			}
			for(int i = 0; i<n; i++) {
				double max = -1e100;
				for(int t = 0; t<n; t++) {
					if(t==i) continue;
					double p = 0;
					if(t==mint) {
						if(i==min2t) {
							p = min3;
						}
						else {
							p = min2;
						}
					}
					else if(t==min2t) {
						if(i==mint) {
							p = min3;
						}
						else {
							p = min;
						}
					}
					else {
						if(i==mint) {
							p = min2;
						}
						else {
							p = min;
						}
					}
					p = R[t][j][1]>p?p:R[t][j][1];
					if(max<p) max = p;					
				}
				A[i][j][0] = max;
			}
		}
	}
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			printf("%f %f %f %f\n", R[i][j][0], R[i][j][1], A[i][j][0], A[i][j][1]);
		}
	}
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<n; j++) {
			double min1 = R[i][j][1]>A[i][j][1]?A[i][j][1]:R[i][j][1];
			double min2 = R[i][j][0]>A[i][j][0]?A[i][j][0]:R[i][j][0];
			
			if(min1-min2>0) {
				printf("1 ");
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}
}

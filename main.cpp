#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define n  4// number of vertices
using namespace std;
class GRAPH
{
	private:
	int num_cities; // number of cities
	int distances[n][n]; // distances matrix
	public:
		
	GRAPH(int mat[n][n]) { // constructor from an input file
		this->num_cities = n;
		int i,j;
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				this->distances[i][j] = mat[i][j];
				this->distances[j][i] = mat[j][i];
			}
			
		}
	}
	
	int get_num_cities() const{
		return this->num_cities;
	}	
	int get_dist(int i, int j){
		return this->distances[i][j];
	}
	
	bool areNeigbours(int i, int j){
		if(distances[i][j]==0)
			return false;
		return true;
	}
	//seters
	void setNumcities(int k){
		this->num_cities = k;
	}
	void IncrementNumcities(){
		this->num_cities+=1;
	}
	void DecrementNumcities(){
		this->num_cities-=1;
	}
	void setDistaces(int i, int j, int weight){
		this->distances[i][j] = weight;
	}
	//obtenir la sommet numeri i
	/*int getVertexAT(int i){
		return this.distances[]
	}*/
	void initialiseDist(){
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				this->distances[i][j] = -1;
			}
			
		}
	}
	int *getVertex(int i){
		int j = 0;
		int t[n];
		for(i=0;i<n;i++){
			t[i] = this->distances[i][j];	
		}
		return t;
		
	}
	int currentNumcities(){
		int i,j;
		int num = 1;//to get the real number of cities
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				if(distances[i][j] != -1){
					num++;
				}
			}	
		}
		return num;
	}
	int getIncost(int v){
		int sum;
		int i;
		for(i=0;i<n;i++){
			sum = this->distances[v][i];
		}
		return sum;
	}
};


struct solution{
	GRAPH *A;
	GRAPH *B;// on doit ajouter je pense la fonction getNeghbour to class GRAPH
};

int somme(struct solution s){
	int j=0,a=0,b=0;
	for(j=0;j<n;j++){
		a += s.A->getIncost(j);
		b +=s.B->getIncost(j);
	}
	return a+b;
}

solution Tabou_search(GRAPH *g){
	struct solution s0;
	s0.A->initialiseDist();
	s0.B->initialiseDist();
	//generating the first solution randomly
	int i,j;
	int b;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			//srand ( time(NULL) );
			b = rand()%RAND_MAX;
			if((b%10)>5){
				s0.A->setDistaces(i,j,g->get_dist(i,j));	
			}
			else{
				s0.B->setDistaces(i,j,g->get_dist(i,j));		
			}
		}
	}
	//to balance the number of cities
	while((s0.B->currentNumcities())> (s0.A->currentNumcities())){
		s0.A->IncrementNumcities();
		s0.B->DecrementNumcities();
	}
	while((s0.A->currentNumcities())> (s0.B->currentNumcities())){
		s0.B->IncrementNumcities();
		s0.A->DecrementNumcities();
	}
	
	//tabou search
	int iterations = 0, MaxIterations = 20;
	int NoImprove = 0, MaxNoImprove = 10;
	int tabou_list[n];
	int m;
	for(m=0;m<n;m++){
		tabou_list[m] = 0;	
	}
	int f_best = somme(s0);
	struct solution current;
	int v=0;//vertex number 0 to be moved
	while(iterations<MaxIterations){
		
		int vA[n],vB[n];
		int column = 0;
		for(column=0;column<n;column++){
			vA[column] = s0.A->get_dist(v,column);
			vB[column] = s0.B->get_dist(v,column);
		}
		int k =0;
		for(k=0;k<n;k++){
			if(tabou_list[v]==0){
				s0.B->setDistaces(v,k,vA[i]);
				s0.A->setDistaces(v,k,vB[i]);
			}	
		}
		tabou_list[v]=1;
		v++;
		current.A = s0.A;
		current.B = s0.B;
		if(f_best>somme(current) and (s0.A->get_num_cities())==(s0.B->get_num_cities())){
			f_best = somme(current);
			s0 = current;
		}
		else{
			NoImprove+=1;
		}
		if(NoImprove>MaxNoImprove){
			NoImprove = 0;
			tabou_list[v]  = 0;
		}
		iterations++;
		
	}
	return s0;
	
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int i,j,poids;
	
	int matrice[n][n];
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			cout<<"entrez l'arete ("<< i <<","<< j <<"): ";
			cout<<endl;
			cin>>poids;
			cout<<endl;
			matrice[i][j]=poids;
			matrice[j][i] = poids;
		}	
	}
	
	GRAPH *graph = new GRAPH(matrice);
	cout<<endl;
	cout<<graph->get_num_cities();
	cout<<endl;
	
	//cout<<graph->areNeigbours(0,1);
	
	/*struct solution s;
	s.A = new GRAPH(matrice);
	cout<<s.A->get_num_cities();
	cout<<s.A->get_num_cities();*/
	
	struct solution s = Tabou_search(graph);
	cout<<somme(s);
	
	/*s.B = new GRAPH(matrice);
	cout<<endl;
	cout<<somme(s);*/
}

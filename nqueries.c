#include "./headers/avl.h"
#include <stdio.h>
#include <string.h>


long all_articles( Avl a ){
	long tot=0;
	if (a!=NULL){
		void* artigo;
		Valor valor;
		valor = getId(a);
		artigo = getAvlEstrutura( a , valor );
		tot = getN(artigo) + all_articles(getNodoEsq(a)) + all_articles(getNOdoDir(a)); 
	}
	return tot;
}

long unique_articles( Avl a){

	Valor arts = totalElems(a);
	return arts;
}

long all_revisions( Avl a ) {
	Valor revs = 0;
	if(a!= NULL){
		void* artigo;
		Valor valor = getId(a);
		artigo = getAvlEstrutura(a, valor);
		char** timeS[];
		int i = getN(artigo);
		getTimeStamp(artigo, timeS[]);
 		revs = Nrevision(timeS[], i) + all_revisions(getNOdoDir(a)) + all_revisions(getNodoEsq(a));
 	}
 	return revs;
 }

int Nrevision(char* t[], int i){
	int n = i;
	for (i;i>0;i--)
		for(int j = i; j > 0 ; j-- )
		if(strcmp(t[i], t[j-1]==0)) {n--; break;}

return n;
}
	
/*char* contributor_name(long id, Avl a){
	char* nome = NULL;
	if(a!= NULL ){
		void* artigo;
		Valor valor = getId(a);
		artigo = getAvlEstrutura(a,valor);
		long c[100];
		getAutId(artigo, c[]);
		int j = getN(artigo);
		int i = indice_autor(c[], id,j);
		if (i!=-1){
			char* aut[100];
			getAutores(artigo, aut[]);
			return aut[i];
		}

	return  nome;

} 


int indice_autor(long c[], long id, int n){
	for(int i=0; i < n; i++){
	if(id==c[i]) return i;
	}
}

*/ 

char* article_title(long articleId, Avl a){
	int i = 1;
	while(i && a!=NULL){
		if(articleId == getId(a)){
			void* artigo;
			Valor valor;
			artigo = getAvlEstrutura(a, valor);
			return getTitulo(a);
			i = 0;
		}
		else {article_title(getNodoEsq(a)); article_title(getNOdoDir(a));}
	}
	return NULL;
}

long* top_10_contributors(Avl a ){
	long** top[100][100];
	if(a!=NULL){
		void* artigo;
		Valor valor;
		artigo = getAvlEstrutura(a, valor);
		getTimeStamp(artigo, t[]);
		getAutId(artigo, a[]);




	}

}



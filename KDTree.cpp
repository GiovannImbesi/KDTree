#include<bits/stdc++.h> 
using namespace std; 
//In questa implementazione prenderemo ad esempio un albero 2-D
//L'albero è implementato tramite una lista di nodi attraverso una semplice struct Node
//La costante dimensione può essere modificata al fine di comprendere degli spazi a diverse dimensioni
const int dimensione = 2; 
struct Node 
{ 
	double coordinates[dimensione];  //Ogni punto è dotato di un array che definisce le sue coordinate
	Node *left, *right;  //Ogni Nodo è collegato al suo sottoalbero destro e sinistro tramite due puntatori
}; 

struct Node* newNode(double arr[]) 
{ 
	struct Node* temp = new Node; //Creo un nuovo nodo tramite allocazione dinamica

	for (int i=0; i<dimensione; i++) //Inizializzo il nodo con le sue coordinate
		temp->coordinates[i] = arr[i]; 

	temp->left = temp->right = NULL; //Inizialmente i suoi puntatori puntano a NULL
	return temp; 
} 
bool arePointsSame(double point1[], double point2[]) //Questo metodo permette di confrontare se due punti sono uguali
{ 
    
    for (int i = 0; i < dimensione; ++i) 
        if (point1[i] != point2[i]) //L'if itera il confronto su tutte le coordinate
            return false; 
  
    return true; 
} 

Node *KD_RecInsert(Node* root, double point[], unsigned depth) 
{ 
	
	if (root == NULL) //Se l'albero è vuoto allora il nuovo nodo aggiunto è la radice
		return newNode(point); 

	
	unsigned cd = depth % dimensione; //Calcolo l'asse corrente

	
	if (point[cd] < (root->coordinates[cd])) //Confronto la coordinata relativa all'asse calcolato
		root->left=	KD_RecInsert(root->left, point, depth + 1); //Se minore mi sposto nel sottoalbero sinistro
	else
		root->right =KD_RecInsert(root->right, point, depth + 1); //Altrimenti mi sposto nel sottoalbero destro

	return root; 
} 


Node* insert(Node *root, double point[]) 
{ 
	return KD_RecInsert(root, point, 0); 
} 

bool KD_Search(Node* root, double point[], unsigned depth) 
{ 
    //Se l'albero è vuoto allora il metodo restituisce false
    if (root == NULL) 
        return false; 
	//Confrontiamo la radice con il punto cercato
    if (arePointsSame(root->coordinates, point)) 
        return true; 
    //Se la radice non è il punto cercato all'ora dobbiamo spostarci nel sottoalbero destro o sinistro
	//Seguiamo la stessa procedura descritta sopra
     
    unsigned cd = depth % dimensione; 
  
    
    if (point[cd] < root->coordinates[cd]) 
        return KD_Search(root->left, point, depth + 1); 
    else
       return KD_Search(root->right, point, depth + 1); 
} 
  
 
bool search(Node* root, double point[]) 
{ 
    
    return KD_Search(root, point, 0); 
} 

Node *minNode(Node *x, Node *y, Node *z, int d) //Questa procedura restituisce il minimo fra tre nodi 
{ 
	Node *res = x; 
	if (y != NULL && y->coordinates[d] < res->coordinates[d]) //Il confronto avviene sulla coordinata relativa all'asse 'd' in input
	res = y; 
	if (z != NULL && z->coordinates[d] < res->coordinates[d]) 
	res = z; 
	return res; 
} 


Node *findMinRec(Node* root, int d, unsigned depth) //Questo metodo permette di trovare il Nodo minimo
{ 
	//Caso base
	if (root == NULL) 
		return NULL; 

	 
	unsigned cd = depth % dimensione; 

	//Se l'asse del livello corrente è uguale a quello dato, il minimo richiesto si trova nel sottoalbero sinistro se esiste
	if (cd == d) 
	{ 
		if (root->left == NULL) 
			return root; 
		return findMinRec(root->left, d, depth+1); 
	} 
//Quando la dimensione del livello corrente è diversa
//il minimo può essere nella sottostruttura sinistra o destra oppure anche il nodo corrente può essere minimo 
//Quindi richiamiamo la procedura su entrambi e ritorniamo il minimo fra il risultato e la radice.
	return minNode(root, 
			findMinRec(root->left, d, depth+1), 
			findMinRec(root->right, d, depth+1), d); 
} 


Node *FindMin(Node* root, int d) 
{ 
	return findMinRec(root, d, 0); 
} 

 
void copyPoint(double p1[], double p2[]) //La procedura permette di copiare un nodo.
{ 
	for (int i=0; i<dimensione; i++) 
		p1[i] = p2[i]; 
} 

Node *DeleteKD(Node *root, double point[], int depth) 
{ 
    //Caso base
	if (root == NULL) 
		return NULL; 

	//Calcolo l'asse corrente
	int cd = depth % dimensione; 

	//Se il nodo corrente contiene il punto da eliminare
	if (arePointsSame(root->coordinates, point)) 
	{  
	    //Se il sottoalbero destro non è vuoto
		if (root->right != NULL) 
		{ 
			// Trovo il nodo minimo 
			Node *min = FindMin(root->right, cd); 
			//Copio il minimo con la radice
			copyPoint(root->coordinates, min->coordinates); 
			//Cancello ricorsivamente il minimo
			root->right = DeleteKD(root->right, min->coordinates, depth+1); 
		} 
		else if (root->left != NULL) //Applico la stessa procedura 
		{ 
			Node *min = FindMin(root->left, cd); 
			copyPoint(root->coordinates, min->coordinates); 
			root->right = DeleteKD(root->left, min->coordinates, depth+1); 
		} 
		//Se il nodo da eliminare è una foglia,esso viene semplicemente eliminato
		else 
		{ 
			delete root; 
			return NULL; 
		} 
		return root; 
	} 

	//Se il nodo corrente non contiene il punto
	if (point[cd] < root->coordinates[cd]) 
		root->left = DeleteKD(root->left, point, depth+1); 
	else
		root->right = DeleteKD(root->right, point, depth+1); 
	return root; 
} 

Node* deleteNode(Node *root, double point[]) 
{ 
     return DeleteKD(root, point, 0); 	 
} 

void InorderKD(Node* root) //Procedura ricorsiva di visita dell'albero
{
	if(root)
	{
		InorderKD(root->left); //Visito prima il sottoalbero sinistro
		cout<<"(";
		for(int i=0;i<dimensione;i++) //Stampo la radice 
		{
			cout<<root->coordinates[i];
			if(i<(dimensione-1)) cout<<",";
		}
		cout<<") ";
		InorderKD(root->right); //Visito il sottoalbero destra
	}
}
void preorderKD(Node* root)
{
	if(root)
	{
		preorderKD(root->left); //Visito il sottoalbero sinistro
		preorderKD(root->right); //Visito il sottoalbero destro
		cout<<"(";
		for(int i=0;i<dimensione;i++) //Stampo la radice
		{
			cout<<root->coordinates[i];
			if(i<(dimensione-1)) cout<<",";
		}
		cout<<"),";
		
	}
}
void postorderKD(Node* root)
{
	if(root)
	{
		cout<<"(";
		for(int i=0;i<dimensione;i++) //Stampo la radice
		{
			cout<<root->coordinates[i];
			if(i<(dimensione-1)) cout<<",";
		}
		cout<<"),";
		postorderKD(root->left); //Visito il sottoalbero sinistro
		
		postorderKD(root->right); //Visito il sottoalbero destro
	}
}

double distSquared(Node* punto1, Node* punto2)
{
	//Confronta le distanze. Si usa farlo senza calcolare le radici.
	long total=0;
	for(int i=0; i< dimensione;i++)
	{
		int diff= abs(punto1->coordinates[i] - punto2->coordinates[i]);
		total += pow(diff,2);
	}
	return total;
	
}
Node* closest(Node* n0, Node* n1 , Node* target)
{ 
    //Determina chi tra n0 e n1 è il più vicino al target
	 
    //Casi base
	if(n0==NULL) return n1;
	if(n1==NULL) return n0;
	//Caso generale
	long d1=distSquared(n0,target);
	long d2=distSquared(n1,target);
	if(d1 < d2)
		return n0;
	else
		return n1;
}

Node* KD_RecNearestNeighbor(Node* root,Node* target, int depth)
{
	//caso base
	if(root==NULL)  
		return NULL;
	
	/*L'algoritmo controlla se potrebbero esserci punti sull'altro lato del piano di divisione
	che sono più vicini al punto di ricerca	rispetto al migliore corrente.A tale scopo manteniamo il puntatore "otherBranch"
	*/
	
	Node* nextBranch=NULL;
	Node* otherBranch=NULL;
	unsigned cd = depth % dimensione;
	if( target->coordinates[cd] < root->coordinates[cd])
	{
		nextBranch= root->left;
		otherBranch=root->right;
	}
	else
	{
		nextBranch= root->right;
		otherBranch=root->left;
	}
	//ricerchiamo ricorsivamente il migliore
	
	Node* temp=KD_RecNearestNeighbor(nextBranch, target,depth+1);
	Node* best = closest(temp,root,target);
	//Calcoliamo la distanza dal nodo target
	long radiusSquared=distSquared(target, best);
	
	//Controlliamo l'altro piano di divisione
	//dist è una sorta di linea immaginaria che ci permette di passare nell'altro piano
	long dist= target->coordinates[cd] - root->coordinates[cd];
	
	//Se la distanza dal nodo 'best' è maggiore della distanza fra il target ed il piano di divisione della radice del sottoalbero
	if(radiusSquared >= dist*dist)
	{
		//Cerchiamo un possibile nodo 'best' nell'altro sottoalbero
		temp=KD_RecNearestNeighbor(otherBranch,target,depth+1);
		best=closest(temp,best,target);
	}
	return best;
	
}

Node* KD_NN(Node* root,Node* target)
{
	return KD_RecNearestNeighbor(root,target,0);
}
void stampaPunto(Node* dastampare)
{
	for(int i=0;i<dimensione;i+=2)
		cout<<"("<<dastampare->coordinates[i]<<","<<dastampare->coordinates[i+1]<<")";
}
int main() 
{ 
    cout<<endl;
    cout<<"**Alberi k-dimensionali**"<<endl;
	struct Node *root = NULL; 
	double points[][dimensione] = {{5,4}, {2,6}, {13,3}, 
					{8,7}, {3,1}, {10,2}}; 
	int n = sizeof(points)/sizeof(points[0]); 
	for (int i=0; i<n; i++) 
		root = insert(root, points[i]);
    cout<<"Una visita inorder è ";
	InorderKD(root);
	
	cout<<endl;		
    double point1[] = {3, 1}; 
    (search(root, point1))? cout << "Il punto 3,1 è presente nell'albero\n": cout << "Il punto 3,1 non è presente nell'albero\n"; 
    double point2[] = {30,40}; 
    (search(root, point2))? cout << "Il punto 30,40 è presente nell'albero\n": cout << "Il punto 30,40 non è presente nell'albero\n"; 
    Node *minimo=FindMin(root,0);
	cout<<"Il nodo minimo ha coordinate: ";
	stampaPunto(minimo);
	cout<<endl;
	root = deleteNode(root, points[0]); 
	cout << "La radice dopo la cancellazione di  (5,4) è "; 
	stampaPunto(root);
	cout<<endl;
	
	double pointx[]={9,4};
	struct Node* target=newNode(pointx);
	for(int i=0;i<dimensione;i++)
		target->coordinates[i]=pointx[i];
	Node* NN= KD_NN(root,target);
	cout<<"Il nodo più vicino al punto ";
	stampaPunto(target);
	cout<<" ha coordinate ";
	stampaPunto(NN);
	cout<<endl;
	return 0; 
} 

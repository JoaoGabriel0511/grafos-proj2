//- Alunos: 1.Khalil Carsten do Nascimento - 15/0134495
//          2.João Gabriel - 15/0131992

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

#define iv pair<int, vector<int>>

//variaveis globais
fstream js_fl;
// map  que ira mapear a matricula de cada vertice com o seu indice
map<string, int> m;
vector<int> L;
vector<bool> visitado(35, 0);

// Classe que define a estrutura do Grafo
class Graph{
    private:
        vector<iv> adj;

    public:
        Graph();
        Graph(int size);
        int size();
        int size_adj(int node);
        void add_edge(int f_node, int s_node);
        void add_weight(int node, int weight);
        void print_graph();
        iv& operator[](int  index);
        int* caminho_crit(vector<int> L);
        void acha_crit(int * aux, int pos);
        int * acha_criti(int * aux, int pos, int * max, int  soma);
};

// Contrutor do grafo, -int size- relativo ao numero de alunos n grafo
Graph::Graph(int size){
    for(int i = 0; i < size; i++){
        iv a;
        adj.push_back(a);
    }
}

int Graph::size(){
    return adj.size();
}
// Funcao que define o operador "[]" para a classe grafo
// assim eh possivel acessar uma lista de adjacencia usando somente g[lista]
// Recebe como parametro o inteiro index que o indice da lista do vertice requisitado
// e retorna a lista de adjacentes desse vertice
iv& Graph::operator[](int index){
    if (index > adj.size() || index < 0)
        throw std::out_of_range("Index out of range");
    return adj[index];
}

void Graph::add_weight(int node, int weight){
    adj[node].first = weight;
}

// Funcao que cria as relacoes(arestas) entre os vertices.
// Tambem garante que nao existe vertices repetidos na lista
// de vizinhos e os mantem ordenados.
void Graph::add_edge(int f_node, int s_node){
    adj[f_node].second.push_back(s_node);
}

string find_value(int value){
    for(auto f : m){
        if(f.second == value){
            return f.first;
        }
    }
}

// Funcao de Debug que escreve o grafo no terminal
void Graph::print_graph(){
    for(int i = 0; i < adj.size(); i++){
        cout << find_value(i) << " " << "Peso: " << adj[i].first << endl;
        cout << "eh pre-requisito para : " << endl;
        for(int j = 0; j < adj[i].second.size(); j++){
            cout << "          |-->" << find_value(adj[i].second[j]) << endl;
        }
        cout << endl;
    }
    cout << adj[2].second[0]<<endl;
}
int *Graph::caminho_crit(vector<int> L){
	int *aux = (int*)malloc(35 * sizeof(int));
	for(int i = 0; i< 35;i++){
		aux[i] = 0;
	}
	int i = 0;
	for(auto v : L){
		for(int j = 0; j < adj[v].second.size();j++){
			if(adj[v].first > aux[adj[v].second[j]]){
				aux[adj[v].second[j]] = adj[v].first;
			}
		}
	}
	return aux;
}
void Graph::acha_crit(int * aux, int pos){
	for(int i = 0; i < 35;i++){
		for(int j = 0; j < adj[i].second.size(); ++j){
			if(adj[i].second[j] == pos){
				cout <<"["<< find_value(pos) <<"]"<< "<---"<< aux[pos] <<"---- ";
				acha_crit(aux, i);
			}
		}
	}
	return;
}
int * Graph::acha_criti(int * aux, int pos, int * max, int  soma){
	for(int j = 0; j < adj[pos].second.size(); j++){
		soma = soma + adj[pos].first;

	}
}

// Essa funcao retorna uma lista com todas as materias q n possuem pre-requisitos
vector<int> return_S(Graph g){
    set<int> s;
    vector<int> v;

    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j < g[i].second.size(); j++){
            s.insert(g[i].second[j]);
        }
    }

    for(int i = 0; i < g.size(); i++){
        if(s.find(i) == s.end()){
            v.push_back(i);
        }
    }

    return v;
}

// Essa funcao promove o dfs no grado gerando na lista L a ordenação topologica
void visita(int node, Graph g){

    if(visitado[node] == 0){
        visitado[node] = 1;
        for(int i = 0; i < g[node].second.size(); i++){
            visita(g[node].second[i], g);
        }
        L.push_back(node);
    }
}

// Funcao responsavel por exibir e controlar o menu
// Recebe como parâmetro g(ponteiro do Grafo em que serão realizadas as operações do menu)
int menu(Graph &g){
    int a;
    int* aux;
    vector<int> S;
    vector<int[2]> G;
    int max = 0;
    int pos;
    vector<int[2]> cam_c;
    while(a != 4){
        cout << "escolha uma opcao:"<< endl;
        cout << "1-->       mostrar o grafo"<< endl;
        cout << "2-->       mostrar o caminho critico"<< endl;
        cout << "3-->       mostrar a ordenacao topologica"<< endl;
        cout << "sair(qualquer outra tecla)"<< endl;
        cin >> a;
        system("clear");
        switch (a){
        	case(1):
        		g.print_graph();
                getchar();
                getchar();
        		break;
        	case(2):
        		S = return_S(g);

                for(auto v : S){
                    visita(v, g);
                }
                aux = g.caminho_crit(L);
    	        for(int i = 0; i < 35; i++){
    	            if(aux[i] >= max){
    	            	max = aux[i];
    	            	pos = i;
    	            }
    	        }
    	        g.acha_crit(aux, pos);
                getchar();
                getchar();
        		break;
        	case(3):

                S = return_S(g);

                for(auto v : S){
                    visita(v, g);
                }
                cout << endl;
                for(auto v : L){
                    cout << "[" << find_value(v) << "]-->";
                }
                cout << "end" << endl;

                getchar();
                getchar();
        		break;
        	default:
        		exit(1);
        }
    }
}

// Funcao responsavel por processar cada linha do arquivo de entrada
// materias_do_curso e criar o grafo a partir dele
// recebe como parâmetrosa line(ponteiro de string, é a linha do arquivo lida),
// g(ponteiro de Grafo, o grafo a ser formado) e
void process_line(string &line, Graph &g){
    string aux(6, 0);
    string aux2(6,0);
    int i, j = 0, ct = 0, cr, f;
    int node;
    int find = 0;

    for(i = 0; line[i] != '\0'; i++){
        if(line[i] == '#'){
            find = 1;
            ct++;
            aux[j+1] = '\0';
            j = 0;
        }
        if(find == 1){
        	if(ct == 1){
            	node = m[aux];
	        } else if(ct == 2){
	            cr = aux[0] - '0';
	        } else if(ct == 3){
	            f = aux[0] - '0';
	        } else{
	        	aux2[0] = aux[0];
	        	aux2[1] = aux[1];
	        	aux2[2] = aux[2];
	        	aux2[3] = aux[3];
	        	aux2[4] = aux[4];
	        	aux2[5] = aux[5];
	        	aux2[6] = aux2[6];
	        	g.add_edge(node, m[aux2]);
	        }
	        find = 0;
	        aux.clear();
	    }
	    if(line[i] != '#') {
        	aux[j] = line[i];
        	j++;
    	}
    }
    g.add_weight(node, cr*f);
}

// Essa funcao processa as materias e cria indices para elas facilitando a
// manipulacao nas estruturas de dados
void process_names(string &line, int indice){
    string aux(6, 0);
    int i;
    for(i = 0; line[i] != '#'; i++){
        aux[i] = line[i];
    }
    aux[i+1] = '\0';
    m[aux] = indice;
}

int main(){
    int a = 35;
    Graph g(a);
    int indice = 0;
    string line;
    ifstream fl1, fl2;

    fl1.open("materias_do_curso2.txt", fstream::in);

    for(string line; getline(fl1, line);){
        process_names(line, indice);
        indice++;
    }

    indice = 0;
    fl1.close();
    fl2.open("materias_do_curso2.txt", fstream::in);

    for(string line; getline(fl2, line);){
        process_line(line, g);
        indice++;
    }
    fl2.close();

    menu(g);

    return 0;
}

//- Alunos: 1.Khalil Carsten do Nascimento - 15/0134495
//          2.João Gabriel - 15/0131992

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;

#define iv pair<int, vector<int>>

//variaveis globais
fstream js_fl;
// map  que ira mapear a matricula de cada vertice com o seu indice
map<string, int> m;

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
};

// Contrutor do grafo, -int size- relativo ao numero de alunos n grafo
Graph::Graph(int size){
    for(int i = 0; i < size; i++){
        iv a;
        adj.push_back(a);
    }
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

// Funcao de Debug que escreve o grafo no terminal
void Graph::print_graph(){
    for(int i = 0; i < adj.size(); i++){
        cout << i << "{" << adj[i].first << "}" << endl;
        for(int j = 0; j < adj[i].second.size(); j++){
            cout << "  |-->" << adj[i].second[j] << "--" << endl;
        }
    }
}

// Funcao responsavel por exibir e controlar o menu
// Recebe como parâmetro g(ponteiro do Grafo em que serão realizadas as operações do menu)
int menu(Graph &g){
    int a;
    while(a != 3){
    }
}

// Funcao responsavel por processar cada linha do arquivo de entrada
// amigos_tag20172 e criar o grafo a partir dele
// recebe como parâmetrosa line(ponteiro de string, é a linha do arquivo lida), g(ponteiro de Grafo, o grafo a ser formado) e
// indice(inteiro usado para se manejar o grafo)
void process_line(string &line, Graph &g){
    string aux(6, 0);
    string aux2;
    int i, j = 0, ct = 0, cr, f;
    int node;

    for(i = 0; line[i] != '\0'; i++){
        if(line[i] == '#'){
            ct++;
            aux[j] = '\0';
            j = 0;
            i++;
        }
        if(ct == 1){
            node = m[aux];
        } else if(ct == 2){
            cr = aux[0] - '0';
        } else if(ct == 3){
            f = aux[0] - '0';
        } else if(ct > 3){
            g.add_edge(node, m[aux]);
        }
        aux[j] = line[i];
        j++;
    }
    cout << line << endl;
    g.add_weight(node, cr*f);
}

void process_names(string &line, int indice){
    string aux(7, 0);
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

    fl1.open("materias_do_curso.txt", fstream::in);

    for(string line; getline(fl1, line);){
        process_names(line, indice);
        indice++;
    }

    indice = 0;
    fl1.close();

    getchar();
    fl2.open("materias_do_curso.txt", fstream::in);

    for(string line; getline(fl2, line);){
        process_line(line, g);
        indice++;
    }
    fl2.close();

    // for(int a = 0;){
    //     cout << a.first << " ---- " << a.second << endl;
    // }

    g.print_graph();
    // menu(g);

    return 0;
}

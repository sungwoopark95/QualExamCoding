#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <list>
#include <queue> 


#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>
#include <fstream>
#include <math.h>

using namespace std;

class Graph {
    protected:
        int v_num; //vertex 개수
        int time_for_dfs; //DFS timestamp를 위한 변수
    public:
        vector<char> vertx; //vertex
        map<char, list<char>> adj; //adjacent list(edge set)
        map<char, char> predecessor; //DFS이후 predecessor dictionary
        map<char, char> color; // DFS 구현 짜다가,, 어쩔수 없이 들어갔음..
        map<char, int> distance; //BFS이후 distance dictionary(BFS시작점에 따라 달라짐)
        map<char, array<int,2>> time_df; //DFS이후 time_discover 및 time_finish
        vector<char> topologic_list={}; //topological list(only for DAG : Directed Acylic Graph)
        vector<char> parenthesis={}; //structure by DFS
        

        Graph(int num):v_num(num){}; //constructor with vertex size v_num
        int getVnum(){return v_num;}; //vertex개수 부르기
        void addVertex(const char&); //vertex 추가하기 
        void addAdj(const char& u, const char& v); //edge (u,v) 추가하기<방향성 유무에 따라 구현이 달라져야 함 / 일단 방향성 있다고 가정>
        void BFS(const char& s); //s에서 BFS 시작()
        void getPath(const char& s, const char& v); // s->v 최단 path 출력(BFS 이후 call)
        void DFS();
        Graph inverseGraph(); //inverseG 만들기
        void findoutSCC(); //parenthesis 이용해서 파악
    friend void DFS_VISIT(Graph&, char);//DFS_VISIT ftn을 recursive하게 쓰하려면 class 바깥의 함수로서 구현해야 할듯-

        
};


//vertex 추가하기 
//vector 제일 뒤쪽에 추가 / !똑같은 문자가 입력되지 않도록 추가제어 필요!
void Graph::addVertex(const char& u){
    if (vertx.size()<v_num) {
        vertx.push_back(u);
        adj[u]={};
        predecessor[u]={};
        distance[u]={};
        time_df[u]={0,0};
        color[u]='W';
    }
    else cout<<"too much vertex"<<endl;
    } 


//edge추가하기
//추가구현 필요사항 : 방향성 없는 Graph일 경우 양방향으로 edge추가/ 중복입력 방지 / u=v인 경우 미입력? (일단 시간이 없으므로..)
void Graph::addAdj(const char& u, const char& v){adj[u].push_back(v);} 



//s에서 출발하는 BFS
void Graph::BFS(const char& s){
    // map<char, char> color; //색상만 local variable ===> DFS구현 중에 Color도 멤버로 넣었음..
    //predecessor과 distance는 class member임(저장해두고 사용할 수 있도록 / 거리 및 path 출력용)//

    //초기설정//
    for (vector<char>::iterator it = vertx.begin() ; it != vertx.end(); ++it){
        color[*it]='W'; //White
        predecessor[*it]=0;
        distance[*it]=-1; //무한대로 표기하기보다는 음수로
    }


    color[s]='G'; //Grey
    predecessor[s]=0;
    distance[s]=0;

    std::queue<char> myqueue;
    myqueue.push(s);
    
    while (!myqueue.empty()){
        char u=myqueue.front();
        myqueue.pop();
        for (list<char>::iterator j=adj[u].begin(); j != adj[u].end(); ++j){
            char v=*j;
            if (color[v]=='W'){
                color[v]='G';
                distance[v]=distance[u]+1;
                predecessor[v]=u;
                myqueue.push(v);
            }    
        }
        color[u]='B'; //Black
    }
}


//최단경로출력 after BFS
void Graph::getPath(const char& s, const char& v){
    if (s==v) {cout<< s << endl;}
    else if (predecessor[v]==0) {cout << "no path from " <<s<<" to "<< v<<" exits"<< endl;}
    else {
        getPath(s, predecessor[v]);
        cout<< " - " << v   ;
    }
}


// DFS
void Graph::DFS(){

    //초기설정//
    for (vector<char>::iterator it = vertx.begin() ; it != vertx.end(); ++it){
        color[*it]='W'; //White
        predecessor[*it]=0;
        time_df[*it]={0,0};
    }
    time_for_dfs=0;
    parenthesis={}; //구조파악위해 parenthesis넣기
    //방문시작//
    for (auto it = vertx.cbegin(); it != vertx.cend(); ++it){
        char u=*it;
        if (color[u]=='W'){DFS_VISIT(*this, u);}
    }
} //DFS 끝

void DFS_VISIT(Graph& G, char u){
    G.time_for_dfs=G.time_for_dfs+1;
    G.time_df[u][0]=G.time_for_dfs;
    G.color[u]='G';
    G.parenthesis.emplace(G.parenthesis.end(),'(');//구조파악위해 parenthesis넣기
    G.parenthesis.emplace(G.parenthesis.end(),u);//구조파악위해 parenthesis넣기
    
 
    
    for (list<char>::iterator j=G.adj[u].begin(); j != G.adj[u].end(); ++j){
        char v=*j;
        if (G.color[v]=='W') {
            G.predecessor[v]=u;
            DFS_VISIT(G, v);
        }
    }

    G.color[u]='B';
    G.topologic_list.emplace(G.topologic_list.begin(),u);
    G.time_for_dfs=G.time_for_dfs+1;
    G.time_df[u][1]=G.time_for_dfs;
    G.parenthesis.emplace(G.parenthesis.end(),u);//구조파악위해 parenthesis넣기
    G.parenthesis.emplace(G.parenthesis.end(),')');//구조파악위해 parenthesis넣기

}


Graph Graph::inverseGraph(){
    Graph inverseG(v_num);//construct same size
    //vertex 입력//
    for (auto it = vertx.cbegin(); it != vertx.cend(); ++it) {
        inverseG.addVertex(*it); 
    }
    //edge 입력//
    for (map<char,list<char>>::iterator it=adj.begin(); it!=adj.end(); ++it){
        for (list<char>::iterator j=it->second.begin(); j != it->second.end(); ++j){
            inverseG.addAdj(*j, it->first); // inverse하게 입력
        }
    }

    return inverseG;
}


void Graph::findoutSCC(){
    DFS(); //DFS한번 돌리고,
    Graph invG=inverseGraph(); //inverse G만들고
    invG.vertx=topologic_list; //vertex순서를 DFS(G)의 역순으로 하고,
    invG.DFS(); //DFS(invG)
    
    //DFS(invG)의 parenthesis list 출력
    cout<<"-------------to find out SCC check parenthesis "<<endl;
    for (vector<char>::iterator it=invG.parenthesis.begin();it!=invG.parenthesis.end();++it){
        cout << *it << " ";
    }
    cout<<'\n';
    cout<<"-------------to find out SCC  parenthesis check done\n\n"<<endl;
    
}



int main(){

    // //for BFS : vertex setting
    // Graph G(8);
   
    // //for BFS : vertex setting
    // G.addVertex('r');    G.addVertex('s');    G.addVertex('t');    G.addVertex('u');
    // G.addVertex('v');    G.addVertex('w');    G.addVertex('x');    G.addVertex('y');

    // //for BFS : adj setting (일단 방향성 있는 식으로 구현하여, 방향없는 그래프를 구현하려면 양쪽을 각각 입력해야함)
    // G.addAdj('v','r'); G.addAdj('r','v');    G.addAdj('r','s'); G.addAdj('s','r');    G.addAdj('s','w'); G.addAdj('w','s');
    // G.addAdj('w','t'); G.addAdj('t','w');    G.addAdj('w','x'); G.addAdj('x','w');    G.addAdj('t','x'); G.addAdj('x','t');
    // G.addAdj('t','u'); G.addAdj('u','t');    G.addAdj('x','u'); G.addAdj('u','x');    G.addAdj('x','y'); G.addAdj('y','x');
    // G.addAdj('y','u'); G.addAdj('u','y');

   //for DFS : exam
    Graph G(9);

    //for DFS : vertex setting for SCC
    G.addVertex('a');    G.addVertex('b');    G.addVertex('c');    G.addVertex('d');
    G.addVertex('e');    G.addVertex('f');    G.addVertex('g');    G.addVertex('h');
    G.addVertex('i');

    //for DFS : adj setting for SCC
    G.addAdj('a','b');  G.addAdj('b','c');  G.addAdj('b','e');  G.addAdj('d','a');  G.addAdj('d','g');  G.addAdj('e','d');  G.addAdj('e','f');  G.addAdj('e','h');
    G.addAdj('f','c');  G.addAdj('f','h');  G.addAdj('f','i');  G.addAdj('g','e');  G.addAdj('g','h');  G.addAdj('h','f');  G.addAdj('i','h');



    // //for DFS : vertex setting for SCC
    // Graph G(8);

    // //for DFS : vertex setting for SCC
    // G.addVertex('a');    G.addVertex('b');    G.addVertex('c');    G.addVertex('d');
    // G.addVertex('e');    G.addVertex('f');    G.addVertex('g');    G.addVertex('h');

    // //for DFS : adj setting for SCC
    // G.addAdj('e','a');  G.addAdj('a','b');  G.addAdj('b','e');  G.addAdj('b','f');  G.addAdj('e','f');  G.addAdj('b','c');  G.addAdj('c','g');
    // G.addAdj('f','g');  G.addAdj('g','f');  G.addAdj('c','d');  G.addAdj('d','c');  G.addAdj('d','h');  G.addAdj('h','h');  G.addAdj('g','h');


    // //for DFS : vertex setting for topoligical sort(DAG / Directed Acyclic Graph)
    // Graph G(6);

    // //for DFS : vertex setting for topoligical sort(DAG / Directed Acyclic Graph)
    // G.addVertex('u');    G.addVertex('v');    G.addVertex('w');
    // G.addVertex('x');    G.addVertex('y');    G.addVertex('z');

    // //for DFS : adj setting for topoligical sort(DAG / Directed Acyclic Graph)
    // G.addAdj('u','v');  G.addAdj('v','y');  G.addAdj('y','x');  G.addAdj('u','x');  G.addAdj('w','y');  G.addAdj('w','z');




    //vertex 출력확인
    cout<<"-------------vertex check"<<endl;
    for (auto it = G.vertx.cbegin(); it != G.vertx.cend(); ++it){
        cout << *it <<endl;}
    cout<<"-------------vertex check done\n\n"<<endl;


    //adj (edge) 출력확인
    cout<<"-------------adj check"<<endl;
    for (map<char,list<char>>::iterator it=G.adj.begin(); it!=G.adj.end(); ++it){
        cout << it->first << " => ";

        for (list<char>::iterator j=it->second.begin(); j != it->second.end(); ++j){
            cout << *j ;
        }
        cout<<'\n';
    }
    cout<<"-------------adj check done\n\n"<<endl;
    


    //predecessor 출력확인
    cout<<"-------------predecessor check"<<endl;
    for (map<char,char>::iterator it=G.predecessor.begin(); it!=G.predecessor.end(); ++it){
        cout << it->first << " => " << it->second << endl;
    }
    cout<<"-------------predecessor check done\n\n"<<endl;

    //distance 출력확인
    cout<<"-------------distance check"<<endl;
    for (map<char,int>::iterator it=G.distance.begin(); it!=G.distance.end(); ++it){
        cout << it->first << " => " << it->second << endl;
    }
    cout<<"-------------distance check done\n\n"<<endl;


///////////////// BFS ////////////////////////////
//     //BFS 's'에서 시작
//     G.BFS('s');


//     cout<<"------------after BFS on 's'------------"<<endl;
//     //BFS 's' 후 predecessor 출력확인
//     cout<<"-------------predecessor check"<<endl;
//     for (map<char,char>::iterator it=G.predecessor.begin(); it!=G.predecessor.end(); ++it){
//         cout << it->first << " => " << it->second << endl;
//     }
//     cout<<"-------------predecessor check done\n\n"<<endl;

//     //BFS 's' 후 distance 출력확인
//     cout<<"-------------distance check"<<endl;
//     for (map<char,int>::iterator it=G.distance.begin(); it!=G.distance.end(); ++it){
//         cout << it->first << " => " << it->second << endl;
//     }
//     cout<<"-------------distance check done\n\n"<<endl;



// cout<<"-------path from s to u  after BFS--------"<<endl;
//   //BFS 's' 후 's'에서 'u' 가는 경로 찾기
//     G.getPath('s','u');
///////////////// BFS ////////////////////////////



///////////////// DFS ////////////////////////////
G.DFS();

cout<<"------------after DFS------------"<<endl;
//DFS 후 predecessor 출력확인
cout<<"-------------predecessor check"<<endl;
for (map<char,char>::iterator it=G.predecessor.begin(); it!=G.predecessor.end(); ++it){
    cout << it->first << " => " << it->second << endl;
}
cout<<"-------------predecessor check done\n\n"<<endl;

//DFS 후 timestamp 출력확인
cout<<"-------------timestamp check"<<endl;
for (map<char,array<int,2>>::iterator it=G.time_df.begin(); it!=G.time_df.end(); ++it){
    cout << it->first << " => ";

   for (auto j = it->second.begin(); j!= it->second.end(); ++j){
    cout << *j << "/ ";
    }
    cout<<'\n';
}
cout<<"-------------timestamp check done\n\n"<<endl;

//DFS 후 parenthesis list 출력
cout<<"------------- parenthesis check"<<endl;
for (vector<char>::iterator it=G.parenthesis.begin();it!=G.parenthesis.end();++it){
    cout << *it << " ";
}
   cout<<'\n';
cout<<"------------- parenthesis check done\n\n"<<endl;

//DFS 후 topological sort list 출력
cout<<"------------- topological sort list check <only valid for DAG> "<<endl;
for (vector<char>::iterator it=G.topologic_list.begin();it!=G.topologic_list.end();++it){
    cout << *it << " - ";
}
   cout<<'\n';

cout<<"------------- topological sort list check <only valid for DAG> done\n\n"<<endl;



G.findoutSCC();

      return 0;
}
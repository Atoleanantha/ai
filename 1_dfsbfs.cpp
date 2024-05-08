#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
struct node{
    string value;
    node* next;
};

class graph{

    public:
        int n; //number of nodes
        struct node* head[20]; //head node array
        int visited[20];
        graph(){
            cout<<"Enter number of nodes: ";
            cin>>n;

            // initiliza head node array
            for(int i=0;i<20;i++){
                head[i]=new node;
                head[i]->value="-";
                head[i]->next=NULL;
                visited[i]=0;
            }
        }
        
        void createGraph();
        void display();
        void bfs();
        void dfs();
    protected:
        void bfs_helper(queue<string>& q,int i);
        void dfs_helper(node *temp,int index, stack<string>& s);

       
};


void graph :: createGraph(){
    
    int x;
    node *temp;
    for( int i=0;i<n;i++){

        cout<<"Enter node:";
        cin>>head[i]->value;

        cout<<"Enter number of connected nodes to"<<head[i]->value<<" : ";
        cin>>x;

        for(int j=0;j<x;j++){
            node *nnode=new node;
            nnode->next=NULL;
            cout<<"Enter connected node: ";
            cin>>nnode->value;
            temp=head[i];
            while(temp->next !=NULL){
                    temp=temp->next;
            }
            temp->next=nnode;
        }
    }
}


void graph ::display(){
    node *temp;
    for(int i=0;i<n;i++){
        temp=head[i];
        cout<<temp->value<<"-> \t";
        while(temp->next!=NULL){
            temp=temp->next;
            cout<<temp->value<<",\t ";
        }
        cout<<endl;
    }
    
}

void graph :: bfs(){
    queue<string> q;

    for(int i=0;i<n;i++){
        visited[i]=0;
    }

    q.push(head[0]->value);
    visited[0]=1;

    bfs_helper(q,0);

}

void graph:: bfs_helper(queue<string>& q,int i){
    if(q.empty()){
        return;
    }

    string a=q.front();
    q.pop();
    cout<<a;
    //find index of a in head
    while(a!=head[i]->value){
        i++;
    }

    node* temp=head[i];
    while(temp!=NULL){

        int j=0;
        while(temp->value !=head[j]->value){
            j++;
        }
        if(visited[j]==0){
            visited[j]=1;
            q.push(temp->value);
        }
        temp=temp->next;
    }

    //recursive
    bfs_helper(q,0);
}

void graph::dfs() {
    // Initialize visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Create a stack for DFS traversal
    stack<string> s;

    // Start DFS from the first node
    s.push(head[0]->value);
    visited[0] = 1;
    cout << head[0]->value;

    // Perform DFS
    dfs_helper(head[0]->next, 1, s);
}

void graph::dfs_helper(node* temp, int index, stack<string>& s) {
    if (temp == NULL) {
        return;
    }

    // Find the index of the current node in the head array
    int i = 0;
    while (i < n && head[i]->value != temp->value) {
        i++;
    }

    // Process the current node if not visited
    if (i < n && visited[i] == 0) {
        cout << temp->value;
        visited[i] = 1;
        s.push(temp->value); // Push the current node onto the stack
        dfs_helper(head[i]->next, i, s); // Recur for the next node in the adjacency list
    }

    // Move to the next node in the adjacency list
    dfs_helper(temp->next, index, s);
}


int main(){
    graph g;
    g.createGraph();
    g.display();
    cout<<"bfs: ";
    g.bfs();
    cout<<endl;
    cout<<"dfd: ";
    g.dfs();
    cout<<endl;
    return 0;
}


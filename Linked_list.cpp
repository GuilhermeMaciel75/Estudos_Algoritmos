#include <iostream>

#define ednl '\n'

using namespace std;

struct Node
{
    int val;

    Node * next;

};

Node* list_add(Node* head, Node* p, int value){

    head = new Node;
    p->next = head;
    head->val = value;
    head->next = NULL;

    return head;

}

void list_show(Node* i){

    while(i->next != NULL){
        i = i->next;
        cout << i->val << '\n';
    }

}

Node* list_search(Node* i, int posi){

    i = i->next;

    for(int j = 0; j < posi; j++){
        i = i->next;
    }

    return i;
}

int list_index(Node* i, int value){

    int posicao = 0;

    while(i->next != NULL && i->next->val != value){

        i = i->next;
        posicao += 1;

    }

    return posicao;

}

Node* list_insert(Node* head, Node* p, Node* i, int value, int posi){

    i = list_search(i, posi - 1);

    head = new Node;
    head->next = i->next;
    i->next = head;
    head->val = value;

    return head;

}

int list_delete(Node* head, Node* p, Node* i, int posi){
    i = list_search(i, posi - 1);

    Node *pp;
    int val;

    pp = i -> next;
    i->next = pp -> next;
    val = pp->val;
    free(pp);

    return val;
}

int main(){

    Node *head, *p, *inicio, *print;

    int result, value, posi, val_delete;

    //head 
    head = new Node;
    inicio = head;
    head->val = 0;
    head->next = NULL;
    p = head;

    while(1){
        cout << '\n' << '\n' << "Escolha uma opção" << '\n';
        cout << "1 - Adicionar ao final da lista" << '\n';
        cout << "2 - Adicionar em uma posição específica lista" << '\n';
        cout << "3 - Mostrar um valor a partir de um índice" << '\n';
        cout << "4 - Mostrar um índice a partir de um valor" << '\n';
        cout << "5 - Deletar um Item da lista" << '\n';
        cout << "6 - Mostrar a estrutura atual" << '\n' << '\n' << '\n';

        cin >> result;

        switch (result)
        {
        case 1:

            cout << "Insira o valor a ser adicionado" << '\n';
            cin >> value;
            p = list_add(head, p, value);

            break;

        case 2:

            cout << "Diga a posição em que você quer inserir: " << '\n';
            cin >> posi;

            cout << "Diga o numero em que você quer inserir: " << '\n';
            cin >> value;

            p = list_insert(head, p, inicio, value, posi);

            break;

        case 3:
            cin >> posi;

            print = list_search(inicio, posi);
            
            cout << "A posição - " << posi << " Corresponde ao número: " << print->val << '\n';

            break;

        case 4:

            cin >> value;

            cout << "A posição - " << list_index(inicio, value)  << " Corresponde ao número: " << value << endl;

            break;

        case 5:

            cout << "Digite a posição a ser excluida" << '\n';
            cin >> posi;

            val_delete = list_delete(head, p, inicio, posi);

            cout << "O valor " << val_delete << " Foi deletado" << '\n';

            break;

        case 6:

            list_show(inicio);

            break;

        default:
            cout << "Valor inválido" << '\n' << '\n';
            break;
        }



    }

    delete [] head, p, inicio;

}
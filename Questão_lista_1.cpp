#include <iostream>

#define ednl '\n'

using namespace std;

//Struct responsável por salvar as paginas para ver depois (Pilha)
struct Save 
{
    string pagina_salva;

    Save * next2;
};

// Histórico de páginas acessadas (Fila)
struct historico
{
    string pagina;

    historico * next;
};

//Função responsácvel por adicionar uma página ao histórico
historico* hist_add(historico* head, historico* i, string value){

    head = new historico;
    head->next = i->next;
    i->next = head;
    head->pagina = value;

    return head;

}

//Função responsável por apagar uma página do histórico
historico* hist_back(historico* head, historico* p, historico* i, int posi){

    historico *pp;
    string val;

    pp = i -> next;
    i->next = pp -> next;
    val = pp->pagina;
    free(pp);

    return i -> next;

}

//Função responsável por adicionar uma página para ser vista depois 
Save* save_add(Save* head2, Save* p2, string value){

    head2 = new Save;
    p2->next2 = head2;
    head2->pagina_salva = value;
    head2->next2 = NULL;

    return head2;

}

//Função responsável por levar o cursor até o começo da pilha
Save* save_search(Save* k, int posi){

    for(int j = 0; j < posi; j++){
        k = k->next2;
    }

    return k;
}

//Remove o elemento da pilha (Primeira página para ser vista depois)
Save* save_rea(Save* head2, Save* p2, Save* i, int posi){

    i = save_search(i, posi - 1);

    Save *pp;
    string val;

    pp = i -> next2;
    i -> next2 = pp -> next2;
    val = pp->pagina_salva;
    free(pp);

    return i;

}

int main(){

    //Declaração de variáveis
    string input, endereco;
    historico *head, *p, *inicio;
    Save *head2, *p2, *inicio2;
    int n_paginas = 0, paginas_apagadas = 0, paginas_nao_lidas = 0;

    //head historico
    head = new historico;
    inicio = head;
    head->pagina = " ";
    head->next = NULL;
    p = head;

    //head Save

    head2 = new Save;
    inicio2 = head2;
    head2->pagina_salva = " ";
    head2->next2 = NULL;
    p2 = head2;

    //Recebendo o primeiro input de entrada
    cin >> input;

    while (input != "END")
    {   

        //Estrutura condicional responsável por verificar o comando de navegação
        if(input == "OPN"){
            //Recebemos o endereço da pagina acessada, o passa para dentro a função e é adicionado a lista
            cin >> endereco;

            p = hist_add(head, inicio, endereco);

            n_paginas += 1; 

            cout << n_paginas << '\n';

        }

        else if(input == "CUR"){

            cout << p->pagina << '\n';

        }

        else if(input == "BCK"){
            
            //verificar se há a necessidade de printar null
            if(n_paginas == 0 || n_paginas == 1){

                p = hist_back(head, p, inicio, n_paginas);
                n_paginas -= 1;
                cout << "NULL" << '\n';
            }

            else{

                p = hist_back(head, p, inicio, n_paginas - 1);
                n_paginas -= 1;
                cout << p->pagina << '\n';

            }

        }

        else if(input == "PAN"){

            cout << n_paginas << '\n';

            //Loop responsável por apagar todas as páginas do histórico
            while(n_paginas != 0){

                p = hist_back(head, p, inicio, n_paginas);
                n_paginas -= 1;

            }

        }

        else if(input == "SAV"){

            //pega a ultima pagina adicoinada ao histórico e a utiliza para adiciona-la para leitura posterior
            p2 = save_add(head2, p2, p->pagina);
            paginas_nao_lidas += 1;

            cout << paginas_nao_lidas << '\n';

        }

        else if(input == "REA"){

            //Caso o número da paginas seja 0, printar NULL
            if(paginas_nao_lidas == 0){

                p2 = save_rea(head2, p2, inicio2, paginas_nao_lidas);
                cout << "NULL" << '\n';
                paginas_nao_lidas -= 1;
            }

            else{

                cout << p2->pagina_salva  << '\n';
                p2 = save_rea(head2, p2, inicio2, paginas_nao_lidas);
                paginas_nao_lidas -= 1;

            }
            
        }

        //Recebendo mais uma entrada de comando de informação
        cin >> input;

    }

    //Deletando os ponteiros utilizados
    delete(head2, head, p, p2, inicio2, inicio);

}
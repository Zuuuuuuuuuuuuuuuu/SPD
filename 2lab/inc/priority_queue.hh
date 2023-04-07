#ifndef PRIOQ
#define PRIOQ
#include <vector>
using namespace std; 

//struktura wewnatrz wektora
struct parameters
{
    int j;
    int r;
    int p;
    int q;
};

//STRUKTURA
struct s_list
{
    s_list *next;
    parameters el;
    int prio;
};

//KLASA
class prio_q
{
    private:
        int e_numb = 0;
        s_list *head;
        s_list *tail;
    public:
        prio_q();
        ~prio_q();
        bool isEmpty();
        parameters max();
        void removeMax();
        int  priority();
        void insert(parameters el, int prio);
        int get_e_numb() {return e_numb;}
};
#endif

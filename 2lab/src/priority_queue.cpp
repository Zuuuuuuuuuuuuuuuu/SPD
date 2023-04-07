#include "priority_queue.hh"
#include <iostream>

using namespace std;

//FUNKCJE KLASY PRIO_Q
prio_q::prio_q()
{
    head = NULL;
}

prio_q::~prio_q()
{
    while(head)
    {
        removeMax();
    }
}

bool prio_q::isEmpty()
{
    return !head;
}

parameters prio_q::max()
{
    if(head)
    {
        return head->el;
    }
    else
    {
        throw "EmptyQueueException";
    }
}

void prio_q::removeMax()
{
    if(head)
    {
        s_list* p = head;
        head = head->next;
        if (!head)
        {
            tail = NULL;
        }
        //delete p;     // SEG FAULT
        e_numb--;  
    }
    else
    {
        throw "EmptyQueueException";
    }

}

void prio_q::insert(parameters el, int prio)
{
    e_numb++;
    s_list *p, *r;
    p = new s_list;
    p->next = NULL;
    p->prio = prio;
    p->el = el;
    if (!head)
    {
        head = p;
        tail = p;
    }
    else if (head->prio < prio)
    {
        p->next = head;
        head = p;
    }
    else
    {
        r = head;
        while ((r->next) && (r->next->prio >= prio))
            {
                r = r->next;
            }
        p->next = r->next;
        r->next = p;
        if(!p->next)
        {
            tail = p;
        }
    }
}

int  prio_q::priority()
{
    if(!head)
    {
        throw "EmptyQueueException";
    }
    else
    { 
        return head->prio;
    }
}

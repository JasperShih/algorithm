//
// Created by root on 9/24/17.
//
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class Elem {
    void *data;

    Elem() {}

    //create: () -> Elem*
    static Elem *create() {
        Elem *elem = new Elem;
        elem->data = NULL;
        return elem;
    }

    //get_data: Elem* -> void*
    void *get_data() {
        return data;
    }

    //set_data: Elem* X void* X size_t -> void
    void set_data(void *_data, size_t size) {
        data = calloc(1, size);
        memcpy(data, _data, size);
    }

public:
    //to_elem: void* X size_t -> Elem*
    static Elem *to_elem(void *_data, size_t size) {
        Elem *elem = create();
        elem->set_data(_data, size);
        return elem;
    }

    //_delete: Elem* -> ()
    void _delete() {
        free(get_data());
        delete this;
    }

    //show: Elem* -> ()
    void show() {
        cout << *(int *) get_data() << endl;
    }
};

//tOdO do we really need to open get_next & set_next?
class List {
    Elem *elem;
    List *next;

    List() {}

    //set_elem: List* X elem* -> ()
    void set_elem(Elem *_elem) {
        elem = _elem;
    }

public:
    //get_elem: List* -> elem*
    Elem *get_elem() {
        return elem;
    }

    //get_next: List* -> List*
    List *get_next() {
        return next;
    }

    //set_next: List* X List* -> ()
    void set_next(List *_list) {
        next = _list;
    }

    //is_tail: List* -> bool
    bool is_tail() {
        return get_next() == NULL;
    }

    //create: () -> List*
    static List *create() {
        List *list = new List;

        list->set_elem(NULL);
        list->set_next(NULL);
        return list;
    }

    //add_elem: List* X Elem* -> List*
    List *add_elem(Elem *_elem) {
        List *list = create();

        list->set_elem(_elem);
        list->set_next(this);
        return list;
    }

    //del_elem: List* -> List*
    List *del_elem() {
        List *list = get_next();

        get_elem()->_delete();
        delete this;
        return list;
    }

    //add_list: List* X List* -> List*
    List *add_list(List *list) {
        List *pre = NULL;
        List *now = list;

        for (;;) {
            if (now->is_tail()) {
                now->del_list();
                if (pre == NULL) {
                    return this;
                } else {
                    pre->set_next(this);
                    return list;
                }
            } else {
                pre = now;
                now = now->get_next();
            }
        }
    }

    //del_list: List* -> ()
    void del_list() {
        List *now;
        for (now = this; !now->is_tail(); now = now->del_elem()) {}
        delete now;
    }

    //show: List* -> ()
    void show() {
        List *now;
        for (now = this; !now->is_tail(); now = now->get_next()) {
            now->get_elem()->show();
        }
    }
};

class DList {
    List *current;
    List *prev;

    //get_current: DList* -> List*
    List *get_current() {
        return current;
    }

    //get_prev: DList* -> List*
    List *get_prev() {
        return prev;
    }

    //set_current: DList* X List* -> DList*
    void set_current(List *list) {
        current = list;
    }

    //set_prev: DList* X List* -> DList*
    void set_prev(List *list) {
        prev = list;
    }

    DList() {}

public:
    //get_elem: DList* -> Elem*
    Elem* get_elem(){
        return get_current()->get_elem();
    }

    //create: () -> DList*
    static DList *create() {
        DList *dlist = new DList;

        dlist->set_current(List::create());
        dlist->set_prev(List::create());
        return dlist;
    }

    //is_current_tail: DList* -> bool
    bool is_current_tail() {
        return get_current()->is_tail();
    }

    //is_prev_tail: DList* -> bool
    bool is_prev_tail() {
        return get_prev()->is_tail();
    }

    //is_tail: DList* -> bool
    bool is_tail() {
        return is_current_tail() && is_prev_tail();
    }

    //move_to_next: DList* -> DList*
    void move_to_next() {
        List *list = get_current()->get_next();

        get_current()->set_next(get_prev());
        set_prev(get_current());
        set_current(list);
    }

    //move_to_prev: DList* -> DList*
    void move_to_prev() {
        List *list = get_prev()->get_next();

        get_prev()->set_next(get_current());
        set_current(get_prev());
        set_prev(list);
    }

    //add_elem: DList* X Elem* -> DList*
    void add_elem(Elem *elem) {
        set_current(get_current()->add_elem(elem));
    }

    //del_elem: DList* -> DList*
    void del_elem() {
        set_current(get_current()->del_elem());
    }

    //add_dlist: DList* X DList* -> DList*
    void add_dlist(DList *dlist) {
        for (; !dlist->is_prev_tail(); dlist->move_to_prev()) {}
        dlist->get_prev()->del_list();
        set_current(get_current()->add_list(dlist->get_current()));
        delete dlist;
    }

    //del_dlist: DList* -> ()
    void del_dlist() {
        get_prev()->del_list();
        get_current()->del_list();
        delete this;
    }

    //show: DList* -> ()
    void show() {
        for (; !is_prev_tail(); move_to_prev()) {}
        get_current()->show();
    }
};

//shouldn't use defensive coding
//we should trust our program and defend the other people program
//defensive programming cannot correct coding logic error in run time
//it just (log it and) swallow it, and force the wrong state program to continue.
//it may result in worse situation.
//so, I think let it crash is better.
//Let it crash, and we immediately know where logic error when our coding, and rewrite it.
//If we have to force wrong state program keep going,
//maybe swallow error in the top flow control and log it, then restart the worker
//is one way.

//Caller knows that when List* is NULL and when List* is not.
//So don't consider List* is null when writing class List.
//It is caller responsibility.
int main() {
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;

    List *list1 = List::create();
    list1 = list1->add_elem(Elem::to_elem(&num1, sizeof(num1)));
    list1 = list1->add_elem(Elem::to_elem(&num2, sizeof(num2)));
    list1 = list1->add_elem(Elem::to_elem(&num3, sizeof(num3)));
    list1 = list1->add_elem(Elem::to_elem(&num4, sizeof(num4)));

    List *list2 = List::create();
    list2 = list2->add_elem(Elem::to_elem(&num1, sizeof(num1)));
    list2 = list2->add_elem(Elem::to_elem(&num2, sizeof(num2)));
    list2 = list2->add_elem(Elem::to_elem(&num3, sizeof(num3)));
    list2 = list2->add_elem(Elem::to_elem(&num4, sizeof(num4)));

    list2 = list2->del_elem();
    list1 = list1->add_list(list2);
    list1->show();
    list1->del_list();

//==============================================================

    DList *dlist1 = DList::create();
    dlist1->add_elem(Elem::to_elem(&num1, sizeof(num1)));
    dlist1->add_elem(Elem::to_elem(&num2, sizeof(num2)));
    dlist1->add_elem(Elem::to_elem(&num3, sizeof(num3)));
    dlist1->add_elem(Elem::to_elem(&num4, sizeof(num4)));

    DList *dlist2 = DList::create();
    dlist2->add_elem(Elem::to_elem(&num1, sizeof(num1)));
    dlist2->add_elem(Elem::to_elem(&num2, sizeof(num2)));
    dlist2->add_elem(Elem::to_elem(&num3, sizeof(num3)));
    dlist2->add_elem(Elem::to_elem(&num4, sizeof(num4)));

    dlist1->move_to_next();
    dlist1->move_to_next();

    dlist2->del_elem();
    dlist1->add_dlist(dlist2);
    dlist1->show();
    dlist1->del_dlist();
}

/*
    [root@localhost untitled1]# valgrind --leak-check=full ./a.out
    ==11787== Memcheck, a memory error detector
    ==11787== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
    ==11787== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
    ==11787== Command: ./a.out
    ==11787==
    3
    2
    1
    4
    3
    2
    1
    4
    3
    3
    2
    1
    2
    1
    ==11787==
    ==11787== HEAP SUMMARY:
    ==11787==     in use at exit: 0 bytes in 0 blocks
    ==11787==   total heap usage: 56 allocs, 56 frees, 576 bytes allocated
    ==11787==
    ==11787== All heap blocks were freed -- no leaks are possible
    ==11787==
    ==11787== For counts of detected and suppressed errors, rerun with: -v
    ==11787== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/

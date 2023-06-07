class operation
{
public:

    int j; //numer zadania
    int p; //czas trwania
    int C; //czas zakończenia

    operation(int j, int p);
};

operation::operation(int j, int p) : j(j), p(p) {}

class parameter
{
public:
    std::vector<operation>op;
    void addoperation(operation tmp);
    int last();
};

void parameter::addoperation(operation tmp) 
{
    op.push_back(tmp);
}

int parameter::last() 
{
    return this->op.size() - 1;
}
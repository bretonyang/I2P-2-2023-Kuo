struct song{
    int num;
    song *pre, *next;
};

void print(song *st, song *en);

class ordering_system{
    private:
        song *head, *tmp1, *tmp2;
    public:
        void initialize();
        void order(int k);
        void play();
        void show();
        void insert(int k);
        void destroy();
};

/**

played | inserted | ordered

8
play
order 4
order 5
insert 1
show
play
play
show

*/









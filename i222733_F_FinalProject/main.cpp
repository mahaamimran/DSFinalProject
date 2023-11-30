#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Header.h"
int main() {
    Graph g(9);
    generateMap(g);
    for(int i=0;i<9;i++){
        g.display(3,3,i);
    }
    return 0;
}

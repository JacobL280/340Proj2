//
// Created by Jacob on 3/3/2021.
//

#ifndef INC_340PROJ2_REG_H
#define INC_340PROJ2_REG_H


struct REG_node {
    struct REG_node * first_neighbor;
    char first_label;
    struct REG_node * second_neighbor;
    char second_label;
};

struct REG {
    struct REG_node * start;
    struct REG_node * accept;
};

#endif //INC_340PROJ2_REG_H

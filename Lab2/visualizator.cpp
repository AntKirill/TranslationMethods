//
// Created by kirant on 15.10.17.
//

#include "visualizator.h"
#include <graphviz/gvc.h>

static Agraph_t *g;
static GVC_t *gvc;

static int cnt;

static std::string gen_fresh_name();

static std::string gen_fresh_name() {
    return std::to_string(cnt++);
}

static FILE *create_png(const std::string &out_file_name) throw() {
    gvLayout(gvc, g, "dot");

    std::string out = out_file_name + ".png";
    FILE *pFile = fopen(out.c_str(), "w");

    gvRender(gvc, g, "png", pFile);
    gvFreeLayout(gvc, g);
    agclose(g);
    assert (gvFreeContext(gvc) == 0);
    return pFile;
}

static Agnode_t *add_node(std::string str_on_node) {
    std::string k = gen_fresh_name();
    Agnode_t *u = agnode(g, &k[0], true);
    std::string attribute = "label";
    agset(u, &attribute[0] , &str_on_node[0]);
    return u;
}

static Agnode_t *create_graph(const parser::iterator &v) {
    Agnode_t *node_v = add_node(v.get_name());
    for (auto &u: v.get_all_children()) {
        Agnode_t *node_u = create_graph(u);
        agedge(g, node_v, node_u, nullptr, true);
    }
    return node_v;
}

FILE *png_from_tree(const parser::iterator &root, std::string file_name) {
    cnt = 0;

    gvc = gvContext();
    std::string graph_name = "my_graph";
    g = agopen(&graph_name[0], Agstrictdirected, nullptr);

    create_graph(root);

    return create_png(file_name);
}

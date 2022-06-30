#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include <algorithm>


// small test data (graph example from lecture slides)
constexpr int N1 = 6;
// clang-format off
constexpr std::array<int, static_cast<size_t>(N1) * static_cast<size_t>(N1)> weights_table_1{{
                                                                                                     -1,  3, -1, -1,  6,  5,
                                                                                                     3, -1,  1, -1, -1,  4,
                                                                                                     -1,  1, -1,  6, -1,  4,
                                                                                                     -1, -1,  6, -1,  8,  5,
                                                                                                     6, -1, -1,  8, -1,  2,
                                                                                                     5,  4,  4,  5,  2, -1
                                                                                             }};
// clang-format on

// larger test data
// test data: distances between major German cities
//    vertices are cities
//    edges denote city connections
//    weights denote travel distances

constexpr int N2 = 20;
// clang-format off
constexpr std::array<int, static_cast<size_t>(N2) * static_cast<size_t>(N2)> weights_table_2{{
                                                                                                     -1, 255, 504, 477, 424, 512, 477, 422, 453, 315, 165, 149, 249, 378, 471, 439, 452, 336, 479, 398,
                                                                                                     255,  -1, 612, 356, 393, 534, 338, 284, 308,  95, 377, 294, 132, 462, 321, 297, 320, 196, 370, 237,
                                                                                                     504, 612,  -1, 456, 304, 190, 486, 477, 493, 582, 359, 360, 488, 150, 503, 486, 470, 483, 433, 510,
                                                                                                     477, 356, 456,  -1, 152, 288,  34,  72,  57, 269, 474, 380, 249, 336,  56,  62,  37, 162,  25, 123,
                                                                                                     424, 393, 304, 152,  -1, 152, 182, 177, 190, 329, 371, 293, 261, 187, 200, 184, 167, 212, 131, 218,
                                                                                                     512, 534, 190, 288, 152,  -1, 322, 328, 335, 478, 412, 364, 401, 157, 342, 332, 311, 364, 264, 371,
                                                                                                     477, 338, 486,  34, 182, 322,  -1,  57,  30, 248, 485, 389, 240, 363,  23,  41,  26, 150,  59, 101,
                                                                                                     422, 284, 477,  72, 177, 328,  57,  -1,  32, 196, 439, 340, 182, 343,  49,  17,  36,  93,  90,  51,
                                                                                                     453, 308, 493,  57, 190, 335,  30,  32,  -1, 217, 470, 371, 212, 364,  18,  14,  24, 122,  81,  70,
                                                                                                     315,  95, 582, 269, 329, 478, 248, 196, 217,  -1, 405, 310, 100, 433, 229, 207, 231, 118, 285, 150,
                                                                                                     165, 377, 359, 474, 371, 412, 485, 439, 470, 405,  -1, 100, 312, 259, 487, 456, 460, 375, 467, 434,
                                                                                                     149, 294, 360, 380, 293, 364, 389, 340, 371, 310, 100,  -1, 214, 229, 389, 358, 363, 275, 375, 334,
                                                                                                     249, 132, 488, 249, 261, 401, 240, 182, 212, 100, 312, 214,  -1, 338, 229, 199, 217,  90, 258, 151,
                                                                                                     378, 462, 150, 336, 187, 157, 363, 343, 364, 433, 259, 229, 338,  -1, 377, 355, 343, 337, 318, 370,
                                                                                                     471, 321, 503,  56, 200, 342,  23,  49,  18, 229, 487, 389, 229, 377,  -1,  32,  33, 138,  81,  84,
                                                                                                     439, 297, 486,  62, 184, 332,  41,  17,  14, 207, 456, 358, 199, 355,  32,  -1,  26, 109,  84,  61,
                                                                                                     452, 320, 470,  37, 167, 311,  26,  36,  24, 231, 460, 363, 217, 343,  33,  26,  -1, 128,  58,  85,
                                                                                                     336, 196, 483, 162, 212, 364, 150,  93, 122, 118, 375, 275,  90, 337, 138, 109, 128,  -1, 175,  62,
                                                                                                     479, 370, 433,  25, 131, 264,  59,  90,  81, 285, 467, 375, 258, 318,  81,  84,  58, 175,  -1, 142,
                                                                                                     398, 237, 510, 123, 218, 371, 101,  51,  70, 150, 434, 334, 151, 370,  84,  61,  85,  62, 142,  -1
                                                                                             }};

// clang-format on

struct Vertex
{
    static constexpr int max_key = std::numeric_limits<int>::max();
    static constexpr int undefined = -1;

    int index = 0; // vertex identifier
    int key = max_key; // temporary minimal weight (Prim algorithm)
    int parent_index = undefined; // temporary minimal distance neighbor vertex (Prim algorithm)
    bool processed = false; // flag used to mark vertices that are already included in V'
};

struct Edge
{
    std::array<int, 2> connected_vertices;
    int weight;
};

struct Graph
{
    int vertex_count = 0; // number of vertices
    std::vector<Vertex> vertices; // set of vertices
    std::vector<Edge> edges; // set of edges
    std::vector<Edge> mst; // minimal spanning tree
    const int* weights_table = nullptr; // weights given as distance matrix
};

int getWeight(Graph& graph, int i, int j) // encapsulates access to (hard-coded) weight tables
{
    assert(i >= 0 && i < graph.vertex_count); // check index i
    assert(j >= 0 && j < graph.vertex_count); // check index j

    size_t index = static_cast<size_t>(i) + static_cast<size_t>(j) * graph.vertex_count;
    assert(graph.weights_table[index] == graph.weights_table[index]); // weights must be symmetric

    return graph.weights_table[index];
}

// pretty vertex printing
std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
{
    os << static_cast<char>('a' + vertex.index); // a, b, c, ...
    return os;
}

// pretty edge printing
std::ostream& operator<<(std::ostream& os, const std::vector<Edge>& edges)
{
    os << "{";
    for (size_t i = 0; i < edges.size(); ++i)
    {
        os << (i > 0 ? "," : "") << "(" << static_cast<char>('a' + edges[i].connected_vertices[0]) << ","
           << static_cast<char>('a' + edges[i].connected_vertices[1]) << ")";
    }
    os << "}";
    return os;
}

// construct vertices and edges for a given graph
void createGraph(Graph& graph)
{
    // TODO 5.1a: clear graph.vertices and graph.edges and insert all vertex objects and edge objects
    // - vertices are numbered (labeled) from 0 to graph.vertex_count-1
    // - edges exist if and only if there is positive distance between two vertices
    // - edges are bidirectional, that is, edges are inserted only once between two vertices

    graph.vertices.clear();
    graph.edges.clear();

    // also add vertices
    for (int i = 0; i < graph.vertex_count; i++) {
        graph.vertices.push_back(Vertex{
            i,
        });
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = graph.vertex_count - 1; j >= i; j--) {
            if (getWeight(graph, i, j) < 0)
                continue;
            Edge newedge = Edge{
                    {i,j},
                    getWeight(graph, i,j),
            };
            graph.edges.push_back(newedge);
        }
    }

    /*
    for (int i = 0; i < graph.vertex_count; ++i)
    {
        graph.vertices.push_back({i});
        for (int j = 0; j < graph.vertex_count; ++j)
        {
            if (getWeight(graph, i, j) > 0)
            {
                //check if edge already in edges
                if (std::end(graph.edges) == std::find_if(std::begin(graph.edges), std::end(graph.edges), [i,j](Edge e){
                            if (e.connected_vertices[0] == j && e.connected_vertices[1]==i){
                                return true;
                            }
                            return false;
                        }))
                    continue;
                //set edge
                graph.edges.push_back(Edge{std::array<int, 2>{i, j}, getWeight(graph, i, j)});
            }
        }
    }*/
}

// return added weights of a list of edges
int totalWeight(const std::vector<Edge>& edges)
{
    // TODO 5.1b: total weight accumulated over a given list of edges
    int total = 0;

    for (size_t i = 0; i < edges.size(); ++i)
    {
        total += edges[i].weight;
    }

    return total;
}

void prim(Graph& graph)
{
    graph.mst.clear();
    graph.vertices[0].key = 0; // arbitrarily defined start vertex, taken to vertices

    // TODO 5.1c: implement prim algorithm

    assert(!graph.vertices.empty());

    graph.vertices[0].processed = true;

    Edge minimal_edge = Edge{
            {0,0},
            std::numeric_limits<int>::max(),
    };

    //find current route with minimal weight (that leads from a processed vertex to a non processed one)
    for (int h = 0; h < graph.vertex_count-1; h++) {
        for (int i = 0; i < graph.vertex_count; i++)
        {
            //check if vertex has been processed
            if (!graph.vertices[i].processed)
                continue;

            //go through all edges of the graph to look for edges that are connected with current vertex
            for (int j = 0; j < graph.edges.size(); j++) {
                Edge curr_edge = graph.edges[j];

                //because edges are just once in edge array both directions have to be checked
                if (curr_edge.connected_vertices[0]==i ) {

                    //the other vertex of the edge has to be a non processed one
                    if (graph.vertices[curr_edge.connected_vertices[1]].processed){
                        continue;
                    } else if (minimal_edge.weight > curr_edge.weight)
                        minimal_edge = curr_edge;

                } else if (curr_edge.connected_vertices[1]==i) {
                    if (graph.vertices[curr_edge.connected_vertices[0]].processed){
                        continue;
                    } else if (minimal_edge.weight > curr_edge.weight)
                        minimal_edge = curr_edge;
                }
            }
        }
        graph.vertices[minimal_edge.connected_vertices[0]].processed = true;
        graph.vertices[minimal_edge.connected_vertices[1]].processed = true;
        graph.mst.push_back(minimal_edge);
        minimal_edge.weight = std::numeric_limits<int>::max();
    }
}

int main()
{
    // Example 1 (small)
    Graph graph1;
    graph1.vertex_count = N1;
    graph1.weights_table = weights_table_1.data();
    createGraph(graph1);
    prim(graph1);
    std::cout << "Example 1: " << graph1.mst << ", total costs: " << totalWeight(graph1.mst) << std::endl;

    // Example 2 (larger)
    Graph graph2;
    graph2.vertex_count = N2;
    graph2.weights_table = weights_table_2.data();
    createGraph(graph2);
    prim(graph2);
    std::cout << "Example 2: " << graph2.mst << ", total costs: " << totalWeight(graph2.mst) << std::endl;

    return 0;
}
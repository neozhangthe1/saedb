/* Copyright (C)
 * 2013 - Yutao Zhang
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include <iostream>
#include "sae_include.hpp"
#include "sample_data.cpp"

class vdata{
public:
    std::vector<int> vid_set;

    int size(){
        return vid_set.size();
    }
}

class edate{
public:
}

//define the triangle count data structure
class triangle_count{
public:
    int out_triangles;
    int in_triangles;
    int through_triangles;
    int cycle_triangles;

    triangle_count& operator+=(const triangle_count& other){
        out_triangles += other.out_triangles;
        in_triangles += other.in_triangles;
        through_triangles += other.through_triangles;
        cycle_triangles += other.cycle_triangles;
        return *this;
    }
}

//define gather type
//it accumulates all neighboring vertices into a vector
class gather_set_union{
public:
    std::vector<int> vectices;

    int size() const{
        return vectices.size();
    }

    gather_set_union& operator+=(const gather_set_union& other){
        if(size() == 0){
            (*this) = other;
            return (*this);
        }else if(other.size() == 0){
            return (*this);
        }

        for(int i=0; i<other.vectices.size(); ++i){

        }
    }

}


/**
 * @brief Triangle Counting
 * This implemnts the counting procedure decribed in
 *  Efficient Algorithms for Large-Scale Local Triangle Counting
 *  each vertex maintains a list of all of its neighbor in a hash set
 *  for each edge(u,v) in the graph, count the number of intersections of the neighbor set on u and v
 *  store the size of the intersection on the edge
 * on gather, we accumulate a set of all adjacent vertices.
 */
class common_neighbors:
    public saedb::sae_algorithm<graph, gather_type>{
private:
    bool perform_scatter;

public:
    //gather on all edges
    edge_dir_type gather_edge(icontext_type& context,
            const vertex_type& vertex) const{
        return saedb::ALL_EDGES;
    }

    //for each edge, find the id of the "other" vertex and accumulate a set of the neighborhood vertex IDs
    gather_type gather(icontext_type& context,
            const vertex_type& vertex,
            edge_type& edge) const{
        set_union_gather gather;
        //get neighbor
        int n_id = (edge.target().id() == vertex.id()) ?
            edge.source().id() : edge.target().id();
        int n_degree = (edge.target().id() == vertex.id())?
            (edge.source().num_in_edges() + edge.source().num_out_edges()):
            (edge.target().num_out_edges() + edge.target().num_out_edges());
        int degree = vertex.num_in_edges() + vertex.num_out_edges();
        if ((n_degree > degree) || (n_degree == degree && n_id > vertex.id())){
            gather.v = n_id;
        }
        return gather;
    }

    //the gather result now contains the vertex Id in the neighborhood.
    //store it on the vertex
    void apply(icontext_type& context,
            vertex_type& vertex,
            const gather_type& neighborhood){
        perform_scatter = true;
        if (neighborhood.vertices.size() == 0){
            //only 0 or 1 neighbors
            vertex.data().vid_set.clear();
            if(neighborhood.v != -1){
                vertex.data().vid_set.vid_vec.push_back(neighborhood.v);
            }
        }else{
            vertex.data().vid_set.assign(neighborhood.vertices);
        }
        perform_scatter = vertex.data().vid_set.size() != 0;
    }

    edge_dir_type scatter_edge(icontext_type& context,
            const vertex_type& vertex) const{
        if(perform_scatter) return saedb::OUT_EDGES;
        else return saedb::NO_EDGES;
    }

    //count the intersection of the neighborhood of the adjacent vertices.
    //this is the number of triangle this edge is involved in
    void scatter(icontext_type& context,
            const vertex_type& vertex,
            edge_type& edge) const{
        const vertex_data_type& srclist = edge.source().data();
        const vertex_data_type& targetlist = edge.target().data();
        if (targetlist.vid_set.size() < srclist.vid_set.size()){
            edge.data() += count_set_intersect(targetlist.vid_set, srclist.vid_set);
        }else{
            edge.data() += count_set_intersect(srclist.vid_set, targetlist.vid_set);
        }
    }
}

class triangle_count:
    public saedb::sae_algorithm<graph_type, int>{
public:
    //gather on all edges
    edge_dir_type gather_edges(icontext_type& context,
            const vertex_type& vertex) const {
        return saedb::ALL_EDGES;
    }

    //gather the number of triangles each edge is involved in
    int gather(icontext_type& context,
            const vertex_type& vertex,
            edge_type& edge) const {
        return edge.data();
    }

    //the gather result is the total sum of the number of triangles
    //each adjacent edge is involved in.
    //dividing by 2 gives the number of triangle
    void apply(icontext_type& context,
            const vertex_type& vertex,
            edge_type& edge) const {
        vertex.data().vid_set.clear();
        vertex.data().num_triangle = num_triangles / 2;
    }

    //no scatter
    edge_dir_type scatter_edge(icontext_type& context,
            const vertex_type& vertex) const {
        return saedb::NO_EDGES;
    }
}


int main(){
    std::cout << "Triangle Counting...\n";

    //load graph
    graph_type graph = sample_graph();
    std::cout << "#vertices: "
        << graph.num_vertices()
        << " #edges:"
        << graph.num_edges()
        << std::endl;

    //running the engine
    saedb::sae_synchronous_engine<common_neighbors> engine_common_neighors(graph);
    engine_common_neighors.start();

    saedb::sae_synchronous_engine<triangle_count> engine_triangle_count(graph);
    engine_triangle_count.start();

    std::cout << "Done" << std::endl;
    return 0;
}
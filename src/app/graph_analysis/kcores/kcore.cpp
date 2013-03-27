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
#include <string>
#include "sae_include.hpp"
#include "sample_data.cpp"


/**
 * @brief This program implement the "k-core" decomposition algorithm
 * It's parallel version of
 *
 * An O(m) algorithm for cores decomposition of networks.
 *
 * - First, recursively remove everything with degree 1
 * - Then recursively remove everything with degree 2
 * - etc.
 */
typedef int vertex_data_type;
typedef float edge_data_type;
typedef saedb::sae_graph<vertex_data_type, edge_data_type> graph_type;

int current_k;

class kcore:
    public saedb::IAlgorithm<graph_type, float>{

private:
    //when a node just been deleted, it's neighbor will be signal in scatter
    bool just_deleted;

public:
    kcore():just_deleted(false) {}

    void init(icontext_type& context,
    		  vertex_type& vertex){
    	vertex.data() = vertex.num_in_edges() + vertex.num_out_edges();
    }

    edge_dir_type gather_edges(icontext_type& context,
            const vertex_type& vertex) const{
        return saedb::NO_EDGES;
    }

    //if the vertex has not yet been deleted
    //decrement the counter on the vertex
    //if the adjacency count of the vertex falls below k,
    //the vertex shall be deleted
    //the vertex data will be set to 0 designate that it is deleted
    void apply(icontext_type& context, vertex_type& vertex,
          const gather_type& total){
        if(vertex.data() > 0){
            if(vertex.data() < current_k){
                just_deleted = true;
                vertex.data() = 0;
            }
        }
    }

    //if the vertex is deleted, signal all neighbors on the scatter
    edge_dir_type scatter_edges(icontext_type& context,
          const vertex_type& vertex) const{
      return just_deleted ?
          saedb::ALL_EDGES : saedb::NO_EDGES;
    }

    void scatter(icontext_type& context,
    		     const vertex_type& vertex,
    		     edge_type& edge) const {
        vertex_type other = edge.source().id() == vertex.id() ? edge.target() : edge.source();
        if(other.data() > 0){
            context.signal(other);
        }
    }
};

graph_type sample_graph(){
    return LOAD_SAMPLE_GRAPH<graph_type>();
}

int main(){
    graph_type graph = sample_graph();

    int kmax = 10;
    int kmin = 0;
    saedb::SynchronousEngine<kcore> engine(graph);
    for(current_k = kmin; current_k <= kmax; current_k++){
        engine.start();
    }
    std::cout << "#vertices: "
        << graph.num_vertices()
        << " #edges:"
        << graph.num_edges() << std::endl;

      // engine.signal_all();
      engine.start();
      std::cout << "Done" << std::endl;
      return 0;
}

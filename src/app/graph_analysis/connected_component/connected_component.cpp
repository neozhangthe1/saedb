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

//define vertex data structure
class vdata{
public:
    long label;
};

//define gather type
class gather_type{
public:
	int label;
	gather_type(){
		label = -1;
	}
	//the sum function finds the minimum id of the connected component
	gather_type& operator+=(const gather_type& other){
		label = std::min<int>(label, other.label);
		return *this;
	}
};

//define data type
typedef vdata vertex_data_type;
typedef float edge_data_type;
typedef saedb::empty message_date_type;
typedef saedb::sae_graph<vertex_data_type, edge_data_type> graph_type;



/**
 * @brief Connected Component
 * Trajan's strong Connected Components algorithm
 * Input: a directed graph
 * Output: find all connected components in the graph, and also count the number of the vertex of each connected components
 * Reference: http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
 */
class connected_component:
    public saedb::IAlgorithm<graph_type, gather_type>{
private:
    // set perform_scatter to determine which edges to scatter on
    bool perform_scatter;

public:
    //set label to vertex id
    void init(icontext_type& context,
    		  vertex_type& vertex) {
    	vertex.data().label = vertex.id();
    }

    //gather on all the edges
    edge_dir_type gather_edges(icontext_type& context,
            				   const vertex_type& vertex) const{
        return saedb::ALL_EDGES;
    }

    //gather return neighbor's label
    gather_type gather(icontext_type& context,
            	 	   const vertex_type& vertex,
            	 	   edge_type& edge){
    	auto other_label = (edge.source().id() == vertex.id()) ?
    						edge.target().data().label : edge.source().data().label;
    	gather_type gather_data = gather_type();
    	gather_data.label = other_label;
    	return gather_data;
    }

    //change the vertex data if any of its neighbors have a lower data value
    void apply(icontext_type& context,
            vertex_type& vertex,
            const gather_type& min_neighbor_id){
        if(min_neighbor_id < vertex.data().label){
        	vertex.data().label = min_neighbor_id.label;
            perform_scatter = true;
        }else{
            perform_scatter = false;
        }
    }

    //only scatter on vertices whose label has been changed
    edge_dir_type scatter_edges(icontext_type& context,
            					const vertex_type& vertex) const{
        if(perform_scatter){
            return saedb::ALL_EDGES;
        }else{
            return saedb::NO_EDGES;
        }
    }

    //if a vertex's label has been changed, signal all it's neighbors
    void scatter(icontext_type& context,
            	 const vertex_type& vertex,
            	 edge_type& edge) const{
    	vertex_type other = (edge.source().id() != vertex.id()) ?
    						 edge.source() : edge.target();
    	context.signal(other);
    }
}

//require a reduce phase to aggregate all the data

int main(){
    std::cout << "Connected Component...\n";

    // load graph
    // todo read graph_dir and format
    graph_type graph = sample_graph();
    // graph.load_format(graph_dir, format);
    std::cout << "#vertices: "
        << graph.num_vertices()
        << " #edges:"
        << graph.num_edges() << std::endl;
    // graph.transform_vertices(init_vertex);

    // running the engine
    saedb::SynchronousEngine<connected_component> engine(graph);
    engine.signalAll();
    engine.start();

    std::cout << "Done" << std::endl;
    return 0;
}

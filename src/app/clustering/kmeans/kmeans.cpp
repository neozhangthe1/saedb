#include "sae_include.hpp"
#include "sample_data.hpp"

typedef float vertex_data_type;
typedef float edge_data_type;
typedef saedb::empty message_date_type;
typedef saedb::sae_graph<vertex_data_type, edge_data_type> graph_type;


struct cluster{
	cluster(): count(0), changed(false) { }
	std::vector<double> center;
	int count;
	bool changed;
};

std::vector<cluster> CLUSTERS;

int KMEANS_INITIALIZATION;
int NUM_CLUSTERS;

struct vertexData{
	std::vector<double> point;
	int best_cluster;
	double best_distance;
	bool changed;
};

struct edgeData{
	double weight;

	edgeData(): weight(0.0) { }
};

//aggregators

//draws a random sample from the data points that is
//proportionate ot the "best distance" stored in the vertex.
struct ramdomSampleAggregator {
	std::vector<double> vertices;
	double weight;

	ramdomSampleAggregator():weight(0) { }

};

class kmeans:
public saedb::IAlgorithm<graph_type, float>
{

};

graph_type sample_graph(){
    return LOAD_SAMPLE_GRAPH<graph_type>();
}

int main(){
    graph_type graph = sample_graph();

    std::cout << "#vertices: "
    << graph.num_vertices()
    << " #edges:"
    << graph.num_edges() << std::endl;

    //perform kmeans++ initialization
    for(KMEANS_INITIALIZATION = 0;
    	KMEANS_INITIALIZATION < NUM_CLUSTERS;
    	++KMEANS_INITIALIZATION) {

    }

    saedb::SynchronousEngine<kmeans> engine(graph);

    // aggregator
    float* init_rank = new float(0);
    saedb::IAggregator* max_pagerank = new Float_max_aggregator();
    max_pagerank->init(init_rank);
    engine.registerAggregator("max_pagerank", max_pagerank);

    // start engine
    engine.signalAll();
    engine.start();

    std::cout << "max pagerank: " << *((float*)max_pagerank->data()) << std::endl;
    std::cout << "Done" << std::endl;
    return 0;
}

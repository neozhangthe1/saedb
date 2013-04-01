#include "sae_include.hpp"
#include "sample_data.hpp"

typedef float vertex_data_type;
typedef float edge_data_type;
typedef saedb::empty message_date_type;
typedef saedb::sae_graph<vertex_data_type, edge_data_type> graph_type;

struct cluster {
	cluster() :
			count(0), changed(false) {
	}
	std::vector<double> center;
	int count;
	bool changed;
};

struct neighbor_info {
	std::map<int, double> cluster_weight_map;

	neighbor_info() :
			cluster_weight_map() {
	}

	neighbor_info& operator+=(const neighbor_info& other) {
		for (std::map<int, double>::const_iterator iter =
				other.cluster_weight_map.begin();
				iter != other.cluster_weight_map.end();
				iter++) {
			int clst = iter->first;
			if (cluster_weight_map.find(clst) == cluster_weight_map.end()) {
				cluster_weight_map.insert(std::make_pair(clst, iter->second));
			} else {
				cluster_weight_map[clst] += iter->second;
			}
		}
		return *this;
	}
};

std::vector<cluster> CLUSTERS;

int KMEANS_INITIALIZATION;
int NUM_CLUSTERS;
int MAX_ITERATION;

struct vertexData {
	std::vector<double> point;
	int best_cluster;
	double best_distance;
	bool changed;
};

struct edgeData {
	double weight;

	edgeData() :
			weight(0.0) {
	}
};

//aggregators

//draws a random sample from the data points that is
//proportionate ot the "best distance" stored in the vertex.
struct ramdomSampleAggregator {
	std::vector<double> vertices;
	double weight;

	ramdomSampleAggregator() :
			weight(0) {
	}

	void reduce(ramdomSampleAggregator* next) {
		double totalWeight = weight + next->weight;

		double myp = weight + next->weight;

	}

};

struct clusterCenterAggregator {
	std::vector<double> vertices;
	double weight;

	clusterCenterAggregator() :
			weight(0) {
	}

	void reduce(ramdomSampleAggregator* next) {
		double totalWeight = weight + next->weight;

		double myp = weight + next->weight;

	}

};

class ClusterAssignment: public saedb::IAlgorithm<graph_type, float> {
public:
	void init(icontext_type& context, vertex_type& vertex) {
		vertex.data() = 1.0;
	}

	//gather on all the edges
	edge_dir_type gather_edges(icontext_type& context,
			const vertex_type& vertex) const {
		return saedb::ALL_EDGES;
	}

	float gather(icontext_type& context, const vertex_type& vertex) const {

	}

	void apply(icontext_type& context, const vertex_type& vertex,
			edge_type& edge) const {

	}

	edge_dir_type scatter_edges(icontext_type& context,
			const vertex_type& vertex) const {

	}

	void scatter(icontext_type& context, const vertex_type& vertex) {

	}

};

graph_type sample_graph() {
	return LOAD_SAMPLE_GRAPH<graph_type>();
}

int main() {
	graph_type graph = sample_graph();

	std::cout << "#vertices: " << graph.num_vertices() << " #edges:"
			<< graph.num_edges() << std::endl;

	//perform kmeans++ initialization
	for (KMEANS_INITIALIZATION = 0; KMEANS_INITIALIZATION < NUM_CLUSTERS;
			++KMEANS_INITIALIZATION) {

	}

	//perform kmeans iterations
	bool clustersChanged = true;
	int iterationCount = 0;
	while (clustersChanged) {
		if (MAX_ITERATION > 0 && iterationCount >= MAX_ITERATION)
			break;
		//aggregate the cluster center
		//clusterCenterAggregator ag = graph.map_reduce...<cluster_center_reducer>(cluster_center_reducer::get_center);
		if (iterationCount > 0) {
			std::cout << "Kmeans iteration " << iterationCount << ": "
					<< "# points with changed assignments = " //<< cc.num_changed
					<< std::endl;
		}
		//find those cluster has been changed
		for (int i = 0; i < NUM_CLUSTERS; i++) {

		}

		saedb::SynchronousEngine<>
	}

	saedb::SynchronousEngine<kmeans> engine(graph);

	// aggregator
	float* init_rank = new float(0);
	saedb::IAggregator* max_pagerank = new ramdomSampleAggregator();
	max_pagerank->init(init_rank);
	engine.registerAggregator("max_pagerank", max_pagerank);

	// start engine
	engine.signalAll();
	engine.start();

	std::cout << "max pagerank: " << *((float*) max_pagerank->data())
			<< std::endl;
	std::cout << "Done" << std::endl;
	return 0;
}

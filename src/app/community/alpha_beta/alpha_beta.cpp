//#define DEGBUG
#include <iostream>
#include "sample_data.hpp"


#define ASSERT(X) {if (!(X)) { printf("ERROR LINE %d\n", __LINE__); exit(0); }}

struct AlphaBetaType{
	int alpha;
	int beta;

	AlphaBetaType(){
		alpha = 0;
		beta = 0;
	}

	AlphaBetaType(int alpha, int beta){
		this->alpha = alpha;
		this->beta = beta;
	}

	AlphaBetaType& operator+=(const AlphaBetaType& other){
		this->alpha += other.alpha;
		this->beta += other.beta;
		return *this;
	}
};

struct ABSetType{
	vector<saedb::vertex_id_type> setA;
	vector<saedb::vertex_id_type> setB;

	ABSetType(){
		setA = new vector();
		setB = new vector();
	}

	void addA(saedb::vertex_id_type vid){
		setA.push_back(vid);
	}

	void addB(saedb::vertex_id_type vid){
		setB.push_back(vid);
	}
};

struct VertexDataType{
	saedb::vertex_id_type id;
	bool isSeed;
	bool inCluster;
	AlphaBetaType alphaBeta;

	VertexDataType(){
		id = -1;
		isSeed = false;
		inCluster = false;
		alphaBeta = new AlphaBetaType();
	}

};

//define the aggregators
class AlphaBetaAggregator: public saedb::IAggregator
{
private:
	AlphaBetaType accu;

public:
    void init(void* i){
        accu = *((float*)i);
    }

    void reduce(void* next){
        accu.alpha = max(accu.alpha, ((AlphaBetaType*)next)->alpha);
        accu.beta = min(accu.beta, ((AlphaBetaType*)next)->beta);
    }

    void* data() const{
        return (void*)(&accu);
    }
};

class ABSetAggregator: public saedb::IAggregator
{
private:
	ABSetType abSet;

public:
    void init(void* i){
        abSet = new ABSetType();
    }

    void reduce(void* next){
    	VertexDataType* vertexData = next;
    	if(vertexData->inCluster){
    		abSet.setB.push_back(vertexData->id);
    	}else{
    		abSet.setA.push_back(vertexData->id);
    	}
    }

    void* data() const{
        return (void*)(&abSet);
    }
};

//aggregator instances
AlphaBetaAggregator* globalAlphaBeta;
ABSetAggregator* globalABSet;

//determine alpha_beta community size
int K = 100;
int* samples;


//define graph type
typedef float edge_data_type;
typedef AlphaBetaType gather_data_type;
typedef saedb::sae_graph<VertexDataType, edge_data_type> graph_type;

//caculate current global alpha beta
class AlphaBeta:
public saedb::IAlgorithm<graph_type, gather_data_type>{
private:

public:
	//random choose a subset of K vertices
	void init(icontext_type& context, vertex_type& vertex){
		vertex.data().id = vertex.id();
	}

	edge_dir_type gather_type(icontext_type& context, const vertex_type& vertex){
		return saedb::ALL_EDGES;
	}

	//compute alpha & beta value for each vertex
	float gather(icontext_type& context, const vertex_type& vertex, edge_type& edge){
		vertex_type other = edge.source_id != vertex.id() ?
					 edge.source() : edge.target();
		gather_data_type gather_data = new gather_data_type();
		if(other.data().inCluster){
			gather_data.alpha = 0;
			gather_data.beta = 1;
		}else{
			gather_data.alpha = 1;
			gather_data.beta = 0;
		}
		return gather_data;
	}

	void apply(icontext_type& context, vertex_type& vertex, gather_data_type& total){
		vertex.data().alphaBeta = total;

		saedb::IAggregator* alphaBetaAggerator = context.getAggregator("global_alpha_beta");
		AlphaBetaType* alphaBeta = alphaBetaAggerator->data();
		if(alphaBeta->alpha > alphaBeta->beta){
			//swapping
			if(vertex.data().inCluster){
				//in set B
#ifdef DEBUG
				ASSERT(vertex.data().alphaBeta.alpha <= globalAlphaBeta->data()->alpha);
#endif
				if(vertex.data().alphaBeta.alpha == ((AlphaBetaType*)globalAlphaBeta->data())->alpha){
					vertex.data().inCluster = false;
				}
			}else{
				//in set A
#ifdef DEBUG
				ASSERT(vertex.data().alphaBeta.beta >= globalAlphaBeta->data()->beta);
#endif
				if(vertex.data().alphaBeta.beta == ((AlphaBetaType*)globalAlphaBeta->data())->beta){
					vertex.data().inCluster = true;
				}
			}
			//end of swapping
		}else if(alphaBeta->alpha == alphaBeta->beta){

		}

	}

	edge_dir_type scatter_type(icontext_type& context, const vertex_type& vertex){
		return saedb::NO_EDGES;
	}

	void aggerate(icontext_type& context, const vertex_type& vertex){
		AlphaBetaAggregator* alphaBetaAggerator = context.getAggregator("global_alpha_beta");
		AlphaBetaType _alphaBeta = vertex.data().alphaBeta;
		alphaBetaAggerator->reduce(&_alphaBeta);
		if(_alphaBeta.alpha > _alphaBeta.beta){
			context.signal(vertex);
		}else if(_alphaBeta.alpha == _alphaBeta.beta){
			ABSetAggregator* abSetAggregator = context.getAggregator("global_ab_set");
			VertexDataType _vdata = vertex.data();
			abSetAggregator->reduce(&_vdata);

		}else{

		}
	}
};

//implemented swapping algorithm
class Swapping:
public saedb::IAlgorithm<graph_type, int>{
private:

public:
	edge_dir_type gather_type(icontext_type& context, const vertex_type& vertex){
		return saedb::ALL_EDGES;
	}

	void gather(icontext_type& context, const vertex_type& vertex, edge_type& edge){

	}

};



int reservoirSample(int sample, int* samples, int size, int count){
	if(count < sample)
		samples[count] = sample;
	else if((rand() % count) < size)
		sample[rand() % size] = sample;
	return ++count;
}

graph_type sampleGraph(){
	return LOAD_SAMPLE_GRAPH<graph_type>();
}

int main(){
	graph_type graph = sampleGraph();

	//random choose a subset of K vertices
	//implemented reservoir sampling
	int count = 0;
	samples = new int[K];
	int sample;
	int i = 0;
	srand(time(NULL));
	std::set id_set = graph.vertex_ids;
	int index = 0;
	for(int vertex_id : id_set){
		if(index<K)
			samples[index] = vertex_id;
		count = rand() % index;
		if(count < K){
			sample[count] = vertex_id;
		}
		index += 1;
	}

	//caculate global alpha beta
	saedb::SynchronousEngine<AlphaBeta> alphaBetaEngine(graph);
	//aggregator
    AlphaBetaType* initAlphaBeta = new AlphaBetaType();
    saedb::IAggregator* globalAlphaBeta = new AlphaBetaAggregator();
    globalAlphaBeta->init(initAlphaBeta);
    alphaBetaEngine.registerAggregator("global_alpha_beta", globalAlphaBeta);

    AlphaBetaType* initAlphaBeta = new AlphaBetaType();
    saedb::IAggregator* globalAlphaBeta = new AlphaBetaAggregator();
    globalAlphaBeta->init(initAlphaBeta);
    alphaBetaEngine.registerAggregator("global_ab_set", globalABSet);

    alphaBetaEngine.signalAll();
    alphaBetaEngine.start();

    //swapping phase
    saedb::SynchronousEngine<Swapping> swappingEngine(graph);




}

#ifndef SAE_ICONTEX_HPP
#define SAE_ICONTEX_HPP

/*
 * Interface for communication between vertex programs.
 */
namespace saedb {
    template<typename GraphType,typename GatherType,typename MessageType>
    class
    {
    public:
	    typedef GraphType                           graph_type;
	    typedef typename graph_type::vertex_type    vertex_type;
	    typedef typename graph_type::vertex_id_type vertex_id_type;
	    typedef MessageType                         message_type;
	    typedef GatherType                          gather_type;
        
    public:
	    virtual size_t getNumVertices() const { return 0; }
	    virtual size_t getNumEdges() const { return 0; }
	    virtual size_t getProcid() const { return 0; }
	    virtual size_t getNumProcs() const { return 0; }
        
        // return the current iteration
	    virtual int getIteration() const {return -1;}
        
        // force the engine to stop
	    virtual void stop() {}
        
	    virtual void signal(const vertex_type& vertex,
                            const message_type& message = message_type()) {}
        
	    virtual void signalVid(vertex_id_type gvid,
                               const message_type& message = message_type()) {}
        
        // get specific aggregator
        virtual IAggregator* getAggregator(const string&) {}
        
        virtual ~IContext() {}
    };
}
#endif

#pragma once
#include <vector>

typedef size_t NodeID;
template <typename NodeData, typename EdgeData>
class Graph {
	struct Edge {
		NodeID from;
		NodeID to;
		EdgeData data;
	};
	std::vector<NodeData> nodes;
	std::vector<Edge> edges;

public:
	/// Create an empty graph.
	Graph() : nodes(), edges() {}

	/// Create a grpah from a list of nodes.
	Graph(std::initializer_list<NodeData> nodes) : nodes(nodes), edges() {}

	/// Add `node` to the graph.
	void add_node(const NodeData& node) {
		this->nodes.push_back(node);
	}

	/// Creates an edge between nodes `from` and `to` consisting of data `edge`.
	void add_directional_edge(const NodeID from, const NodeID to, const EdgeData& edge) {
		this->edges.push_back({ .from = from, .to = to, .data = edge });
	}

	/// Creates two edges between nodes `from` and `to`, and vice-versa consisting of data `edge`. 
	void add_non_directional_edge(const NodeID from, const NodeID to, const EdgeData& edge) {
		this->edges.push_back({ .from = from, .to = to, .data = edge });
		this->edges.push_back({ .from = to, .to = from, .data = edge });
	}

	/// Returns false if no node matches `node` leaving `outNodeID` untouched.
	/// If a node matching `node` does exist, true is returned and `outNodeID`
	/// is set to the NodeID of the matching node.
	bool find_node_id(const NodeData& node, NodeID& outNodeID) const {
		for (size_t i = 0; i < this->nodes.size(); i++) {
			if (this->nodes[i] == node) {
				outNodeID = i;
				return true;
			}
		}
		return false;
	}

	/// Returns false if no edge can be found leaving `outEdge` untouched.
	/// If an edge is found, true is returned and `outEdge` is set to the
	/// corresponding edge data.
	bool find_edge_between_nodes(NodeID from, NodeID to, EdgeData& outEdge) const {
		for (size_t i = 0; i < this->edges.size(); i++) {
			if ((this->edges[i].from == from) && this->edges[i].to == to) {
				outEdge = this->edges[i].data;
				return true;
			}
		}
		return false;
	}

	/// Returns the NodeData from the NodeID
	inline NodeData get_node_data(NodeID node) const { return nodes[node]; }
};
